#pragma once

#include "Camera.h"

typedef char CameraVector;

class CameraController
{
private:
	Camera *camera;

public:
	CameraController(void);
	~CameraController(void);

	void setCamera( Camera *aCamera )
	{
		this->camera = aCamera;
	}

	Camera *getCamera()	
	{
		return this->camera;
	}
	
public: // Callbacks
	void moveOverVector( float aOffset, CameraVector aVector );
	void rotateAroundVector( float aDegree, CameraVector aVector );

	const static CameraVector VECTOR_U = 0;
	const static CameraVector VECTOR_V = 1;
	const static CameraVector VECTOR_N = 2;
};
