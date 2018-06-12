#include <iostream>

#include "nes.h"

int main()
{
	NES nes;
	nes.mmu.write(0, 0x65);
	nes.mmu.write(1, 100);
	nes.mmu.write(100, 10);
	nes.cpu.tick();
	nes.mmu.read(0);
}