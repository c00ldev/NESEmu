#include "cpu.h"

#include "ctrl_bus.h"
#include "mem_bus.h"


InstructionDecoder CPU::decoder;

CPU::CPU(CtrlBus & ctrl, MemBus & bus)
	: ctrl(ctrl)
	, bus(bus)
	, A(0)
	, X(0), Y(0)
	, PC(0)
	, S(0)
	, P(0b00100000)
	, opcode(0)
	, addr(0)
	, d(0)
	, t(0)
	, c(0)
	, sb(0)
	, pbits(0)
	, instr()
{
}

void CPU::tick()
{
	if (instr.empty())
	{
		fetch();
		decode();
	}
	execute();
}

void CPU::fetch()
{
	if (ctrl.reset)
	{
		opcode = 0x101;
		return;
	}
	if (ctrl.nmi && !ctrl.nmiEdge)
	{
		opcode = 0x100;
		ctrl.nmiEdge = true;
		return;
	}
	if (ctrl.interrupt & !I)
	{
		opcode = 0x102;
		return;
	}
	instr.push(57);
	instr.push(65);
	instr.push(0);
	instr.push(71);
	instr.push(66);
	while (!instr.empty())
		execute();
}

void CPU::decode()
{
	if (!ctrl.nmi)
		ctrl.nmiEdge = false;
	addr = 0;
	d = 0;
	t = 0xFF;
	c = 0;
	sb = 0;
	pbits = opcode < 0x100 ? 0x30 : 0x20;
	for (size_t ins : InstructionDecoder::instructions[opcode])
		instr.push(ins);
}

void CPU::execute()
{
	while (!instr.empty())
	{
		size_t i = instr.front();
		instr.pop();
#define t(n,code) case n: code; break;
		switch (i)
		{
		case 0: return;
			/* Decode address operand */
		t(1, addr = 0xFFFA) // NMI vector location
		t(2, addr = 0xFFFC) // Reset vector location
		t(3, addr = 0xFFFE) // Interrupt vector location
		t(5, d = X) // register index
		t(6, d = Y)
		t(7, addr=uint8_t(addr+d); d=0)              // add zeropage-index
		t(8, addr=uint8_t(addr))       // absolute address
//		t(10, misfire(addr, addr+d)) // abs. load: extra misread when cross-page
			/* Load source operand */
		t(12, t &= A) // Many operations take A or X as operand. Some try in
		t(13, t &= X) // error to take both; the outcome is an AND operation.
		t(14, t &= Y) // sty,dey,iny,tya,cpy
		t(15, t &= S) // tsx, las
		t(16, t &= P|pbits; c = t)// php, flag test/set/clear, interrupts
		t(17, c = t; t = 0xFF)        // save as second operand
			/* Operations that mogrify memory operands directly */
		t(20, V = t & 0x40; N = t & 0x80) // bit
		t(21, sb = C)       // rol,rla, ror,rra,arr
		t(22, C = t & 0x80) // rol,rla, asl,slo,[arr,anc]
		t(23, C = t & 0x01) // lsr,sre, ror,rra,asr
		t(24, t = (t << 1) | (sb * 0x01))
		t(25, t = (t >> 1) | (sb * 0x80))
		t(26, t = uint8_t(t - 1))  // dec,dex,dey,dcp
		t(27, t = uint8_t(t + 1))  // inc,inx,iny,isb
			/* Stack operations and unconditional jumps */
//		t(31, waitTick(); t = pop())                        // pla,plp,rti
//		t(32, read(PC++); PC = pop(); PC |= (pop() << 8)) // rti,rts
//		t(34, d = PC + (opcode ? -1 : 1); push(d>>8); push(d))      // jsr, interrupts
		t(35, PC = addr) // jmp, jsr, interrupts
//		t(36, push(t))   // pha, php, interrupts
			/* Bitmasks */
		t(37, t = 1)
		t(38, t <<= 1)
		t(39, t <<= 2)
		t(40, t <<= 4)
		t(41, t = uint8_t(~t)) // sbc, isb,      clear flag
		t(42, t = c | t)  // ora, slo,      set flag
		t(43, t = c & t)  // and, bit, rla, clear/test flag
		t(44, t = c ^ t)  // eor, sre
			/* Conditional branches */
//		t(45, if(t)  { waitTick(); misfire(PC, addr = int8_t(addr) + PC); PC=addr; })
//		t(46, if(!t) { waitTick(); misfire(PC, addr = int8_t(addr) + PC); PC=addr; })
			/* Addition and subtraction */
		t(47, c = t; t += A + C; V = (c^t) & (A^t) & 0x80; C = t & 0x100)
		t(48, t = c - t; C = ~t & 0x100) // cmp,cpx,cpy, dcp, sbx
			/* Store modified value (register) */
		t(49, A = t)
		t(50, X = t) // ldx, dex, tax, inx, tsx,lax,las,sbx
		t(51, Y = t) // ldy, dey, tay, iny
		t(52, S = t) // txs, las, shs
		t(53, P = t & ~0x30) // plp, rti, flag set/clear
			/* Generic status flag updates */
		t(54, N = t & 0x80)
		t(55, Z = uint8_t(t) == 0)
		t(56, V = (((t >> 5)+1)&2))         // [arr]


			/* Memory microinstructions */
		t(57, bus.address = PC++)
		t(58, bus.address = c = addr)
		t(59, bus.address = wrap(c,c+1))
		t(60, bus.address = wrap(addr, addr+d))
		t(61, bus.address = addr+d)

		t(62, addr = bus.data)
		t(63, addr += 256 * bus.data)
		t(64, t &= bus.data)

		t(65, bus.enable = true)
		t(66, bus.enable = false)
		t(67, bus.write = true)
		t(68, bus.write = false)

		t(69, bus.data = t)
		t(70, bus.data = t &= ((addr+d) >> 8))

		t(71, opcode = bus.data)

		}
#undef t
	}
	ctrl.reset = false;
}

uint16_t CPU::wrap(uint16_t oldaddr, uint16_t newaddr)
{
	return (oldaddr & uint16_t(0xFF00)) + uint8_t(newaddr);
}

//void CPU::misfire(uint16_t old, uint16_t addr)
//{
//	if (uint16_t q = wrap(old, addr); q != addr)
//		read(q);
//}
//
//uint8_t CPU::push(uint8_t data)
//{
//	return write(uint16_t(0x100) | S--, data);
//}
//
//uint8_t CPU::pop()
//{
//	return read(uint16_t(0x100) | ++S);
//}
//
//uint8_t CPU::read(uint16_t address)
//{
//	bus.address = address;
//	bus.enable = true;
//	waitTick();
//	return bus.data;
//}
//
//uint8_t CPU::write(uint16_t address, uint8_t data)
//{
////	if (reset)
////		return read(address);
//	bus.address = address;
//	bus.data = data;
//	bus.write = true;
//	bus.enable = true;
//	waitTick();
//	return bus.data;
//}
