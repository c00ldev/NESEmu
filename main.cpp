#include <iostream>
#include <iomanip>

#include "nes.h"

#include "i_nes.h"

int main()
{
	NES nes;
	iNES rom;
	rom.load("M:\\Downloads\\NES Tests\\nestest.nes");
	Cartridge * cartridge = rom.getCartridge();
	nes.setCartridge(cartridge);
	nes.powerUp();
//	std::cout << std::hex << std::setfill('0') << std::uppercase;
//	std::cin >> std::hex;
//	for (uint16_t addr = 0; (size_t)addr < 0x10000; addr += 0x10)
//	{
//		std::cout << "0x" << std::setw(4) << addr << ":\t";
//		for (size_t i = 0; i < 16; ++i)
//		{
//			uint16_t b = nes.mem.read(addr + i);
//			std::cout << std::setw(2) << b << " ";
//		}
//		std::cout << "\n";
//	}

	for (;;)
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