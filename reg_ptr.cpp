#include "reg_ptr.h"


RegPtr::RegPtr(uint8_t * reg, size_t size)
	: reg(reg)
	, size_(size)
{

}

uint8_t RegPtr::read(uint16_t addr) const
{
	return reg[addr % size_];
}

uint8_t RegPtr::write(uint16_t addr, uint8_t val)
{
	return reg[addr % size_] = val;
}

uint8_t RegPtr::write(uint16_t addr, uint8_t val) const
{
	return read(addr);
}

size_t RegPtr::size() const
{
	return size_;
}
