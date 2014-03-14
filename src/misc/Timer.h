/*
 * Timer.h
 *
 *  Created on: Jan 20, 2014
 *      Author: lucas
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <ctime>

class Timer {
public:
	Timer();
	virtual ~Timer();

	std::clock_t timingStart;
	std::clock_t lastMeasurement;

	int getMSTimeElapsedSinceLastMeasurement();
	int getNonZeroMSTimeElapsedSinceLastMeasurement();
};


#endif /* TIMER_H_ */
