/*
 * Object.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "Object.h"

namespace Objects{
	MessagesHandler* Object::msgHandler = nullptr;

	Object::Object(ObjectType::objectType type){
		this->type = type;
		this->position = Vector3f(0,0,0);
		this->visible = true;
		this->rotation = Vector3f(0,0,0);
	}

	Object::~Object() {

	}

}
