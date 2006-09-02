#include "Box.h"

#include "Base.h"
#include "Util.h"

Box::Box(void)
: Bl(0.1,0.1,0.1), Bh(-0.1,-0.1,-0.1)
{
	this->updatePlanes( );
}

Box::Box( const Vector3D &aBl, const Vector3D &aBh)
: Bl(aBl), Bh(aBh)
{
	this->updatePlanes( );
}

Box::Box( const Vector3D &aPosition, double aWidth, double aHeight, double aLenght)
: Bl(aPosition.x - aWidth/2, aPosition.y - aHeight/2, aPosition.z - aLenght/2),
Bh(aPosition.x + aWidth/2, aPosition.y + aHeight/2, aPosition.z + aLenght/2)
{
	this->updatePlanes( );
}

Box::~Box(void)
{
}

double Box::checkIntersection( const Ray& aRay )
{
	double result = -1;

	double Tnear = -100000.0;
	double Tfar = 100000.0;

	for ( int i = 0; i < 3; i ++ )
	{
		// Se raio é paralelo aos planos Xs
		if( this->pairsOfPlanes[i].p1.isParallel(aRay.vector) )
		{
			const Vector3D &viewPosition1 = this->pairsOfPlanes[i].p1.getWorldPosition();
			const Vector3D &viewPosition2 = this->pairsOfPlanes[i].p2.getWorldPosition();		

			double maxValue = max( viewPosition1[i], viewPosition2[i] );
			double minValue = min( viewPosition1[i], viewPosition2[i] );

			// Se ponto nap estiver entre os planos
			if( aRay.point.x > maxValue  || aRay.point.x < minValue )
				return result;
		}
		else
		{
			double t1 = this->pairsOfPlanes[i].p1.checkIntersection(aRay);
			double t2 = this->pairsOfPlanes[i].p2.checkIntersection(aRay);

			bool swaped  = false;

			// Swap
			if( t2 < t1 )
			{
				double temp = t1;
				t1 = t2;
				t2 = temp;

				swaped = true;				
			}

			if( t1 > Tnear  )
			{
				Tnear = t1;

				// Quando qual dos planos foi intersectado
				if( swaped )
					this->planeIntersected = &this->pairsOfPlanes[i].p2;
				else
					this->planeIntersected = &this->pairsOfPlanes[i].p1;
			}
			if( t2 < Tfar )
			{
				Tfar = t2;
			}
		}
	}

	if(Tnear < Tfar)
		result = Tnear;

	return result;
}

Vector3D Box::getNormalVector( const Vector3D& aPoint, Vector2D aTextureUVCoordinates )
{
	Vector3D result(this->planeIntersected->getVector());

	// Se existir um mapa de normais
	if( this->material.existNormalMap() )
	{		
		Vector3D originalNormalVector = this->planeIntersected->getVector();

		Vector3D normalVectorFromMap = this->material.getNormalResult( aTextureUVCoordinates ).toNormalizedVector3D();

		Base normalMapBase;

		if( originalNormalVector == Vector3D::UNIT_X )
		{
			normalMapBase = Base(Vector3D(0,1,0), Vector3D(0,0,1), Vector3D(1,0,0));
		}	
		else if( originalNormalVector == Vector3D::NEGATIVE_UNIT_X )
		{
			normalMapBase = Base(Vector3D(0,1,0), Vector3D(0,0,1), Vector3D(-1,0,0));
		}
		else if( originalNormalVector == Vector3D::UNIT_Y )
		{
			normalMapBase = Base(Vector3D(1,0,0), Vector3D(0,0,1), Vector3D(0,1,0));
		}	
		else if( originalNormalVector == Vector3D::NEGATIVE_UNIT_Y )
		{
			normalMapBase = Base(Vector3D(1,0,0), Vector3D(0,0,1), Vector3D(0,-1,0));
		}
		else if( originalNormalVector == Vector3D::UNIT_Z )
		{
			normalMapBase = Base(Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(0,0,1));
		}	
		else if( originalNormalVector == Vector3D::NEGATIVE_UNIT_Z )
		{
			normalMapBase = Base(Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(0,0,-1));
		}

		result = normalMapBase.changeToCanonicalBase(normalVectorFromMap);
	}

	return result;
}

Vector2D Box::getTextureUVCoordinates( const Vector3D& aIntersectionPoint)
{
	Vector2D result;

	Vector3D normalVector = this->planeIntersected->getVector();

	if( normalVector == Vector3D::UNIT_X || normalVector == Vector3D::NEGATIVE_UNIT_X )
	{	
		double y = (aIntersectionPoint.y - this->Bl.y)/(this->Bh.y - this->Bl.y);
		double z = (aIntersectionPoint.z - this->Bl.z)/(this->Bh.z - this->Bl.z);

		result = Vector2D(y, z);
	}
	else if( normalVector == Vector3D::UNIT_Y || normalVector == Vector3D::NEGATIVE_UNIT_Y )
	{
		double x = (aIntersectionPoint.x - this->Bl.x)/(this->Bh.x - this->Bl.x);
		double z = (aIntersectionPoint.z - this->Bl.z)/(this->Bh.z - this->Bl.z);

		result = Vector2D(x, z);
	}
	else
	{
		double x = (aIntersectionPoint.x - this->Bl.x)/(this->Bh.x - this->Bl.x);
		double y = (aIntersectionPoint.y - this->Bl.y)/(this->Bh.y - this->Bl.y);

		result = Vector2D(x, y);
	}

	return result;
}