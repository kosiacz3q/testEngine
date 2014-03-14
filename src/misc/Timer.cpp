/*
 * Timer.cpp
 *
 *  Created on: Jan 20, 2014
 *      Author: lucas
 */

#include "Timer.h"


Timer::Timer() {
	timingStart = lastMeasurement = std::clock();
}

Timer::~Timer() {

}

int Timer::getMSTimeElapsedSinceLastMeasurement(){
	std::clock_t newMeas;
	int stamp = ( (newMeas = std::clock()) - lastMeasurement) / (double)(CLOCKS_PER_SEC / 1000);

	if(stamp != 0)
		lastMeasurement = newMeas;

	return stamp;
}

int Timer::getNonZeroMSTimeElapsedSinceLastMeasurement(){

	std::clock_t newMeas;
	int stamp = ( (newMeas = std::clock()) - lastMeasurement) / (double)(CLOCKS_PER_SEC / 1000);
	while(stamp == 0 ){
		stamp = ( (newMeas = std::clock()) - lastMeasurement) / (double)(CLOCKS_PER_SEC / 1000);
	}
	lastMeasurement = newMeas;
	return stamp;

}


