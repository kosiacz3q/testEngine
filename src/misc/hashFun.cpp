/*
 * hashFun.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#include "hashFun.h"

unsigned int hashFunFromString(std::string toHash){
   unsigned int h = 31; /* also prime */

   for(auto iter = toHash.begin(); iter != toHash.end(); ++iter){
     h = (h * 54059) ^ (*iter * 76963);
   }

   return h;
}

unsigned int hashFun(const char* toHash){
   unsigned int h = 31; /* also prime */
   int length = strlen(toHash) ;

   for(int i = 0; i < length; ++i)
	   h = (h * 54059) ^ (toHash[i] * 76963);

   return h;
}
