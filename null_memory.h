#pragma once

#include "memory.h"

class NullMemory : public Memory
{
public:
	static NullMemory nullMemory;
public:
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
};
