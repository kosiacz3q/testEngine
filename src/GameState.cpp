/*
 * GameState.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "GameState.h"

GameState::GameState() {
	actualScene = nullptr;
	resources = new ResourcesManager();
	cameraTarget = 0;


}

GameState::~GameState() {
	for(auto i = scenes.begin(); i != scenes.end(); ++i)
		delete i->second;

	delete resources;

}

void GameState::chagneActual(UID newSceneID){
	this->actualScene = scenes[newSceneID];
}
