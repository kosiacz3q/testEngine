/*
 * Scene.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "misc/Camera.h"

#include "MessagesHandler.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	ObjectContainer* objectContainer;
	Camera* camera;
};

#endif /* SCENE_H_ */
