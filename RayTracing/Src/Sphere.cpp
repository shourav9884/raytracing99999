#include "Sphere.h"

#include "Util.h"
#include <cmath>

Sphere::Sphere(void)
: radius(1)
{
}

Sphere::Sphere( float aRadius, const Vector3D &aPosition )
: radius(aRadius), Object3D(aPosition)
{
}

double Sphere::checkIntersection( const Ray& aRay )
{
	double resultT = -1;

	const Vector3D &rayVector = aRay.vector;
	const Vector3D &rayPoint = aRay.point;
	
	// Vetor que vai do centro da esfera ao ponto C (da camera)
	Vector3D C_Minus_S = (rayPoint - this->worldPosition);	

	// Produto vetorial do vetor da reta
	double rayVectorDotProduct = rayVector.dotProduct(rayVector);

	// Delta da Formula de Baskara
	double delta = pow( (rayVector.dotProduct( C_Minus_S )), 2 )
		- ( ( rayVectorDotProduct ) * ( C_Minus_S.dotProduct(C_Minus_S) - (this->radius * this->radius) ));

	if( delta >= 0.0 ) // Intersecta em um ou mais de um ponto da esfera
	{
		double numerator = - (rayVector.dotProduct(C_Minus_S));
		double denominator = rayVectorDotProduct;
		double deltaSqrt = sqrt(delta);

		double resultT1 = (numerator + deltaSqrt) / denominator;
		double resultT2 = (numerator - deltaSqrt) / denominator;

		if( resultT1 <= 0.0 && resultT2 <= 0.0 ) // Esfera atrás do inicio do raio
		{
			resultT = -1;
		}
		else if( (resultT1 > 0.0) ^ (resultT2 > 0.0) ) // Raio comeca dentro da esfera
		{
			//resultT = max(resultT1, resultT2);

			// Deste jeito nao leva em consideracao a parte interna da esfera
			resultT = -1;
		}
		else // Esfera completamente a frente do inicio da raio
		{
			resultT = min(resultT1, resultT2);
		}
	}

	return resultT;
}

Vector3D Sphere::getNormalVector( const Vector3D &aPoint, double t )
{
	return Vector3D( aPoint - this->worldPosition );
}

Vector2D Sphere::getTextureUVCoordinates( const Vector3D &aIntersectionPoint, const Vector3D &aNormalVector )
{
	Vector2D result;

	return result;
}