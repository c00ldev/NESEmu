#include "nes.h"

#include "null_memory.h"

NES::NES()
	: ctrl()
	, clock(21.477272_MHz)
	, bus()
	, vbus()
	, ram(0x800)
	, vram(0x800)
	, cpu(ctrl, bus)
	, cartridgeSlot()
{
	clock.addHandler(12, [this]{ cpu.tick(); });
	clock.addHandler(12, [this]{ memMap(); vmemMap(); });
}

void NES::run()
{
	clock.cycle();
}

void NES::setCartridge(Cartridge * cartridge)
{
	cartridgeSlot.setCartridge(cartridge);
}

void NES::memMap()
{
	if (!bus.enable)
		return;
	if (bus.write)
		ram.write(bus.address, bus.data);
	else
		bus.data = ram.read(bus.address);
}

void NES::vmemMap()
{
	if (!vbus.enable)
		return;
	if (vbus.write)
		vram.write(vbus.address, vbus.data);
	else
		vbus.data = vram.read(vbus.address);
}
