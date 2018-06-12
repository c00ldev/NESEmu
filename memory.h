#pragma once

#include <cstdint>
#include <cstddef>

class Memory
{
public:
	virtual ~Memory() = default;
	virtual uint8_t read(uint16_t addr) const = 0;
	virtual uint8_t write(uint16_t addr, uint8_t val) = 0;
	virtual uint8_t write(uint16_t addr, uint8_t val) const = 0;
	virtual size_t size() const = 0;
};
