/*
 * ObjectContainer.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "ObjectContainer.h"

ObjectContainer::ObjectContainer() {
	objects = new map_UID_pObject();
	lights = new map_UID_lights();
}

ObjectContainer::~ObjectContainer() {
	for(auto i = objects->begin(); i != objects->end(); ++i)
		delete i->second;
	delete objects;

	for(auto i = lights->begin(); i != lights->end(); ++i)
		delete i->second;
	delete lights;
}

