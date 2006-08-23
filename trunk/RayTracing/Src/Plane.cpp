#include "Plane.h"

Plane::Plane(void)
: vector(Vector3D::UNIT_Y)
{
}

Plane::Plane( const Vector3D &aVector, const Vector3D &aPoint )
: vector(aVector), Object3D(aPoint)
{
}

Plane::~Plane(void)
{
}

////////////////////////////////////////////////////////////////////////////////
// t = (-a.(xv-xo)-b.(yv-yo)-c.(zv-zo))/(a.av + b.bv + c.cv)
////////////////////////////////////////////////////////////////////////////////
double Plane::checkIntersection( const Ray& aRay )
{
	double result = -1;	

	if( !this->isParallel(aRay.vector) )
	{
		double denominator = aRay.vector.dotProduct(this->vector);

		Vector3D invertedVector = this->vector;
		invertedVector.invertDirection();

		double numerator = (aRay.point - this->worldPosition).dotProduct( invertedVector );

		result  = numerator/denominator;
	}

	return result;
}

Vector3D Plane::getNormalVector( const Vector3D &aPoint, double t )
{
	return this->vector;
}

Vector2D Plane::getTextureUVCoordinates( const Vector3D &aIntersectionPoint, const Vector3D &aNormalVector )
{
	Vector2D result;

	return result;
}