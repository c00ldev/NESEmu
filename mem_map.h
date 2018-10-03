#pragma once

#include "memory.h"

#include <list>
#include <utility>

class MemMap : public Memory
{
	std::list<std::pair<uint16_t, Memory &>> map_;
public:
	~MemMap() override = default;
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
protected:
	std::pair<Memory &, uint16_t> resolve(uint16_t addr) const;
public:
	void map(uint16_t addr, Memory & mem);
};
