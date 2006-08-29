#pragma once

#include "Scene.h"
#include "Object3D.h"
#include "FrameBuffer.h"
#include <vector>

class RayTracer
{
private:
	struct Fragment
	{	
		ColorRGBf color;
		float zValue;
	};

private:
	Scene scene;

	// Distancias que formam o frustum
	double zNear;
	double zFar;

	// Valor que será utilzado como tolerancia para os calculo das intersecoes
	double tiny;

	// Resolução
	int width;
	int height;
	
public:
	RayTracer( void );
	~RayTracer( void );

	void init( );
	
	void executeRayTracer( FrameBuffer* aFrameBuffer, Scene* aScene );
	RayTracer::Fragment traceRay( const Ray& aRay, Scene* aScene , int aRecursionCurrentLevel);
	ColorRGBf shadePixel( IntersectionResult& aIntersectionResult, Object3D* aCurrentObject, Scene* aScene , int aRecursionCurrentLevel);

public:
	int getWidth()
	{
		return this->width;
	}

	void setWidth( int aWidth )
	{
		this->width = aWidth;
	}

	int getHeight()
	{
		return this->height;
	}

	void setHeight( int aHeight  )
	{
		this->height = aHeight;
	}

	void setZNear( double aZNear )
	{
		this->zNear = aZNear;
	}

	void setZFar( double aZFar )
	{
		this->zFar = aZFar;
	}

	void setTiny( double aTiny )
	{
		this->tiny = aTiny;
	}

};
