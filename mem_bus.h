#pragma once

#include "memory.h"

#include <utility>

class MemBus : public Memory
{
	Memory & ram;
	Memory & ppu;
	Memory & apu_io;
	Memory & cartridge;
	Memory & cartridge_exp;
public:
	MemBus(Memory & ram, Memory & ppu, Memory & apu_io, Memory & cartridge, Memory & cartridge_exp);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
	std::pair<Memory &, uint16_t> resolve(uint16_t addr) const;
};

class VMemBus : public Memory
{
	Memory & patternTables;
	Memory & nameTable0;
	Memory & nameTable1;
	Memory & nameTable2;
	Memory & nameTable3;
	Memory & palette;
public:
	VMemBus(Memory & patternTables, Memory & nameTable0, Memory & nameTable1,
			Memory & nameTable2, Memory & nameTable3, Memory & palette);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
	std::pair<Memory &, uint16_t> resolve(uint16_t addr) const;
};
