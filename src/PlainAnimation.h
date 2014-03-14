/*
 * PlainAnimation.h
 *
 *  Created on: Jan 20, 2014
 *      Author: lucas
 */

#ifndef PLAINANIMATION_H_
#define PLAINANIMATION_H_

#include "Object.h"

namespace Objects {

	class PlainAnimation : public Object {
	public:
		PlainAnimation();
		virtual ~PlainAnimation();

		void getMessage(Message* msg);
		void update(int elapsedTime);

		UID textureID ;
		int elapsedTime;
		int duration_total;
		int duration_perFrame;
		int fixedStart;
	};

} /* namespace Objects */
#endif /* PLAINANIMATION_H_ */
