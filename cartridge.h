#pragma once

#include "memory.h"

enum class Mirroring
{
	Horizontal,
	Vertical,
	SingleScreen,
	FourScreen
};

class Cartridge
{
public:
	virtual ~Cartridge() = default;
	virtual Memory & getPRG() = 0;
	virtual Memory & getCHR() = 0;
	virtual Memory & getEXP() = 0;

//	virtual Memory & getNametable0() = 0;
//	virtual Memory & getNametable1() = 0;
//	virtual Memory & getNametable2() = 0;
//	virtual Memory & getNametable3() = 0;
};
