/*
 * TerrainBlock.h
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#ifndef TERRAINBLOCK_H_
#define TERRAINBLOCK_H_

#include "Object.h"

namespace Objects {

	class TerrainBlock : public Object{
	public:
		TerrainBlock();
		virtual ~TerrainBlock();

		void getMessage(Message* msg);
		void update(int elapsedTime);

		UID brickModelID;
		UID leftTextureID;
		UID frontTextureID;
		UID rightTectureID;
		UID upperTextureID;
	};

}
#endif /* TERRAINBLOCK_H_ */
