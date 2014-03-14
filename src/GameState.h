/*
 * GameState.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "ResourcesManager.h"
#include "Scene.h"

typedef std::map<UID , Scene*> map_UID_scene;

class GameState {
public:
	GameState();
	virtual ~GameState();

	ResourcesManager *resources;
	Scene *actualScene;
	map_UID_scene scenes;
	UID cameraTarget;


	void chagneActual(UID newSceneID);

};

#endif /* GAMESTATE_H_ */
