/*
 * Doll.cpp
 *
 *  Created on: 27 Jan 2014
 *      Author: lucas
 */

#include "Doll.h"

namespace Objects {

Doll::Doll()
	:Object(ObjectType::DOLL){
	actualSkeletonID = 0;
	movementElapsedTime = 0;
	bodyParts = new map_bodyPartUID_pair_animationUID_vector2f();
}

Doll::~Doll() {
	delete bodyParts;
}

void Doll::getMessage(Message* msg){

}

void Doll::update(int time){
	movementElapsedTime += time;
}

} /* namespace Objects */
