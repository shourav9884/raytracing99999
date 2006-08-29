#include "Scene.h"

#include "box.h"
#include "Sphere.h"
#include "OmniLight.h"

#include "Texture.h"

Scene::Scene(void)
: ambientLight( 0.3f, 0.3f, 0.3f )
{
}

Scene::~Scene(void)
{	
}

void Scene::init( )
{
	// Apenas de teste

	this->ambientLight = ColorRGBf(0.5f,0.5f,0.5f);

	//Box *tempBox = new Box(Vector3D(-10.0,-1.0,-10.0),Vector3D(10.0,0.0,10.0));
	Box *tempBox = new Box(Vector3D(0.0,-3.0,3.0), 10.0, 5.0, 10.0);
	tempBox->getMaterial().setSpecularLevel(1.0f);
	tempBox->getMaterial().setGlossiness(1.0);
	Texture *tempImage = new Texture("images/cobblestonesDiffuse.tga", Texture::BILINEAR);
	tempBox->getMaterial().setDiffuseMap(tempImage);
	tempBox->getMaterial().setAmbientMap(tempImage);
	tempBox->getMaterial().setNormalMap(new Texture("images/cobblestonesNormal.tga", Texture::BILINEAR));
	tempBox->getMaterial().setSpecularMap(new Texture("images/cobblestonesDepth.tga", Texture::BILINEAR));
	this->sceneObjects.push_back(tempBox);

	////Box *tempBox = new Box(Vector3D(-10.0,-1.0,-10.0),Vector3D(10.0,0.0,10.0));
	//tempBox = new Box(Vector3D(0.0,1.0,0.0), 1.0, 1.0, 1.0);
	//tempBox->getMaterial().setSpecularLevel(1.0f);
	//tempBox->getMaterial().setGlossiness(1.0);
	//tempBox->getMaterial().setRefract(0.5f);
	//tempBox->getMaterial().setIndexOfRefraction(1.66f);
	//this->sceneObjects.push_back(tempBox);

	//Plane *tempPlane = new Plane(Vector3D(0,1,0), Vector3D(0,0,0));
	//tempPlane->getMaterial().getDiffuseColor().g = 0.0;
	//this->sceneObjects.push_back(tempPlane);

	// Esfera1
	//Sphere *tempSphere = new Sphere(1.5, Vector3D(0, 0, 2));
	//tempSphere->getMaterial().getDiffuseColor().r = 1.2f;
	//tempSphere->getMaterial().getDiffuseColor().g = 0.2f;
	//tempSphere->getMaterial().getDiffuseColor().b = 0.2f;
	//tempSphere->getMaterial().setGlossiness(10.0);
	//tempSphere->getMaterial().setReflect(0.4f);
	//tempSphere->getMaterial().setRefract(0.0);
	//tempSphere->getMaterial().setIndexOfRefraction(1.6f);
	//this->sceneObjects.push_back( tempSphere );

	// Esfera2
	//tempSphere = new Sphere(0.5, Vector3D(1.0, 1.0, 6.0));
	//tempSphere->getMaterial().getDiffuseColor().r = 0.0;
	//this->sceneObjects.push_back( tempSphere );

	this->sceneLights.push_back( new OmniLight(Vector3D(-5,5,5)) );

	//this->sceneLights.push_back( new OmniLight(Vector3D(0,5,-3)) );
}
