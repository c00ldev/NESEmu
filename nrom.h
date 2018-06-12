#pragma once

#include "ram.h"

class NROM
{
	ROM prg_rom;
public:
	Memory & getPRGROM();
};
