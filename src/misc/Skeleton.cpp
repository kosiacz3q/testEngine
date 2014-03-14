/*
 * Skeleton.cpp
 *
 *  Created on: 27 Jan 2014
 *      Author: lucas
 */


#include "Skeleton.h"
#include  <algorithm>

namespace Resource {

Skeleton::Skeleton() {

	LCMofAnimTimes = 0;
	mountPoints = new map_UID_pvpipf();
	centerX = 0;


}

Skeleton::~Skeleton() {
	delete mountPoints;
}


Vector4f Skeleton::getMountPoint(UID bodyPart, int side , int time){

		vpipf::iterator iter = std::lower_bound( (*mountPoints)[bodyPart]->begin(),
												 (*mountPoints)[bodyPart]->end() ,
												 time % (LCMofAnimTimes + 1) + 1,
												 []( const pipf& right , const int t ){ return right.first < t; } );

		if( iter == (*mountPoints)[bodyPart]->end())
			--iter;

		Vector4f result(iter->second);

		if(side == 1){
			result.x = centerX + (centerX - result.x);
		}

		return result;
}

}
