#include <iostream>

#include "nes.h"

#include "i_nes.h"

int main()
{
	NES nes;
	iNES rom;
	rom.load("M:\\Downloads\\NES Tests\\cpu_dummy_reads.nes");
	Cartridge * cartridge = rom.getCartridge();
	nes.setCartridge(cartridge);
	while (true)
		nes.run();
//	uint8_t a = nes.mmu.read(0x4020);
//	nes.mmu.read(0x6000);
	return 0;

//	NES nes;
//	nes.mmu.write(0x2008, 100);
//	nes.clock.run();
//	return 0;

//	bool running = true;
//	while (running)
//	{
//
//	}
}