#pragma once

#include <array>
#include <vector>
#include <cstddef>

struct InstructionDecoder
{
	static const std::array<std::vector<size_t>, 0x108> instructions;
};
