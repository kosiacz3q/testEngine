/*
 * StaticLightSource.h
 *
 *  Created on: Jan 21, 2014
 *      Author: lucas
 */

#ifndef STATICLIGHTSOURCE_H_
#define STATICLIGHTSOURCE_H_

#include "Object.h"

#include <GL/gl.h>
#include <map>

namespace Objects {

typedef std::map<GLenum , bool> map_GLenum_bool;

class LightSource: public Objects::Object {
public:
	LightSource();
	virtual ~LightSource();

	GLfloat lightPosition[4]; //same as Object->position
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat spotDirection[3];
	GLfloat spotExponent;
	GLfloat spotCutoff;

	void getMessage(Message* msg);
	void update(int);
};

}
#endif /* STATICLIGHTSOURCE_H_ */
