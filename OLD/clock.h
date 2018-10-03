#pragma once

#include "tickable.h"

#include <chrono>
#include <forward_list>
#include <functional>
#include <tuple>

class Clock : public Tickable
{
	using clock_type = std::chrono::steady_clock;
	clock_type clock;
	long double period;
	double dutyCycle;
	size_t ticks;
public:
	using fn_type = std::function<void(Tickable &)>;
private:
	std::forward_list<std::tuple<size_t, Tickable &>> handlers;
public:
	Clock(long double frequency, double dutyCycle = 0.5);
	void start();
	bool run();
	void addHandler(size_t onTick, Tickable & object);
public:
	void tick() override;
	void tick_down() override;
};
