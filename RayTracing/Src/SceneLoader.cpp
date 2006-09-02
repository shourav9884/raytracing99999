#include "SceneLoader.h"

#include <fstream>
#include <string>
using namespace std;

#include "Box.h"
#include "Sphere.h"
#include "OmniLight.h"

void SceneLoader::loadScene(const char *aFilename, AppRoot &aApproot, RayTracer &aRayTracer, Scene &aScene)
{
	// Pega o nome do arquivo que contem a cena
	fstream fs0;
	fs0.open("initialScene.txt", fstream::in);

	string fileName;
	fs0 >> fileName;
	fs0.close();

	// Carrega os dados da cena	
	fstream fs;
	fs.open(fileName.c_str(), fstream::in);

	if( fs.is_open() )
	{
		// Buffers que armazenam os valores lidos do arquivo
		string stringValue;
		string stringValue2;
		int intValue;
		float floatValue1;
		float floatValue2;
		float floatValue3;

		//for(int i = 0; i < 7; i++)

		bool temp = fs.eof();
		while( temp = !fs.eof() )
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

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				aRayTracer.setClearColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> intValue;
				aRayTracer.setRecursionLevel( intValue );
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
				tempCamera.setWorldPosition( Vector3D(floatValue1, floatValue2, floatValue3) );

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

				// Material
				Material &tempMaterial = tempBox->getMaterial();

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setDiffuseColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> stringValue >> stringValue2;
				if( stringValue != string("null") )
				{
					if( stringValue2 == string("bilinear") )
						tempMaterial.setDiffuseMap( new Texture(stringValue.c_str(), Texture::BILINEAR) );
					else
						tempMaterial.setDiffuseMap( new Texture(stringValue.c_str(), Texture::NEAREST) );
				}

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setSpecularColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSpecularLevel( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setGlossiness( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSoften( floatValue1 );

				fs >> stringValue >> stringValue >> stringValue >> stringValue2;
				if( stringValue != string("null") )
				{
					if( stringValue2 == string("bilinear") )
						tempMaterial.setSpecularMap( new Texture(stringValue.c_str(), Texture::BILINEAR) );
					else
						tempMaterial.setSpecularMap( new Texture(stringValue.c_str(), Texture::NEAREST) );
				}

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setAmbientColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> stringValue >> stringValue2;
				if( stringValue != string("null") )
				{
					if( stringValue2 == string("bilinear") )
						tempMaterial.setAmbientMap( new Texture(stringValue.c_str(), Texture::BILINEAR) );
					else
						tempMaterial.setAmbientMap( new Texture(stringValue.c_str(), Texture::NEAREST) );
				}

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setReflect( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setRefract( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setIndexOfRefraction( floatValue1 );


				fs >> stringValue >> stringValue >> stringValue >> stringValue2;
				if( stringValue != string("null") )
				{
					if( stringValue2 == string("bilinear") )
						tempMaterial.setNormalMap( new Texture(stringValue.c_str(), Texture::BILINEAR) );
					else
						tempMaterial.setNormalMap( new Texture(stringValue.c_str(), Texture::NEAREST) );
				}


				aScene.addObject3D( tempBox );
			}
			else if( readLine == string("#sphere") )
			{
				Sphere *tempSphere = new Sphere;

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempSphere->setWorldPosition( Vector3D(floatValue1, floatValue2, floatValue3) );
				
				fs >> stringValue >> stringValue >> floatValue1 ;
				tempSphere->setRadius( floatValue1 );

				// Material
				Material &tempMaterial = tempSphere->getMaterial();

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setDiffuseColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setSpecularColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSpecularLevel( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setGlossiness( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSoften( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setAmbientColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setReflect( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setRefract( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setIndexOfRefraction( floatValue1 );


				aScene.addObject3D( tempSphere );
			}
			else if( readLine == string("#plane") )
			{
				Plane *tempPlane = new Plane;

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempPlane->setWorldPosition( Vector3D(floatValue1, floatValue2, floatValue3) );
				
				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempPlane->setVector( Vector3D(floatValue1, floatValue2, floatValue3) );

				// Material
				Material &tempMaterial = tempPlane->getMaterial();

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setDiffuseColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setSpecularColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSpecularLevel( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setGlossiness( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setSoften( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempMaterial.setAmbientColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setReflect( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setRefract( floatValue1 );

				fs >> stringValue >> stringValue >> floatValue1;
				tempMaterial.setIndexOfRefraction( floatValue1 );

				aScene.addObject3D( tempPlane );
			}
			else if( readLine == string("#omnilight") )
			{
				OmniLight *tempOmniLight = new OmniLight;

				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempOmniLight->setWorldPosition( Vector3D(floatValue1, floatValue2, floatValue3) );
				
				fs >> stringValue >> stringValue >> floatValue1 >> floatValue2 >> floatValue3;
				tempOmniLight->setColor( ColorRGBf(floatValue1, floatValue2, floatValue3) );

				fs >> stringValue >> stringValue >> floatValue1 ;
				tempOmniLight->setIntensity( floatValue1 );

				fs >> stringValue >> stringValue >> stringValue ;
				bool result = true;
				if( stringValue == string("false") )
					result = false;
				tempOmniLight->setCastShadow(result);

				aScene.addLight( tempOmniLight );
			}
		}
	}

	fs.close();
}