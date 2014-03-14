/*
 * StaticLightSource.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: lucas
 */

#include "LightSource.h"

namespace Objects {

LightSource::LightSource()
	:Object(Objects::ObjectType::LIGHT_SOURCE){
	spotExponent = 0;
	spotCutoff = 180;

}

LightSource::~LightSource() {

}

void LightSource::getMessage(Message* msg){

}

void LightSource::update(int){

}

}
