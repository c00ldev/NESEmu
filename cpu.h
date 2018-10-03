#pragma once

#include "tickable.h"

#include <cstdint>
#include <cstddef>

#include "memory.h"

class CPU : public Tickable
{
	Memory & memory;

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
//	std::queue
	size_t cycles;
public:
	CPU(Memory & memory);
	void tick() override;
private:
	void impl();
	uint8_t imm();
	uint16_t zp();
	uint16_t zpx();
	uint16_t zpy();
	uint16_t rel();
	uint16_t abs();
	uint16_t absx();
	uint16_t absy();
	uint16_t ind();
	uint16_t xind();
	uint16_t indy();
private:
	void push(uint8_t val);
	uint8_t pull();

	void pushw(uint16_t val);
	uint16_t pullw();
};
