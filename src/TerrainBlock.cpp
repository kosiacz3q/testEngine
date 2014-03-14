/*
 * TerrainBlock.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#include "TerrainBlock.h"

namespace Objects {

	TerrainBlock::TerrainBlock()
		:Object(ObjectType::TERRAIN_BLOCK){
		brickModelID = 0;

		leftTextureID = 0;
		rightTectureID = 0;
		frontTextureID = 0;
		upperTextureID = 0;

	}

	TerrainBlock::~TerrainBlock() {

	}

	void TerrainBlock::getMessage(Message* msg){

	}

	void TerrainBlock::update(int elapsedTime){

	}
}
