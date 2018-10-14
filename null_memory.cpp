#include "null_memory.h"


NullMemory NullMemory::nullMemory;

uint8_t NullMemory::read(uint16_t addr) const
{
	return 0;
}

uint8_t NullMemory::write(uint16_t addr, uint8_t val)
{
	return 0;
}

uint8_t NullMemory::write(uint16_t addr, uint8_t val) const
{
	return 0;
}

size_t NullMemory::size() const
{
	return 0;
}
