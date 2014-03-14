/*
 * hashFun.h
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#ifndef HASHFUN_H_
#define HASHFUN_H_

#include <string.h>
#include <string>

unsigned int hashFunFromString(std::string toHash);

unsigned int hashFun(const char* toHash);

#endif /* HASHFUN_H_ */
