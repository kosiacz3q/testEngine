/*
 * Object.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class MessagesHandler;

#include "msg/Message.h"
#include "misc/Vectorf.h"

namespace Objects{

	namespace ObjectType{
		enum objectType{
			ACTOR = 0,
			PLAIN_TEXTURE,
			TERRAIN_BLOCK,
			PLAIN_ANIMATION,
			LIGHT_SOURCE,
			DOLL,
		};
	}

	class Object {
	public:
		Object(ObjectType::objectType type);

		virtual ~Object();
		virtual void getMessage(Message* msg) = 0;
		virtual void update(int) = 0;

		ObjectType::objectType type;
		Vector3f position;
		Vector2f dimensions;
		Vector3f rotation;
		bool visible;

		static MessagesHandler* msgHandler;
	};

}
#endif /* OBJECT_H_ */
