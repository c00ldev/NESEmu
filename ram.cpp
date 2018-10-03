#include "ram.h"

#include <utility>


RAM::RAM(size_t memSize)
	: mem(memSize)
{

}

uint8_t RAM::read(uint16_t addr) const
{
	return mem[addr % size()];
}

uint8_t RAM::write(uint16_t addr, uint8_t val)
{
	return mem[addr % size()] = val;
}

uint8_t RAM::write(uint16_t addr, uint8_t val) const
{
	return mem[addr % size()];
}

size_t RAM::size() const
{
	return mem.size();
}


ROM::ROM(size_t memSize)
	: mem(memSize)
{

}

uint8_t ROM::read(uint16_t addr) const
{
	return mem[addr % size()];
}

uint8_t ROM::write(uint16_t addr, uint8_t val)
{
	return read(addr);
}

uint8_t ROM::write(uint16_t addr, uint8_t val) const
{
	return read(addr);
}

size_t ROM::size() const
{
	return mem.size();
}

void ROM::setContents(std::vector<uint8_t> contents)
{
	size_t s = size();
	mem = std::move(contents);
	mem.resize(s);
}
