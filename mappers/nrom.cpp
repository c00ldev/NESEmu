#include "nrom.h"

#include <utility>


NROM::NROM(Type type)
	: PRG_ROM(size_t(type) * 16384)
	, PRG_RAM(8192)
	, CHR(8192)
{
	map.map(0x0000, PRG_RAM);
	map.map(0x2000, PRG_ROM);
	if (type == Type::NROM_128)
		map.map(0x6000, PRG_ROM);
}

uint8_t NROM::read(uint16_t addr) const
{
	return map.read(addr - 0x1FE0);
}

uint8_t NROM::write(uint16_t addr, uint8_t val)
{
	return map.write(addr - 0x1FE0, val);
}

uint8_t NROM::write(uint16_t addr, uint8_t val) const
{
	return map.read(addr - 0x1FE0);
}

size_t NROM::size() const
{
	return map.size();
}

void NROM::load(std::vector<uint8_t> PRG_ROM, std::vector<uint8_t> CHR)
{
	this->PRG_ROM.setContents(std::move(PRG_ROM));
	this->CHR.setContents(std::move(CHR));
}
