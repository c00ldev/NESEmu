#include "nes.h"

#include "null_memory.h"

NES::NES()
	: clock(21.477272_MHz)
	, ram(0x800)
	, vram(0x800)
	, cpu(mem)
	, ppu(vmem)
	, cartridgeSlot(nullptr)
	, mem(ram, ppu.getRegs(), ram, cartridgeSlot.getPRG(), cartridgeSlot.getEXP())
	, vmem(cartridgeSlot.getCHR(), NullMemory::nullMemory, NullMemory::nullMemory, NullMemory::nullMemory, NullMemory::nullMemory, ppu.getPalettes())
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
	size_t count = cpu.getCycleCount();
	clock.cycle(12 * count);
}

void NES::setCartridge(Cartridge * cartridge)
{
	cartridgeSlot.setCartridge(cartridge);
}
