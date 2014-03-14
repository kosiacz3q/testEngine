/*
 * ObjectContainer.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef OBJECTCONTAINER_H_
#define OBJECTCONTAINER_H_

#include <vector>
#include <map>
#include "LightSource.h"

typedef std::map<UID , Objects::Object*> map_UID_pObject;
typedef std::vector<UID> vector_objectUID;
typedef std::map<UID , Objects::LightSource*> map_UID_lights;

class ObjectContainer {
public:
	map_UID_pObject* objects;
	vector_objectUID objectsForCollisionCheck;
	map_UID_lights* lights;


	ObjectContainer();
	virtual ~ObjectContainer();
};

#endif /* OBJECTCONTAINER_H_ */
