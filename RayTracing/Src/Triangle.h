#pragma once

#include "Object3D.h"
#include "Vector3D.h"

class Triangle : public Object3D
{
private:
	Vector3D pointA;
	Vector3D pointB;
	Vector3D pointC;

public:
	Triangle( void );

	void checkIntersection( const Ray &aRay, IntersectionResult &aResult );
};
