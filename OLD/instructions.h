#pragma once

#include <array>
#include <functional>

class CPU;

class Instructions
{
	static std::array<std::function<void(CPU &)>, 0x108> table;
public:
	void operator()(uint16_t opcode, CPU & cpu);
};
