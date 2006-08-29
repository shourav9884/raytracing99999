#pragma once

#include "RayTracer.h"
#include "Scene.h"
#include "AppRoot.h"
#include "Vector3D.h"

class SceneLoader
{
public:
	static void loadScene( const char *aFilename, AppRoot &aApproot, RayTracer &aRayTracer, Scene &aScene );
};
