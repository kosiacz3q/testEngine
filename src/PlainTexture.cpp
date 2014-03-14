/*
 * PlainTexture.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "PlainTexture.h"

namespace Objects{

PlainTexture::PlainTexture()
	:Object(ObjectType::PLAIN_TEXTURE){

	textureUID = -1;
}

PlainTexture::~PlainTexture() {

}

void PlainTexture::getMessage(Message* msg){

}

void PlainTexture::update(int elapsedTime){

}

}
