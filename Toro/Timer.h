#pragma once

#define MS 5000.0;

class Timer
{
private:
	double _elapsedTime = 0.0;
public:
	Timer();
	virtual ~Timer();
	void incTime(double delta_t);
	bool expirated();
};

