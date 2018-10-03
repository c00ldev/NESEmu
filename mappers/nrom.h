#pragma once

#include "../cartridge.h"
#include "../ram.h"
#include "../mem_map.h"

#include <vector>
#include <cstdint>

class NROM : public Cartridge
{
	ROM PRG_ROM;
	RAM PRG_RAM;
	ROM CHR;
	MemMap map;
public:
	enum class Type
	{
		NROM_128 = 1,
		NROM_256 = 2
	};
	NROM(Type type);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
	void load(std::vector<uint8_t> PRG_ROM, std::vector<uint8_t> CHR);
};
