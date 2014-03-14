/*
 * Scene.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "Scene.h"

Scene::Scene() {
	objectContainer = new ObjectContainer();
	camera = new Camera();
}

Scene::~Scene() {
	delete objectContainer;
	delete camera;
}

