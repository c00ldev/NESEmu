#include "mem_bus.h"

#include <functional>


MemBus::MemBus(Memory & ram, Memory & ppu, Memory & apu_io, Memory & cartridge, Memory & cartridge_exp)
	: ram(ram)
	, ppu(ppu)
	, apu_io(apu_io)
	, cartridge(cartridge)
	, cartridge_exp(cartridge_exp)
{
}

bool bit(uint16_t addr, size_t i)
{
	return (addr & uint16_t(1 << i)) != 0;
}

uint8_t MemBus::read(uint16_t addr) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.read(pAddr);
}

uint8_t MemBus::write(uint16_t addr, uint8_t val)
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

uint8_t MemBus::write(uint16_t addr, uint8_t val) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

size_t MemBus::size() const
{
	return 0x10000u;
}

std::pair<Memory &, uint16_t> MemBus::resolve(uint16_t addr) const
{
	switch ((addr & uint16_t(0b111u << 13)) >> 13)
	{
	case 0b000:	// [0x0000, 0x2000)
		return std::pair(std::ref(ram), addr & uint16_t(0b11111111111u));
	case 0b001:	// [0x2000, 0x4000)
		return std::pair(std::ref(ppu), addr & uint16_t(0b111u));
	case 0b010:	// [0x4000, 0x6000)
		if ((addr & uint16_t(0b11111111u << 5)) >> 5 == 0)	// [0x4000, 0x4020)
			return std::pair(std::ref(apu_io), addr & uint16_t(0b11111u));
		return std::pair(std::ref(cartridge_exp), addr & 0b1111111111111u);
	default:	// [0x6000, 0xFFFF)
		return std::pair(std::ref(cartridge), addr - 0x4020u);
	}
}
