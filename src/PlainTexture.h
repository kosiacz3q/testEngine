/*
 * PlainTexture.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef PLAINTEXTURE_H_
#define PLAINTEXTURE_H_
#include "Object.h"

namespace Objects{

	class PlainTexture : public Object{
	public:

		PlainTexture();
		virtual ~PlainTexture();

		void getMessage(Message* msg);
		void update(int elapsedTime);

		UID textureUID;
	};

}

#endif /* PLAINTEXTURE_H_ */
