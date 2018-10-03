#include "nes.h"

NES::NES()
	: clock(21477272)
	, ram(0x800)
	, cpu(mem)
	, ppu()
	, mem(ram, ppu.getRegs(), ram, cartridgeSlot, cartridgeSlot)
	, cartridgeSlot(nullptr)
{
	clock.addHandler(cpu, 12);
//	mmu.map(0x0000, ram);
//	mmu.map(0x2000, ppu.getRegs());
//	mmu.map(0x4020, cartridgeSlot);
}

void NES::run()
{
	clock.run();
}

void NES::setCartridge(Cartridge * cartridge)
{
	cartridgeSlot.setCartridge(cartridge);
}
