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
	switch ((addr & uint16_t(0b111u << 13u)) >> 13u)
	{
	case 0b000:	// [0x0000, 0x2000)
		return std::pair(std::ref(ram), addr & uint16_t(0b111'1111'1111u));
	case 0b001:	// [0x2000, 0x4000)
		return std::pair(std::ref(ppu), addr & uint16_t(0b111u));
	case 0b010:	// [0x4000, 0x6000)
		if ((addr & uint16_t(0b11111111u << 5u)) >> 5u == 0)	// [0x4000, 0x4020)
			return std::pair(std::ref(apu_io), addr & uint16_t(0b1'1111u));
		return std::pair(std::ref(cartridge_exp), addr & 0b1'1111'1111'1111u);
	default:	// [0x6000, 0xFFFF)
		return std::pair(std::ref(cartridge), addr - 0x6000);
	}
}







VMemBus::VMemBus(Memory & patternTables, Memory & nameTable0, Memory & nameTable1,
				 Memory & nameTable2, Memory & nameTable3, Memory & palette)
	: patternTables(patternTables)
	, nameTable0(nameTable0)
	, nameTable1(nameTable1)
	, nameTable2(nameTable2)
	, nameTable3(nameTable3)
	, palette(palette)
{
}

uint8_t VMemBus::read(uint16_t addr) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.read(pAddr);
}

uint8_t VMemBus::write(uint16_t addr, uint8_t val)
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

uint8_t VMemBus::write(uint16_t addr, uint8_t val) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

size_t VMemBus::size() const
{
	return 0x4000;
}

std::pair<Memory &, uint16_t> VMemBus::resolve(uint16_t addr) const
{
	switch ((addr & uint16_t(0b11u << 12u)) >> 12u)
	{
	case 0b00:
		return std::pair(std::ref(patternTables), addr & uint16_t(0b1'1111'1111'1111u));	// TODO: Check
	case 0b01:
		return std::pair(std::ref(patternTables), addr & uint16_t(0b1'1111'1111'1111u));	// TODO: Check
	case 0b11:
		if ((addr & uint16_t(0b1111u << 8u)) >> 8u == 0b1111u)
			return std::pair(std::ref(palette), addr & uint16_t(0b1'1111u));
		addr -= 0x1000u;
		[[fallthrough]];
	case 0b10:
		switch ((addr & uint16_t(0b11u << 10u)) >> 10u)
		{
		case 0b00:
			return std::pair(std::ref(nameTable0), addr & uint16_t(0b11'1111'1111u));
		case 0b01:
			return std::pair(std::ref(nameTable1), addr & uint16_t(0b11'1111'1111u));
		case 0b10:
			return std::pair(std::ref(nameTable2), addr & uint16_t(0b11'1111'1111u));
		case 0b11:
			return std::pair(std::ref(nameTable3), addr & uint16_t(0b11'1111'1111u));
		default:
			return std::pair(std::ref(patternTables), 0);
		}
	default:
		return std::pair(std::ref(patternTables), 0);
	}
}
