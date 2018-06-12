#include "cpu.h"

#include "instructions.h"

CPU::CPU(Memory & memory)
	: memory(memory)
	, A(0)
	, X(0), Y(0)
	, PC(0)
	, S(0)
	, P(0b00100000)
	, cycles(0)
{
}

void CPU::tick()
{
	if (cycles)
	{
		--cycles;
		return;
	}
	cycles += 2;
	uint8_t opcode = memory.read(PC++);
	uint16_t addr = 0;
	uint8_t temp = 0;
	switch (opcode)
	{
	case 0x00:	// BRK
		cycles += 2;
		pushw(PC);
		push(P);
		// TODO: Load PC
		B = true;
		break;

		// ORA
	case 0x01:
		OP_ORA(A, memory.read(xind()), P);
		break;
	case 0x05:
		OP_ORA(A, memory.read(zp()), P);
		break;
	case 0x09:
		OP_ORA(A, imm(), P);
		break;
	case 0x0D:
		OP_ORA(A, memory.read(abs()), P);
		break;
	case 0x11:
		OP_ORA(A, memory.read(indy()), P);
		break;
	case 0x15:
		OP_ORA(A, memory.read(zpx()), P);
		break;
	case 0x19:
		OP_ORA(A, memory.read(absy()), P);
		break;
	case 0x1D:
		OP_ORA(A, memory.read(absx()), P);
		break;

		// ASL
	case 0x06:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x0A:
		OP_ASL(A, P);
		break;
	case 0x0E:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x16:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x1E:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ASL(temp, P);
		memory.write(addr, temp);
		break;

	case 0x20:	// JSR
		pushw(PC + uint16_t(2));
		PC = abs();
		break;

		// AND
	case 0x21:
		OP_AND(A, memory.read(xind()), P);
		break;
	case 0x25:
		OP_AND(A, memory.read(zp()), P);
		break;
	case 0x29:
		OP_AND(A, imm(), P);
		break;
	case 0x2D:
		OP_AND(A, memory.read(abs()), P);
		break;
	case 0x31:
		OP_AND(A, memory.read(indy()), P);
		break;
	case 0x35:
		OP_AND(A, memory.read(zpx()), P);
		break;
	case 0x39:
		OP_AND(A, memory.read(absy()), P);
		break;
	case 0x3D:
		OP_AND(A, memory.read(absx()), P);
		break;

		// BIT
	case 0x24:
		OP_BIT(A, memory.read(zp()), P);
		break;
	case 0x2C:
		OP_BIT(A, memory.read(abs()), P);
		break;

	case 0x08:	// PHP
		push(P);
		break;
	case 0x28:	// PLP
		P = pull();
		break;
	case 0x48:	// PHA
		push(A);
		break;
	case 0x68:	// PLA
		A = pull();
		break;

	case 0x40:	// RTI
		cycles -= 2;
		P = pull();
		PC = pullw();
		break;
	case 0x60:	// RTS
		PC = pullw();
		++PC;
		break;

		// ROL
	case 0x26:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x2A:
		OP_ROL(A, P);
		break;
	case 0x2E:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x36:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;
	case 0x3E:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ROL(temp, P);
		memory.write(addr, temp);
		break;

		// EOR
	case 0x41:
		OP_EOR(A, memory.read(xind()), P);
		break;
	case 0x45:
		OP_EOR(A, memory.read(zp()), P);
		break;
	case 0x49:
		OP_EOR(A, imm(), P);
		break;
	case 0x4D:
		OP_EOR(A, memory.read(abs()), P);
		break;
	case 0x51:
		OP_EOR(A, memory.read(indy()), P);
		break;
	case 0x55:
		OP_EOR(A, memory.read(zpx()), P);
		break;
	case 0x59:
		OP_EOR(A, memory.read(absy()), P);
		break;
	case 0x5D:
		OP_EOR(A, memory.read(absx()), P);
		break;

		// LSR
	case 0x46:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x4A:
		OP_LSR(A, P);
		break;
	case 0x4E:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x56:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x5E:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_LSR(temp, P);
		memory.write(addr, temp);
		break;

		// ADC
	case 0x61:
		OP_ADC(A, memory.read(xind()), P);
		break;
	case 0x65:
		OP_ADC(A, memory.read(zp()), P);
		break;
	case 0x69:
		OP_ADC(A, imm(), P);
		break;
	case 0x6D:
		OP_ADC(A, memory.read(abs()), P);
		break;
	case 0x71:
		OP_ADC(A, memory.read(indy()), P);
		break;
	case 0x75:
		OP_ADC(A, memory.read(zpx()), P);
		break;
	case 0x79:
		OP_ADC(A, memory.read(absy()), P);
		break;
	case 0x7D:
		OP_ADC(A, memory.read(absx()), P);
		break;

		// ROR
	case 0x66:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x6A:
		OP_ROR(A, P);
		break;
	case 0x6E:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x76:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;
	case 0x7E:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_ROR(temp, P);
		memory.write(addr, temp);
		break;

		// STA
	case 0x81:
		memory.write(xind(), A);
		break;
	case 0x85:
		memory.write(zp(), A);
		break;
	case 0x8D:
		memory.write(abs(), A);
		break;
	case 0x91:
		memory.write(indy(), A);
		cycles = 6;
		break;
	case 0x95:
		memory.write(zpx(), A);
		break;
	case 0x99:
		memory.write(absy(), A);
		cycles = 5;
		break;
	case 0x9D:
		memory.write(absx(), A);
		cycles = 5;
		break;

		// STX
	case 0x86:
		memory.write(zp(), X);
		break;
	case 0x8E:
		memory.write(abs(), X);
		break;
	case 0x96:
		memory.write(zpy(), X);
		break;

		// STY
	case 0x84:
		memory.write(zp(), Y);
		break;
	case 0x8C:
		memory.write(abs(), Y);
		break;
	case 0x94:
		memory.write(zpx(), Y);
		break;

		// JMP
	case 0x4C:
		PC = abs();
		cycles -= 1;
		break;
	case 0x6C:
		PC = ind();
		break;

		// LDA
	case 0xA1:
		OP_LD(A, memory.read(xind()), P);
		break;
	case 0xA5:
		OP_LD(A, memory.read(zp()), P);
		break;
	case 0xA9:
		OP_LD(A, imm(), P);
		break;
	case 0xAD:
		OP_LD(A, memory.read(abs()), P);
		break;
	case 0xB1:
		OP_LD(A, memory.read(indy()), P);
		break;
	case 0xB5:
		OP_LD(A, memory.read(zpx()), P);
		break;
	case 0xB9:
		OP_LD(A, memory.read(absy()), P);
		break;
	case 0xBD:
		OP_LD(A, memory.read(absx()), P);
		break;

		// LDX
	case 0xA2:
		OP_LD(X, imm(), P);
		break;
	case 0xA6:
		OP_LD(X, memory.read(zp()), P);
		break;
	case 0xAE:
		OP_LD(X, memory.read(abs()), P);
		break;
	case 0xB6:
		OP_LD(X, memory.read(zpy()), P);
		break;
	case 0xBE:
		OP_LD(X, memory.read(absy()), P);
		break;

		// LDY
	case 0xA0:
		OP_LD(Y, imm(), P);
		break;
	case 0xA4:
		OP_LD(Y, memory.read(zp()), P);
		break;
	case 0xAC:
		OP_LD(Y, memory.read(abs()), P);
		break;
	case 0xB4:
		OP_LD(Y, memory.read(zpx()), P);
		break;
	case 0xBC:
		OP_LD(Y, memory.read(absx()), P);
		break;

		// CMP
	case 0xC1:
		OP_CMP(A, memory.read(xind()), P);
		break;
	case 0xC5:
		OP_CMP(A, memory.read(zp()), P);
		break;
	case 0xC9:
		OP_CMP(A, imm(), P);
		break;
	case 0xCD:
		OP_CMP(A, memory.read(abs()), P);
		break;
	case 0xD1:
		OP_CMP(A, memory.read(indy()), P);
		break;
	case 0xD5:
		OP_CMP(A, memory.read(zpx()), P);
		break;
	case 0xD9:
		OP_CMP(A, memory.read(absy()), P);
		break;
	case 0xDD:
		OP_CMP(A, memory.read(absx()), P);
		break;

		// CPX
	case 0xE0:
		OP_CMP(X, imm(), P);
		break;
	case 0xE4:
		OP_CMP(X, memory.read(zp()), P);
		break;
	case 0xEC:
		OP_CMP(X, memory.read(abs()), P);
		break;

	case 0xEA:	// NOP
		impl();
		break;

		// CPY
	case 0xC0:
		OP_CMP(Y, imm(), P);
		break;
	case 0xC4:
		OP_CMP(Y, memory.read(zp()), P);
		break;
	case 0xCC:
		OP_CMP(Y, memory.read(abs()), P);
		break;

		// DEC
	case 0x88:	// DEY
		OP_DEC((impl(), Y), P);
		break;
	case 0xC6:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xCA:	// DEX
		OP_DEC((impl(), X), P);
		break;
	case 0xCE:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xD6:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xDE:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_DEC(temp, P);
		memory.write(addr, temp);
		break;

		// INC
	case 0xC8:	// INY
		OP_INC((impl(), Y), P);
		break;
	case 0xE6:
		cycles += 2;
		addr = zp();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xE8:	// INX
		OP_INC((impl(), X), P);
		break;
	case 0xEE:
		cycles += 2;
		addr = abs();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xF6:
		cycles += 2;
		addr = zpx();
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;
	case 0xFE:
		addr = absx();
		cycles = 7;
		temp = memory.read(addr);
		OP_INC(temp, P);
		memory.write(addr, temp);
		break;

	case 0x10:	// BPL
		if (!N)
			PC = rel();
		break;
	case 0x30:	// BMI
		if (N)
			PC = rel();
		break;
	case 0x50:	// BVC
		if (!V)
			PC = rel();
		break;
	case 0x70:	// BVS
		if (V)
			PC = rel();
		break;
	case 0x90:	// BCC
		if (!C)
			PC = rel();
		break;
	case 0xB0:	// BCS
		if (C)
			PC = rel();
		break;
	case 0xD0:	// BNE
		if (!Z)
			PC = rel();
		break;
	case 0xF0:	// BEQ
		if (Z)
			PC = rel();
		break;

	case 0x18:	// CLC
		C = (impl(), false);
		break;
	case 0x58:	// CLI
		I = (impl(), false);
		break;
	case 0xB8:	// CLV
		V = (impl(), false);
		break;
	case 0xD8:	// CLD
		D = (impl(), false);
		break;

	case 0x38:	// SEC
		(impl(), C) = true;
		break;
	case 0x78:	// SEI
		(impl(), I) = true;
		break;
	case 0xF8:	// SED
		(impl(), D) = true;
		break;

	case 0x8A:	// TXA
		impl();
		OP_LD(A, X, P);
		break;
	case 0x98:	// TYA
		impl();
		OP_LD(A, Y, P);
		break;
	case 0x9A:	// TXS
		impl();
		OP_LD(S, X, P);
		break;

	case 0xA8:	// TAY
		impl();
		OP_LD(Y, A, P);
		break;
	case 0xAA:	// TAX
		impl();
		OP_LD(X, A, P);
		break;
	case 0xBA:	// TSX
		impl();
		OP_LD(X, S, P);
		break;

		// TODO: SBC

	default:
		break;
	}
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
	return memory.read(PC++);
}

uint16_t CPU::zp()
{
	cycles += 1;
	return memory.read(PC++);
}

uint16_t CPU::zpx()
{
	cycles += 2;
	return memory.read(PC++) + X;
}

uint16_t CPU::zpy()
{
	cycles += 2;
	return memory.read(PC++) + Y;
}

uint16_t CPU::rel()
{
	cycles += 0;
	int8_t offset = memory.read(PC++);
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
	return addr.addr + Y;
}

uint16_t CPU::ind()
{
	cycles += 3;
	addr_t addr{};
	addr_t addr0{};
	addr0.low = memory.read(PC++);
	addr0.high = memory.read(PC++);
	addr.low = memory.read(addr0.addr++);
	addr.high = memory.read(addr0.addr);
	return addr.addr;
}

uint16_t CPU::xind()
{
	cycles += 4;
	uint8_t arg = memory.read(PC++);
	addr_t addr{};
	addr.low = memory.read(uint8_t(arg + X));
	addr.high = memory.read(uint8_t(arg + X + 1));
	return addr.addr;
}

uint16_t CPU::indy()
{
	cycles += 3;
	uint8_t arg = memory.read(PC++);
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
