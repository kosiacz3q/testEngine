/*
 * TypeHandlers.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#include "TypeHandlers.h"

double toReal(const char* c){

	std::stringstream str;

    str << c;

    double x;
    str >> x;

    return x;

}

