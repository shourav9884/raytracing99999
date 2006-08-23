#pragma once

#include "SceneObject.h"
#include "Ray.h"
#include "Material.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Vector2D.h"

// Estrutura que armazena o resultado da intesecao do raio com o objeto
struct IntersectionResult
{
	double t;
	Vector3D normal;
	Vector3D point;
	Vector2D textureUVCoordinates;
};

class Object3D : public SceneObject
{
protected:
	Material material;	

protected:
	virtual Vector3D getNormalVector( const Vector3D &aPoint, double t ) = 0;

	virtual Vector2D getTextureUVCoordinates( const Vector3D &aIntersectionPoint, const Vector3D &aNormalVector ) = 0;

public:
	Object3D( void );
	Object3D( const Vector3D &aPosition, const Material &aMaterial = Material() );

	virtual double checkIntersection( const Ray& aRay ) = 0 ;	
	
	virtual void getIntersectionResults( const Ray& aRay, IntersectionResult& aResult );	

	inline Material &getMaterial()
	{
		return this->material;
	}

	inline void setMaterial( const Material & aMaterial )
	{
		this->material = aMaterial;
	}
};
