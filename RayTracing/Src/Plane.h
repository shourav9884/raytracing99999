#pragma once

#include "Object3D.h"
#include "Vector3D.h"
#include "Ray.h"

class Plane : public Object3D
{
private:
	Vector3D vector;
	// O ponto (View e World position) é herdado da Object3D que herda do SceneObject

private:
	Vector3D getNormalVector( const Vector3D& aPoint, Vector2D aTextureUVCoordinates );

	Vector2D getTextureUVCoordinates( const Vector3D& aIntersectionPoint);

public:
	Plane(void);
	Plane( const Vector3D &aVector, const Vector3D &aPoint );
	~Plane(void);

	double checkIntersection( const Ray& aRay );

	// É paralelo quando os vetores sao ortogonais
	inline bool isParallel(const Vector3D &aVector)
	{
		double value = aVector.dotProduct(this->vector);

		if( value > 0.00000000001 || value < -0.00000000001 )
			return false;
		else 
			return true;
	}

	inline const Vector3D &getVector( ) const
	{
		return this->vector;
	}
};
