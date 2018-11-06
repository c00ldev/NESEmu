#pragma once

#include "memory.h"

struct MemBus
{
	uint16_t address;
	uint8_t data;
	bool write;
	bool enable;
public:
	MemBus();
};
