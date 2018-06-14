#include <iostream>

#include "nes.h"

int main()
{
	NES nes;
	nes.mmu.write(0x2008, 100);
	nes.clock.run();
	return 0;
//	bool running = true;
//	while (running)
//	{
//
//	}
}