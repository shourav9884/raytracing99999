#include "SceneLoader.h"

#include <fstream>
#include <string>
using namespace std;

#include "Box.h"
#include "Sphere.h"

void SceneLoader::loadScene(const char *aFilename, AppRoot &aApproot, RayTracer &aRayTracer, Scene &aScene)
{
	fstream fs;
	fs.open(aFilename, fstream::in);

	assert( fs.is_open() );

	// Buffers que armazenam os valores lidos do arquivo
	string stringValue;
	int intValue;
	float floatValue1;
	float floatValue2;
	float floatValue3;

	while( true )
	{
		string readLine;
		
		fs >> readLine;

		if(  readLine == string("#raytracer") )
		{
			fs >> stringValue >> stringValue >> intValue;
			aRayTracer.setWidth( intValue );

			fs >> stringValue >> stringValue >> intValue;
			aRayTracer.setHeight( intValue );

			fs >> stringValue >> stringValue >> floatValue1;
			aRayTracer.setTiny( floatValue1 );

			fs >> stringValue >> stringValue >> floatValue1;
			aRayTracer.setZNear( floatValue1 );

			fs >> stringValue >> stringValue >> floatValue1;
			aRayTracer.setZFar( floatValue1 );
		}
		else if( readLine == string("#scene") )
		{
			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			aScene.setAmbientLight( ColorRGBf(floatValue1, floatValue2, floatValue3) );
		}
		else if( readLine == string("#camera") )
		{
			Camera &tempCamera = aScene.getCamera();

			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			tempCamera.setV( Vector3D(floatValue1, floatValue2, floatValue3) );

			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			tempCamera.setN( Vector3D(floatValue1, floatValue2, floatValue3) );

			fs >> stringValue >> stringValue >> floatValue1 ;
			tempCamera.setHx( floatValue1 );

			fs >> stringValue >> stringValue >> floatValue1 ;
			tempCamera.setHy( floatValue1 );

			fs >> stringValue >> stringValue >> floatValue1 ;
			tempCamera.setD( floatValue1 );
		}
		else if( readLine == string("#box") )
		{
			Box *tempBox = new Box;

			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			tempBox->setBl( Vector3D(floatValue1, floatValue2, floatValue3) );
			
			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			tempBox->setBh( Vector3D(floatValue1, floatValue2, floatValue3) );

			aScene.addObject3D( tempBox );
		}
		else if( readLine == string("#sphere") )
		{
			Sphere *tempSphere = new Sphere;

			fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
			tempSphere->setWorldPosition( Vector3D(floatValue1, floatValue2, floatValue3) );
			
			fs >> stringValue >> stringValue >> floatValue1 ;
			tempSphere->setRadius( floatValue1 );

			aScene.addObject3D( tempSphere );
		}

	}


	//printf("Lido = %s\n", readLine);
	
	fs.close();
}