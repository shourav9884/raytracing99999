#include "Scene.h"

#include "box.h"
#include "Sphere.h"
#include "OmniLight.h"

#include "Image.h"

Scene::Scene(void)
{
}

Scene::~Scene(void)
{	
}

void Scene::init( )
{
	// Apenas de teste

	this->ambientLight = ColorRGBf(0.3f,0.3f,0.3f);

	//Box *tempBox = new Box(Vector3D(-10.0,-1.0,-10.0),Vector3D(10.0,0.0,10.0));
	Box *tempBox = new Box(Vector3D(0.0,-3.0,3.0), 15.0, 1.0, 15.0);
	tempBox->getMaterial().setSpecularLevel(0.5f);
	tempBox->getMaterial().setGlossiness(1.0);
	Image *tempImage = new Image("images/brickwallDiffuse.png");
	tempBox->getMaterial().setDiffuseMap(tempImage);
	tempBox->getMaterial().setAmbientMap(tempImage);
	tempBox->getMaterial().setSpecularMap(new Image("images/brickwallSpecular.png"));;
	this->sceneObjects.push_back(tempBox);

	//Plane *tempPlane = new Plane(Vector3D(0,1,0), Vector3D(0,0,0));
	//tempPlane->getMaterial().getDiffuseColor().g = 0.0;
	//this->sceneObjects.push_back(tempPlane);

	// Esfera1
	Sphere *tempSphere = new Sphere(1.5, Vector3D(0, 0, 2));
	tempSphere->getMaterial().getDiffuseColor().r = 1.2f;
	tempSphere->getMaterial().getDiffuseColor().g = 0.2f;
	tempSphere->getMaterial().getDiffuseColor().b = 0.2f;
	tempSphere->getMaterial().setGlossiness(10.0);
	//tempSphere->getMaterial().setReflect(0.3f);
	tempSphere->getMaterial().setRefract(0.5);
	tempSphere->getMaterial().setIndexOfRefraction(0.8f);
	this->sceneObjects.push_back( tempSphere );

	// Esfera2
	//tempSphere = new Sphere(0.5, Vector3D(1.0, 1.0, 6.0));
	//tempSphere->getMaterial().getDiffuseColor().r = 0.0;
	//this->sceneObjects.push_back( tempSphere );

	this->sceneLights.push_back( new OmniLight(Vector3D(-5,5,5)) );

	this->sceneLights.push_back( new OmniLight(Vector3D(0,5,-3)) );
}
