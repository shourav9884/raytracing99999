#pragma once

#include "Object3D.h"
#include "Camera.h"
#include "Light.h"
#include "ColorRGBf.h"
#include <vector>
using namespace std; // Devido ao vector

class Scene
{
public:
	// Objetos da cena
	vector<Object3D*> sceneObjects;	
	vector<Light*> sceneLights;
	Camera camera;

	ColorRGBf ambientLight;

public:
	Scene( void );
	~Scene( void );

	void init( );

	const inline vector<Object3D*> &getSceneObjects( ) const
	{
		return this->sceneObjects;
	}

	const inline vector<Light*> &getSceneLights( ) const
	{
		return this->sceneLights;
	}

	inline Camera &getCamera( )
	{
		return this->camera;
	}

	inline ColorRGBf &getAmbientLight()
	{
		return this->ambientLight;
	}
};
