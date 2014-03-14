/*
 * Skeleton.h
 *
 *  Created on: 27 Jan 2014
 *      Author: lucas
 */

#ifndef SKELETON_H_
#define SKELETON_H_

#include <utility>
#include <map>
#include <vector>
#include "Vectorf.h"

typedef unsigned int UID;

typedef std::pair<int , float*> pipf;
typedef std::vector<pipf> vpipf;
typedef std::map<UID, vpipf*> map_UID_pvpipf;

namespace Resource {

class Skeleton {
public:
	Skeleton();
	virtual ~Skeleton();

	int LCMofAnimTimes;
	int centerX;

	map_UID_pvpipf* mountPoints;

	Vector4f getMountPoint(UID bodyPart, int side , int time);


private :

};

} /* namespace Resource */
#endif /* SKELETON_H_ */
