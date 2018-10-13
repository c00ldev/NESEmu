#include "nes.h"

NES::NES()
	: clock(21.477272_MHz)
	, ram(0x800)
	, cpu(mem)
	, ppu(vmem)
	, mem(ram, ppu.getRegs(), ram, cartridgeSlot, cartridgeSlot)
	, vmem(ram, ram, ram, ram, ram, ram, ram)
	, cartridgeSlot(nullptr)
{
	clock.addHandler(12, [this]{ cpu.tick(); });
//	clock.addHandler(4, [this]{ ppu.tick(); });
//	mmu.map(0x0000, ram);
//	mmu.map(0x2000, ppu.getRegs());
//	mmu.map(0x4020, cartridgeSlot);
}

void NES::powerUp()
{
	cpu.powerUp();
}

void NES::run()
{
	clock.cycle();
}

void NES::setCartridge(Cartridge * cartridge)
{
	cartridgeSlot.setCartridge(cartridge);
}
