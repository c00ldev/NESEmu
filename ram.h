#pragma once

#include "memory.h"

#include <vector>

class RAM : public Memory
{
	std::vector<uint8_t> mem;
public:
	RAM(size_t memSize);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
};

class ROM : public Memory
{
	std::vector<uint8_t> mem;
public:
	ROM(size_t memSize);
	uint8_t read(uint16_t addr) const override;
	uint8_t write(uint16_t addr, uint8_t val) override;
	uint8_t write(uint16_t addr, uint8_t val) const override;
	size_t size() const override;
	void setContents(std::vector<uint8_t> contents);
};
