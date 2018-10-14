#pragma once

#include "../cartridge.h"
#include "../ram.h"

#include <vector>
#include <cstdint>

class NROM : public Cartridge
{
	ROM PRG_ROM;
	RAM PRG_RAM;
	ROM CHR;

	friend class PRG_t;
	class PRG_t : public Memory
	{
		friend class NROM;
		NROM & nrom;
		explicit PRG_t(NROM & nrom);
	public:
		uint8_t read(uint16_t addr) const override;
		uint8_t write(uint16_t addr, uint8_t val) override;
		uint8_t write(uint16_t addr, uint8_t val) const override;
		size_t size() const override;
		std::pair<Memory &, uint16_t> resolve(uint16_t addr);
		std::pair<const Memory &, uint16_t> resolve(uint16_t addr) const;
	} PRG;
public:
	enum class Type
	{
		NROM_128 = 1,
		NROM_256 = 2
	};
	explicit NROM(Type type);
	Memory & getPRG() override;
	Memory & getCHR() override;
	Memory & getEXP() override;
	void load(std::vector<uint8_t> PRG_ROM, std::vector<uint8_t> CHR);
};
