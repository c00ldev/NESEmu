#pragma once

#include "reg_ptr.h"
#include "ram.h"
#include <cstdint>

class CtrlBus;
class MemBus;

class PPU
{
	CtrlBus & ctrl;
	MemBus & bus;

	ROM palettes;

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
	PPU(CtrlBus & ctrl, MemBus & bus);
	void tick();
	Memory & getRegs();
	Memory & getPalettes();
};
