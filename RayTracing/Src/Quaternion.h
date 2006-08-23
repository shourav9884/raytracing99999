#pragma once

#include "Vector3D.h"
#include <cmath>

class Quaternion
{
private:
	double realPart;
	Vector3D purePart;

	
public:
	inline Quaternion( )
		: realPart(0.0), purePart(0,1,0)
	{
	}

	inline Quaternion( double aRealPart, const Vector3D &aPurePart )
		: realPart(aRealPart), purePart(aPurePart)
	{
	}

	inline Quaternion operator +( const Quaternion &aQuaternion )
	{
		return Quaternion(this->realPart + aQuaternion.realPart, this->purePart + aQuaternion.purePart);
	}

	inline Quaternion operator *( const Quaternion &aQuaternion )
	{
		Quaternion result;

		result.realPart = (this->realPart * aQuaternion.realPart) - (this->purePart.dotProduct(aQuaternion.purePart));
		result.purePart = ( aQuaternion.purePart * this->realPart) + 
						  (this->purePart * aQuaternion.realPart) + 
						  (this->purePart.crossProduct(aQuaternion.purePart));

		return result;
	}

	inline Quaternion operator *( const Vector3D &aPureQuaternion )
	{
		Quaternion result = (*this) * Quaternion(0,aPureQuaternion);

		return result;
	}

	inline Quaternion conjugate( )
	{
		Vector3D invertedVector = this->purePart;
		invertedVector.invertDirection();

		Quaternion result(this->realPart, invertedVector);

		return result;
	}

	inline Vector3D rotate( const Vector3D &aVector ) 
	{
		Vector3D result;

		Quaternion tempQuaternion = (*this);
		tempQuaternion.purePart.normalize();
		tempQuaternion.purePart = tempQuaternion.purePart * sin(this->realPart/2);
		tempQuaternion.realPart = cos(this->realPart/2);
		
		Quaternion conjugatedTempQuaternion = tempQuaternion.conjugate();

		result = ( tempQuaternion * (Quaternion(0, aVector) * conjugatedTempQuaternion)).purePart;

		return result;
	}

};
