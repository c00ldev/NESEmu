#pragma once

#include <cstdint>
#include <cstddef>
#include <queue>

class CtrlBus;
class MemBus;

class CPU
{
	CtrlBus & ctrl;
	MemBus & bus;

	uint8_t A;
	uint8_t X, Y;
	union
	{
		uint16_t PC;
		struct
		{
			uint8_t PCL;
			uint8_t PCH;
		};
	};
	uint8_t S;
	union
	{
		uint8_t P;
		struct
		{
			bool C : 1;
			bool Z : 1;
			bool I : 1;
			bool D : 1;
			bool B : 1;
			bool Always1 : 1;
			bool V : 1;
			bool N : 1;
		};
	};
	uint16_t opcode;
	unsigned addr;
	unsigned d;
	unsigned t;
	unsigned c;
	unsigned sb;
	unsigned pbits;
	std::queue<size_t> instr;
	bool fetched;
	//template<uint16_t Opcode> friend void instruction(CPU & cpu);
public:
	CPU(CtrlBus & ctrl, MemBus & bus);
	void tick();

	void fetch();
	void decode();
	void execute();

	uint16_t wrap(uint16_t oldaddr, uint16_t newaddr);
//	void misfire(uint16_t old, uint16_t addr);
//	uint8_t push(uint8_t data);
//	uint8_t pop();
//	uint8_t read(uint16_t address);
//	uint8_t write(uint16_t address,uint8_t data);
};
