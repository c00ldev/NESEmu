#include "nes.h"

#include "null_memory.h"

#include <functional>

NES::NES()
	: clock(21.477272_MHz)
	, ctrl()
	, bus()
	, vbus()
	, cpu(ctrl, bus)
	, ppu(ctrl, vbus)
	, ram(0x800)
	, vram(0x800)
	, cartridgeSlot()
{
	clock.addHandler(12, [this]{ cpu.tick(); memMap(); });
	clock.addHandler(4, [this]{ ppu.tick(); vmemMap(); });

	ram.write(0x00, 0x69);
	ram.write(0x01, 1);
}

//void NES::run()
//{
//	clock.cycle();
//}

//void NES::setCartridge(Cartridge * cartridge)
//{
//	cartridgeSlot.setCartridge(cartridge);
//}

void NES::memMap()
{
	if (!bus.enable)
		return;
	auto [mem, address] = resolveCPU(bus.address);
	if (bus.write && !ctrl.reset)
		mem.write(address, bus.data);
	else
		bus.data = mem.read(address);
}

void NES::vmemMap()
{
	if (!vbus.enable)
		return;
	auto [mem, address] = resolvePPU(vbus.address);
	if (vbus.write)
		mem.write(address, vbus.data);
	else
		vbus.data = mem.read(address);
}

std::pair<Memory &, uint16_t> NES::resolveCPU(uint16_t address)
{
	if (address >= 0x6000)
		return std::pair(std::ref(cartridgeSlot.getPRG()), address - 0x6000);
	if (address >= 0x4020)
		return std::pair(std::ref(cartridgeSlot.getEXP()), address - 0x4020);
	if (address >= 0x4000)
		return std::pair(std::ref(NullMemory::nullMemory), address - 0x4000);
	if (address >= 0x2000)
		return std::pair(std::ref(ppu.getRegs()), address & 0b111);
	return std::pair(std::ref(ram), address & 0b111'1111'1111);
}

std::pair<Memory &, uint16_t> NES::resolvePPU(uint16_t address)
{
	return std::pair(std::ref(vram), address & 0b0000'1111'1111'1111);
}
