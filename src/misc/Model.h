/*
 * Model.h
 *
 *  Created on: Jan 19, 2014
 *      Author: lucas
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Vectorf.h"

namespace Resource {

	class Model {
	public:
		Model();
		virtual ~Model();

		Vector3f vertices[8];

	};

} /* namespace Objects */
#endif /* MODEL_H_ */
