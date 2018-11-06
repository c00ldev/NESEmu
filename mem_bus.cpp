#include "mem_bus.h"

#include <functional>


MemBus::MemBus()
	: address(0)
	, data(0)
	, write(false)
	, enable(false)
{
}
