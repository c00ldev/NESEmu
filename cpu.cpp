#include "cpu.h"

#include "instructions.h"

#include <queue>

#include "log.h"

#include <thread>

CPU::CPU(Memory & memory)
	: memory(memory)
	, A(0)
	, X(0), Y(0)
	, PC(0)
	, S(0)
	, P(0b00100000)
	, cycles(0)
	, start(clock_type::now())
{
}

void CPU::tick()
{
//	if (cycles)
//	{
//		--cycles;
//		return;
//	}
	cycles += 2;
	uint8_t opcode = memory.read(PC++);
	uint16_t addr = 0;
	uint8_t temp = 0;
	Log(std::hex);
	switch (opcode)
	{
	case 0x00:	// BRK
		Log("BRK ");
		cycles += 2;
		pushw(PC);
		push(P);
		PCL = memory.read(0xFFFE);
		PCH = memory.read(0xFFFF);
		B = true;
		break;

		// ORA
	case 0x01:
		Log("ORA ");
		OP_ORA(A, memory.read(xind()), P);
		break;
	case 0x05:
		Log("ORA ");
		OP_ORA(A, memory.read(zp()), P);
		break;
	case 0x09:
		Log("ORA ");
		OP_ORA(A, imm(), P);
		break;
	case 0x0D:
		Log("ORA ");
		OP_ORA(A, memory.read(abs()), P);
		break;
	case 0x11:
		Log("ORA ");
		OP_ORA(A, memory.read(indy()), P);
		break;
	case 0x15:
		Log("ORA ");
		OP_ORA(A, memory.read(zpx()), P);
		break;
	case 0x19:
		Log("ORA ");
		OP_ORA(A, memory.read(absy()), P);
		break;
	case 0x1D:
		Log("ORA ");
		OP_ORA(A, memory.read(absx()), P);
		break;

		// ASL
	case 0x06:
		Log("ASL ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x0A:
		Log("ASL ");
		OP_ASL(A, P);
		break;
	case 0x0E:
		Log("ASL ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x16:
		Log("ASL ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x1E:
		Log("ASL ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;

	case 0x20:	// JSR
		Log("JSR ");
		pushw(PC + uint16_t(2));
		PC = abs();
		break;

		// AND
	case 0x21:
		Log("AND ");
		OP_AND(A, memory.read(xind()), P);
		break;
	case 0x25:
		Log("AND ");
		OP_AND(A, memory.read(zp()), P);
		break;
	case 0x29:
		Log("AND ");
		OP_AND(A, imm(), P);
		break;
	case 0x2D:
		Log("AND ");
		OP_AND(A, memory.read(abs()), P);
		break;
	case 0x31:
		Log("AND ");
		OP_AND(A, memory.read(indy()), P);
		break;
	case 0x35:
		Log("AND ");
		OP_AND(A, memory.read(zpx()), P);
		break;
	case 0x39:
		Log("AND ");
		OP_AND(A, memory.read(absy()), P);
		break;
	case 0x3D:
		Log("AND ");
		OP_AND(A, memory.read(absx()), P);
		break;

		// BIT
	case 0x24:
		Log("BIT ");
		OP_BIT(A, memory.read(zp()), P);
		break;
	case 0x2C:
		Log("BIT ");
		OP_BIT(A, memory.read(abs()), P);
		break;

	case 0x08:	// PHP
		Log("PHP ");
		push(P);
		break;
	case 0x28:	// PLP
		Log("PLP ");
		P = pull();
		break;
	case 0x48:	// PHA
		Log("PHA ");
		push(A);
		break;
	case 0x68:	// PLA
		Log("PLA ");
		A = pull();
		break;

	case 0x40:	// RTI
		Log("RTI ");
		cycles -= 2;
		P = pull();
		PC = pullw();
		break;
	case 0x60:	// RTS
		Log("RTS ");
		PC = pullw();
		++PC;
		break;

		// ROL
	case 0x26:
		Log("ROL ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x2A:
		Log("ROL ");
		OP_ROL(A, P);
		break;
	case 0x2E:
		Log("ROL ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x36:
		Log("ROL ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x3E:
		Log("ROL ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;

		// EOR
	case 0x41:
		Log("EOR ");
		OP_EOR(A, memory.read(xind()), P);
		break;
	case 0x45:
		Log("EOR ");
		OP_EOR(A, memory.read(zp()), P);
		break;
	case 0x49:
		Log("EOR ");
		OP_EOR(A, imm(), P);
		break;
	case 0x4D:
		Log("EOR ");
		OP_EOR(A, memory.read(abs()), P);
		break;
	case 0x51:
		Log("EOR ");
		OP_EOR(A, memory.read(indy()), P);
		break;
	case 0x55:
		Log("EOR ");
		OP_EOR(A, memory.read(zpx()), P);
		break;
	case 0x59:
		Log("EOR ");
		OP_EOR(A, memory.read(absy()), P);
		break;
	case 0x5D:
		Log("EOR ");
		OP_EOR(A, memory.read(absx()), P);
		break;

		// LSR
	case 0x46:
		Log("LSR ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x4A:
		Log("LSR ");
		OP_LSR(A, P);
		break;
	case 0x4E:
		Log("LSR ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x56:
		Log("LSR ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x5E:
		Log("LSR ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;

		// ADC
	case 0x61:
		Log("ADC ");
		OP_ADC(A, memory.read(xind()), P);
		break;
	case 0x65:
		Log("ADC ");
		OP_ADC(A, memory.read(zp()), P);
		break;
	case 0x69:
		Log("ADC ");
		OP_ADC(A, imm(), P);
		break;
	case 0x6D:
		Log("ADC ");
		OP_ADC(A, memory.read(abs()), P);
		break;
	case 0x71:
		Log("ADC ");
		OP_ADC(A, memory.read(indy()), P);
		break;
	case 0x75:
		Log("ADC ");
		OP_ADC(A, memory.read(zpx()), P);
		break;
	case 0x79:
		Log("ADC ");
		OP_ADC(A, memory.read(absy()), P);
		break;
	case 0x7D:
		Log("ADC ");
		OP_ADC(A, memory.read(absx()), P);
		break;

		// ROR
	case 0x66:
		Log("ROR ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x6A:
		Log("ROR ");
		OP_ROR(A, P);
		break;
	case 0x6E:
		Log("ROR ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x76:
		Log("ROR ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x7E:
		Log("ROR ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;

		// STA
	case 0x81:
		Log("STA ");
		memory.write(xind(), A);
		break;
	case 0x85:
		Log("STA ");
		memory.write(zp(), A);
		break;
	case 0x8D:
		Log("STA ");
		memory.write(abs(), A);
		break;
	case 0x91:
		Log("STA ");
		memory.write(indy(), A);
		cycles = 6;
		break;
	case 0x95:
		Log("STA ");
		memory.write(zpx(), A);
		break;
	case 0x99:
		Log("STA ");
		memory.write(absy(), A);
		cycles = 5;
		break;
	case 0x9D:
		Log("STA ");
		memory.write(absx(), A);
		cycles = 5;
		break;

		// STX
	case 0x86:
		Log("STX ");
		memory.write(zp(), X);
		break;
	case 0x8E:
		Log("STX ");
		memory.write(abs(), X);
		break;
	case 0x96:
		Log("STX ");
		memory.write(zpy(), X);
		break;

		// STY
	case 0x84:
		Log("STY ");
		memory.write(zp(), Y);
		break;
	case 0x8C:
		Log("STY ");
		memory.write(abs(), Y);
		break;
	case 0x94:
		Log("STY ");
		memory.write(zpx(), Y);
		break;

		// JMP
	case 0x4C:
		Log("JMP ");
		PC = abs();
		cycles -= 1;
		break;
	case 0x6C:
		Log("JMP ");
		PC = ind();
		break;

		// LDA
	case 0xA1:
		Log("LDA ");
		OP_LD(A, memory.read(xind()), P);
		break;
	case 0xA5:
		Log("LDA ");
		OP_LD(A, memory.read(zp()), P);
		break;
	case 0xA9:
		Log("LDA ");
		OP_LD(A, imm(), P);
		break;
	case 0xAD:
		Log("LDA ");
		OP_LD(A, memory.read(abs()), P);
		break;
	case 0xB1:
		Log("LDA ");
		OP_LD(A, memory.read(indy()), P);
		break;
	case 0xB5:
		Log("LDA ");
		OP_LD(A, memory.read(zpx()), P);
		break;
	case 0xB9:
		Log("LDA ");
		OP_LD(A, memory.read(absy()), P);
		break;
	case 0xBD:
		Log("LDA ");
		OP_LD(A, memory.read(absx()), P);
		break;

		// LDX
	case 0xA2:
		Log("LDX ");
		OP_LD(X, imm(), P);
		break;
	case 0xA6:
		Log("LDX ");
		OP_LD(X, memory.read(zp()), P);
		break;
	case 0xAE:
		Log("LDX ");
		OP_LD(X, memory.read(abs()), P);
		break;
	case 0xB6:
		Log("LDX ");
		OP_LD(X, memory.read(zpy()), P);
		break;
	case 0xBE:
		Log("LDX ");
		OP_LD(X, memory.read(absy()), P);
		break;

		// LDY
	case 0xA0:
		Log("LDY ");
		OP_LD(Y, imm(), P);
		break;
	case 0xA4:
		Log("LDY ");
		OP_LD(Y, memory.read(zp()), P);
		break;
	case 0xAC:
		Log("LDY ");
		OP_LD(Y, memory.read(abs()), P);
		break;
	case 0xB4:
		Log("LDY ");
		OP_LD(Y, memory.read(zpx()), P);
		break;
	case 0xBC:
		Log("LDY ");
		OP_LD(Y, memory.read(absx()), P);
		break;

		// CMP
	case 0xC1:
		Log("CMP ");
		OP_CMP(A, memory.read(xind()), P);
		break;
	case 0xC5:
		Log("CMP ");
		OP_CMP(A, memory.read(zp()), P);
		break;
	case 0xC9:
		Log("CMP ");
		OP_CMP(A, imm(), P);
		break;
	case 0xCD:
		Log("CMP ");
		OP_CMP(A, memory.read(abs()), P);
		break;
	case 0xD1:
		Log("CMP ");
		OP_CMP(A, memory.read(indy()), P);
		break;
	case 0xD5:
		Log("CMP ");
		OP_CMP(A, memory.read(zpx()), P);
		break;
	case 0xD9:
		Log("CMP ");
		OP_CMP(A, memory.read(absy()), P);
		break;
	case 0xDD:
		Log("CMP ");
		OP_CMP(A, memory.read(absx()), P);
		break;

		// CPX
	case 0xE0:
		Log("CPX ");
		OP_CMP(X, imm(), P);
		break;
	case 0xE4:
		Log("CPX ");
		OP_CMP(X, memory.read(zp()), P);
		break;
	case 0xEC:
		Log("CPX ");
		OP_CMP(X, memory.read(abs()), P);
		break;

	case 0xEA:	// NOP
		Log("NOP ");
		impl();
		break;

		// CPY
	case 0xC0:
		Log("CPY ");
		OP_CMP(Y, imm(), P);
		break;
	case 0xC4:
		Log("CPY ");
		OP_CMP(Y, memory.read(zp()), P);
		break;
	case 0xCC:
		Log("CPY ");
		OP_CMP(Y, memory.read(abs()), P);
		break;

		// DEC
	case 0x88:	// DEY
		Log("DEY ");
		OP_DEC((impl(), Y), P);
		break;
	case 0xC6:
		Log("DEC ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xCA:	// DEX
		Log("DEX ");
		OP_DEC((impl(), X), P);
		break;
	case 0xCE:
		Log("DEC ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xD6:
		Log("DEC ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xDE:
		Log("DEC ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;

		// INC
	case 0xC8:	// INY
		Log("INY ");
		OP_INC((impl(), Y), P);
		break;
	case 0xE6:
		Log("DEC ");
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xE8:	// INX
		Log("INX ");
		OP_INC((impl(), X), P);
		break;
	case 0xEE:
		Log("DEC ");
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xF6:
		Log("DEC ");
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xFE:
		Log("DEC ");
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;

	case 0x10:	// BPL
		Log("BPL ");
		if (!N)
			PC = rel();
		break;
	case 0x30:	// BMI
		Log("BMI ");
		if (N)
			PC = rel();
		break;
	case 0x50:	// BVC
		Log("BVC ");
		if (!V)
			PC = rel();
		break;
	case 0x70:	// BVS
		Log("BVS ");
		if (V)
			PC = rel();
		break;
	case 0x90:	// BCC
		Log("BCC ");
		if (!C)
			PC = rel();
		break;
	case 0xB0:	// BCS
		Log("BCS ");
		if (C)
			PC = rel();
		break;
	case 0xD0:	// BNE
		Log("BNE ");
		if (!Z)
			PC = rel();
		break;
	case 0xF0:	// BEQ
		Log("BEQ ");
		if (Z)
			PC = rel();
		break;

	case 0x18:	// CLC
		Log("CLC ");
		C = (impl(), false);
		break;
	case 0x58:	// CLI
		Log("CLI ");
		I = (impl(), false);
		break;
	case 0xB8:	// CLV
		Log("CLV ");
		V = (impl(), false);
		break;
	case 0xD8:	// CLD
		Log("CLD ");
		D = (impl(), false);
		break;

	case 0x38:	// SEC
		Log("SEC ");
		(impl(), C) = true;
		break;
	case 0x78:	// SEI
		Log("SEI ");
		(impl(), I) = true;
		break;
	case 0xF8:	// SED
		Log("SED ");
		(impl(), D) = true;
		break;

	case 0x8A:	// TXA
		Log("TXA ");
		impl();
		OP_LD(A, X, P);
		break;
	case 0x98:	// TYA
		Log("TYA ");
		impl();
		OP_LD(A, Y, P);
		break;
	case 0x9A:	// TXS
		Log("TXS ");
		impl();
		OP_LD(S, X, P);
		break;

	case 0xA8:	// TAY
		Log("TAY ");
		impl();
		OP_LD(Y, A, P);
		break;
	case 0xAA:	// TAX
		Log("TAX ");
		impl();
		OP_LD(X, A, P);
		break;
	case 0xBA:	// TSX
		Log("TSX ");
		impl();
		OP_LD(X, S, P);
		break;

		// SBC
	case 0xE1:
		Log("SBC ");
		OP_SBC(A, memory.read(xind()), P);
		break;
	case 0xE5:
		Log("SBC ");
		OP_SBC(A, memory.read(zp()), P);
		break;
	case 0xE9:
		Log("SBC ");
		OP_SBC(A, imm(), P);
		break;
	case 0xED:
		Log("SBC ");
		OP_SBC(A, memory.read(abs()), P);
		break;
	case 0xF1:
		Log("SBC ");
		OP_SBC(A, memory.read(indy()), P);
		break;
	case 0xF5:
		Log("SBC ");
		OP_SBC(A, memory.read(zpx()), P);
		break;
	case 0xF9:
		Log("SBC ");
		OP_SBC(A, memory.read(absy()), P);
		break;
	case 0xFD:
		Log("SBC ");
		OP_SBC(A, memory.read(absx()), P);
		break;

	default:
		break;
	}
	Log(std::endl);
	for (size_t i = 0; i < cycles; ++i)
	{
		// ppu.tick()
		// ppu.tick()
		// ppu.tick()
	}
	std::chrono::duration<long double, std::ratio<1, 1>> dur(12.0 / 21477272.0);
	auto dur1 = std::chrono::duration_cast<clock_type::duration>(dur);
	std::this_thread::sleep_until(start + dur1 * cycles);
	start += dur1 * cycles;
}

union addr_t
{
	uint16_t addr;
	struct
	{
		uint8_t low;
		uint8_t high;
	};
};

void CPU::impl()
{
	cycles += 0;
}

uint8_t CPU::imm()
{
	cycles += 0;
	uint8_t res = memory.read(PC++);
	Log("#$" << (signed)res);
	return res;
}

uint16_t CPU::zp()
{
	cycles += 1;
	uint8_t res = memory.read(PC++);
	Log("$" << (signed)res);
	return res;
}

uint16_t CPU::zpx()
{
	cycles += 2;
	uint8_t res = memory.read(PC++) + X;
	Log("$" << (signed)res << ",X");
	return res;
}

uint16_t CPU::zpy()
{
	cycles += 2;
	uint8_t res = memory.read(PC++) + Y;
	Log("$" << (signed)res << ",Y");
	return res;
}

uint16_t CPU::rel()
{
	cycles += 0;
	int8_t offset = memory.read(PC++);
	if (offset < 0)
		Log("$-" << (signed)-offset);
	else
		Log("$" << (signed)offset);
	addr_t addr1{};
	addr1.addr = PC;
	addr1.low += offset;
	if (PC + offset != addr1.addr)
		cycles += 1;
	return PC + offset;
}

uint16_t CPU::abs()
{
	cycles += 2;
	addr_t addr{};
	addr.low = memory.read(PC++);
	addr.high = memory.read(PC++);
	Log("$" << (signed)addr.addr);
	return addr.addr;
}

uint16_t CPU::absx()
{
	cycles += 2;
	addr_t addr{};
	addr.low = memory.read(PC++);
	addr.high = memory.read(PC++);
	addr_t addr1 = addr;
	addr1.low += X;
	if (addr.addr + X != addr1.addr)
		cycles += 1;
	Log("$" << (signed)addr.addr << ",X");
	return addr.addr + X;
}

uint16_t CPU::absy()
{
	cycles += 2;
	addr_t addr{};
	addr.low = memory.read(PC++);
	addr.high = memory.read(PC++);
	addr_t addr1 = addr;
	addr1.low += Y;
	if (addr.addr + Y != addr1.addr)
		cycles += 1;
	Log("$" << (signed)addr.addr << ",Y");
	return addr.addr + Y;
}

uint16_t CPU::ind()
{
	cycles += 3;
	addr_t addr{};
	addr_t addr0{};
	addr0.low = memory.read(PC++);
	addr0.high = memory.read(PC++);
	Log("($" << (signed)addr0.addr << ")");
	addr.low = memory.read(addr0.addr++);
	addr.high = memory.read(addr0.addr);
	return addr.addr;
}

uint16_t CPU::xind()
{
	cycles += 4;
	uint8_t arg = memory.read(PC++);
	Log("($" << (signed)arg << ",X)");
	addr_t addr{};
	addr.low = memory.read(uint8_t(arg + X));
	addr.high = memory.read(uint8_t(arg + X + 1));
	return addr.addr;
}

uint16_t CPU::indy()
{
	cycles += 3;
	uint8_t arg = memory.read(PC++);
	Log("($" << (signed)arg << "),Y");
	addr_t addr{};
	addr.low = memory.read(uint8_t(arg));
	addr.high = memory.read(uint8_t(arg + 1));
	addr_t addr1 = addr;
	addr1.low += Y;
	if (addr.addr + Y != addr1.addr)
		cycles += 1;
	return addr.addr + Y;
}

void CPU::push(uint8_t val)
{
	cycles += 1;
	memory.write(uint16_t(0x100) + (--(impl(), S)), val);
}

uint8_t CPU::pull()
{
	cycles += 2;
	return memory.read(uint16_t(0x100) + ((impl(), S)++));
}

void CPU::pushw(uint16_t val)
{
	addr_t addr{};
	addr.addr = val;
	push(addr.high);
	push(addr.low);
}

uint16_t CPU::pullw()
{
	addr_t addr{};
	addr.low = pull();
	addr.high = pull();
	return addr.addr;
}

void CPU::powerUp()
{
	PCL = memory.read(0xFFFC);
	PCH = memory.read(0xFFFD);
}

size_t CPU::getCycleCount()
{
	return 1;
}
