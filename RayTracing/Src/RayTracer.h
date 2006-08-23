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
	
public:
	RayTracer( void );
	~RayTracer( void );

	void init( );
	
	void executeRayTracer( int aWidth, int aHeight, FrameBuffer* aFrameBuffer, Scene* aScene );
	RayTracer::Fragment traceRay( const Ray& aRay, Scene* aScene , int aRecursionCurrentLevel);
	ColorRGBf shadePixel( IntersectionResult& aIntersectionResult, Object3D* aCurrentObject, Scene* aScene , int aRecursionCurrentLevel);

};
