#pragma once

#include "Object3D.h"
#include "Vector3D.h"
#include "Plane.h"

class Box :	public Object3D
{
private:
	struct PairOfPlanes
	{
		Plane p1;
		Plane p2;
	};

private:
	Vector3D Bl;
	Vector3D Bh;

	// Planos
	PairOfPlanes pairsOfPlanes[3];

	// Armazenará o plano que foi intersectado desde a ultima vez q
	// o checkintersection foi chamado
	Plane *planeIntersected;

private:
	inline void updatePlanes( )
	{
		this->pairsOfPlanes[0].p1 = Plane(Vector3D(-1,0,0), Vector3D(Bl.x,0,0));
		this->pairsOfPlanes[0].p2 = Plane(Vector3D(1,0,0), Vector3D(Bh.x,0,0));

		this->pairsOfPlanes[1].p1 = Plane(Vector3D(0,-1,0), Vector3D(0,Bl.y,0));
		this->pairsOfPlanes[1].p2 = Plane(Vector3D(0,1,0), Vector3D(0,Bh.y,0));

		this->pairsOfPlanes[2].p1 = Plane(Vector3D(0,0,-1), Vector3D(0,0,Bl.z));
		this->pairsOfPlanes[2].p2 = Plane(Vector3D(0,0,1), Vector3D(0,0,Bh.z));
	}

	Vector3D getNormalVector( const Vector3D& aPoint, Vector2D aTextureUVCoordinates );

	Vector2D getTextureUVCoordinates( const Vector3D& aIntersectionPoint);

public:
	inline void setBl( const Vector3D &aBl )
	{
		this->Bl = aBl;

		this->updatePlanes();
	}

	inline void setBh( const Vector3D &aBh )
	{
		this->Bh = aBh;

		this->updatePlanes();
	}

public:
	Box(void);
	Box( const Vector3D &aBl, const Vector3D &aBh);
	Box( const Vector3D &aPosition, double aLenght, double aHeight, double aWidth);
	~Box(void);

	double checkIntersection( const Ray& aRay );
};
