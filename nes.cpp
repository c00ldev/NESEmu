#include "nes.h"

NES::NES()
	: clock(21477272)
	, ram(0x800)
	, cpu(mem)
	, ppu(vmem)
	, mem(ram, ppu.getRegs(), ram, cartridgeSlot, cartridgeSlot)
	, vmem(ram, ram, ram, ram, ram, ram, ram)
	, cartridgeSlot(nullptr)
{
	clock.addHandler(cpu, 12);
	clock.addHandler(ppu, 4);
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
	clock.run();
}

void NES::setCartridge(Cartridge * cartridge)
{
	cartridgeSlot.setCartridge(cartridge);
}
