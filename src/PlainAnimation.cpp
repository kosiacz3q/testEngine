/*
 * PlainAnimation.cpp
 *
 *  Created on: Jan 20, 2014
 *      Author: lucas
 */
#include "PlainAnimation.h"

namespace Objects {

PlainAnimation::PlainAnimation()
	:Object(ObjectType::PLAIN_ANIMATION){
	elapsedTime = 0;
	duration_total = 0;
	duration_perFrame = 0;
	fixedStart = 0;
	textureID = 0;
}

PlainAnimation::~PlainAnimation() {

}

void PlainAnimation::getMessage(Message* msg){

}

void PlainAnimation::update(int elapsedTime){
	this->elapsedTime += elapsedTime;

	this->elapsedTime = this->elapsedTime % duration_total;
}

} /* namespace Objects */
