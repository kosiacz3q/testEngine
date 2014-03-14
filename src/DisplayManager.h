/*
 * DisplayManager.h
 *
 *  Created on: 26 Jan 2014
 *      Author: lucas
 */

#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_

#include <GL/gl.h>
#include "Scene.h"
#include "ResourcesManager.h"

#include "GameState.h"
#include "PlainTexture.h"
#include "TerrainBlock.h"
#include "PlainAnimation.h"
#include "LightSource.h"
#include "Doll.h"
#include "misc/Colors.h"


class DisplayManager {
public:
	bool availableLights[8];
	GLenum lightID[8];


	void display(Scene* , ResourcesManager* );

	DisplayManager();
	virtual ~DisplayManager();
};

#endif /* DISPLAYMANAGER_H_ */
