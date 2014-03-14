#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

#include "Vectorf.h"

class Camera
{
    public:

		void updatePosition(Vector3f target);
		void setVision();
		void setStaticVision();
	    void reset();
		void setPosition(Vector3f pos);
        float distanceFromCenter;
        Vector3f lastPosition;
        Vector3f position;
        Vector3f lookPoint;
        Vector3f verticalTurn;
        Vector3f verticalTurnToReach;
        Vector3f rotate;
        Vector3f positionToReach;
        float scale;
        Camera();

    protected:
    private:
        static bool firstUpdate;


};

#endif // CAMERA_H
