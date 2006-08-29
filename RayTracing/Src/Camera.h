#pragma once

#include "Vector3D.h"
#include "SceneObject.h"
#include "Base.h"

class Camera : public SceneObject
{
private:
	Vector3D v; // - Vetores que sao passados como paremetros
	Vector3D n; // -

	Base base; // Base do sistema de coordenadas que será gerado

	float d; // Distancia focal

	float Hx; // Hx * 2 é a largura do plano de projecao
	float Hy; // Hy * 2 é a altura do plano de projecao

public:
	inline float getD() const
	{
		return this->d;
	}

	inline void setD( float aD)
	{
		this->d = aD;
	}

	inline float getHx() const
	{
		return this->Hx;
	}

	inline void setHx( float aHx )
	{
		this->Hx = aHx;
	}

	inline float getHy() const
	{
		return this->Hy;
	}

	inline void setHy( float aHy )
	{
		this->Hy = aHy;
	}

	inline void setV( Vector3D &aVector )
	{
		this->v = aVector;

		this->updateCoordinateSystemBase();
	}

	inline void setN( Vector3D &aVector )
	{
		this->n = aVector;

		this->updateCoordinateSystemBase();
	}

	inline Base &getBase()
	{
		return this->base;
	}

public:
	Camera( void );
	Camera( const Vector3D &aV, const Vector3D &aN, float aD = 1.0, 
		float aHx = 1.0, float aHy = 1.0, const Vector3D &aPosition = Vector3D(Vector3D::ZERO) );
	~Camera( void );

	inline void updateCoordinateSystemBase()
	{
		this->base.U = v.crossProduct(n);
		this->base.U.normalize();

		this->base.V = n.crossProduct(this->base.U);
		this->base.V.normalize();

		this->base.N = n;
		this->base.N.normalize();
	}
	
};