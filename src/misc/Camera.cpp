#include "Camera.h"
#include <math.h>



void Camera::reset(){
	position.reset();
	positionToReach.reset();
	verticalTurnToReach.reset();
	verticalTurnToReach.y = 1.;
	lookPoint.reset();
	verticalTurn.reset();
	verticalTurn.y = 1.;
	rotate.reset();
	lastPosition.reset();
}

void Camera::updatePosition(Vector3f target){

	if(!(position == positionToReach)){
		float tmp = position.z;
		Vector3f::moveCloseToVector(target, position , 0.1);
		position.z = tmp;
		positionToReach.smooth( lastPosition , 0.001 );
	}
}

void Camera::setVision(){
    gluLookAt( position.x , position.y, position.z ,
               lookPoint.x , lookPoint.y , lookPoint.z,
               verticalTurn.x , verticalTurn.y , verticalTurn.z);

   glRotatef(Camera::rotate.x , 0. , 1. , 0.);
   glRotatef(Camera::rotate.y , 1. , 0. , 0.);
   glRotatef(Camera::rotate.z , 0. , 0. , 1.);

   glScaled(scale , scale , scale);
}

void Camera::setStaticVision(){
	gluLookAt(0 ,0, 3,
		   0 , 0 , 0,
		   0 , 1. , 0);
}

void Camera::setPosition(Vector3f pos){
	position = pos;
	positionToReach = pos;
}

Camera::Camera(){
	 position = Vector3f( 0. , 0. , 0.);
	 positionToReach = Vector3f( 0. , 0. , 0.);
	 verticalTurnToReach = Vector3f(0. , 1. , 0.);
	 lookPoint = Vector3f( 0. , 0. , 0.);
	 verticalTurn = Vector3f( 0. ,  1. , 0.);
	 rotate = Vector3f(0. , 0. , 0.);
	 lastPosition = Vector3f(0. , 0. , 0.);
	 distanceFromCenter = 3;
	 scale = 1;
}
