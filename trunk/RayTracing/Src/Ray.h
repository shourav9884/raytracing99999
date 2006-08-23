#pragma once

#include "Vector3D.h"
#include <cmath>

class Ray
{
public: // Atributos
	Vector3D vector;
	Vector3D point;

public:
	inline Ray( void )
		: vector(Vector3D::UNIT_X)
	{
	}

	inline Ray( const Vector3D &aVector, const Vector3D &aPoint)
		: vector(aVector), point(aPoint)
	{
	}

	inline Ray( const Ray &aRay )
		: vector(aRay.vector), point(aRay.point)
	{
	}

	inline Ray( const Ray *aRay )
		: vector(aRay->vector), point(aRay->point)
	{
	}

	inline double getTOfPoint( const Vector3D &aPoint )
	{
		double result = 0.0;

		double xVectorAbs = fabs(this->vector.x);
		double yVectorAbs = fabs(this->vector.y);
		double zVectorAbs = fabs(this->vector.z);

		if( xVectorAbs > yVectorAbs && xVectorAbs > zVectorAbs )
		{
			result = (aPoint.x - this->point.x) / this->vector.x;
		}
		else if(yVectorAbs > xVectorAbs && yVectorAbs > zVectorAbs )
		{
			result = (aPoint.y - this->point.y) / this->vector.y;
		}
		else //if(zVectorAbs > xVectorAbs && zVectorAbs > yVectorAbs )
		{
			result = (aPoint.z - this->point.z) / this->vector.z;
		}

		return result;
	}


};
