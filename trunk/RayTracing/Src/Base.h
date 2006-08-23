#pragma once

#include "Vector3D.h"

class Base
{
// Atruibutes
public:
	Vector3D U; // -
	Vector3D V; // Base do sistema de coordenadas da camera
	Vector3D N;

public:
	inline Base(void)
	{
	}

	inline Base( const Vector3D &aU, const Vector3D &aV, const Vector3D &aN )
		:U(aU), V(aV), N(aN)
	{
	}

	inline Vector3D changeFromCanonicalBase( const Vector3D &aVector )
	{
		Vector3D result(this->U.dotProduct(aVector), this->V.dotProduct(aVector), this->N.dotProduct(aVector));

		return result;
	}

	inline Base changeFromCanonicalBase( const Base &aBase )
	{
		Base result(this->changeFromCanonicalBase(aBase.U), 
					this->changeFromCanonicalBase(aBase.V), 
					this->changeFromCanonicalBase(aBase.N) );

		return result;
	}

};
