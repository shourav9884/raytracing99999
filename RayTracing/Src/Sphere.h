#pragma once

#include "Object3D.h"

class Sphere : public Object3D
{
private:
	float radius;

private:
	Vector3D getNormalVector( const Vector3D &aPoint, double t );

	Vector2D getTextureUVCoordinates( const Vector3D &aIntersectionPoint, const Vector3D &aNormalVector );

public:
	Sphere( void );
	Sphere( float aRadius, const Vector3D &aPosition = Vector3D(Vector3D::ZERO) );

	double checkIntersection( const Ray& aRay );
};
