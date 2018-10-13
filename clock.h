#pragma once

#include "tickable.h"

#include <list>
#include <utility>
#include <cstddef>

class Clock
{
	std::list<std::pair<size_t, Tickable &>> handlers;
	long double period;
	size_t ticks;
public:
	explicit Clock(long double frequency);
	void tick();
	void run();
	void addHandler(Tickable & tickable, size_t onTick = 1u);
	void addHandler(long double freq, Tickable & tickable);
};
