/*
 * Doll.h
 *
 *  Created on: 27 Jan 2014
 *      Author: lucas
 */

#ifndef DOLL_H_
#define DOLL_H_

#include "Object.h"
#include <map>
#include <utility>

namespace Objects {

typedef std::pair<UID , Vector2f> pair_UID_vector2f;
typedef std::map<UID , pair_UID_vector2f> map_bodyPartUID_pair_animationUID_vector2f;

class Doll: public Objects::Object {
public:
	Doll();
	virtual ~Doll();

	UID actualSkeletonID;
	int movementElapsedTime;

	map_bodyPartUID_pair_animationUID_vector2f* bodyParts; //animations

	void getMessage(Message* msg) ;
	void update(int) ;
};

}
#endif /* DOLL_H_ */
