#pragma once

#include "memory.h"

class RegPtr : public Memory
{
	uint8_t * reg;
	size_t size_;
public:
	RegPtr(uint8_t * reg, size_t size);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
};
