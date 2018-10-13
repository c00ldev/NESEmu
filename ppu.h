#pragma once

#include <cstdint>

#include "reg_ptr.h"
#include "ram.h"

class PPU
{
	Memory & memory;

	union
	{
		uint8_t PPUCTRL;
	};
	union
	{
		uint8_t PPUMASK;
	};
	union
	{
		uint8_t PPUSTATUS;
	};
	union
	{
		uint8_t OAMADDR;
	};
	union
	{
		uint8_t OAMDATA;
	};
	union
	{
		uint8_t PPUSCROLL;
	};
	union
	{
		uint8_t PPUADDR;
	};
	union
	{
		uint8_t PPUDATA;
	};

	union
	{
		uint8_t OAMDMA;
	};

	RegPtr regs1;

	RAM OAM;
public:
	explicit PPU(Memory & memory);
	Memory & getRegs();
};
