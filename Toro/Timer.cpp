#include "Timer.h"
#include <iostream>

using namespace std;

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::incTime(double delta_t) {
	_elapsedTime += delta_t;
}

bool Timer::expirated() {
	double time = MS;
	return (_elapsedTime >= time) ? true : false;
}
