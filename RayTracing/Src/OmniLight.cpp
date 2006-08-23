#include "OmniLight.h"	

#include "Scene.h"
#include <vector>
using namespace std;

OmniLight::OmniLight( void )
: Light()
{
}

OmniLight::OmniLight( const Vector3D &aPosition, const ColorRGBf &aColor)
: Light(aPosition, aColor)
{
}

double OmniLight::evaluateIlumination( const Vector3D& aPoint, const Scene* aScene, double aTiny)
{
	// Deveria ter alguma coisa aqui de decaimeno
	double result = 1.0;

	if( this->castShadow )
	{
		const vector<Object3D*> &sceneObjects = aScene->getSceneObjects();

		// OBS: o vetor deste raio está normalizado, 
		// asim pode-se calcular decaimento, utilizar o tiny corretamente, etc.
		Vector3D rayVector = (this->worldPosition - aPoint);
		rayVector.normalize();
		Ray rayFromPointToLight( rayVector, aPoint);

		double tMax = rayFromPointToLight.getTOfPoint( this->worldPosition );

		bool lightOcluded = false;
		// Varre a lista de objetos da cena pra checar se a luz foi escondida por algum objeto
		for( vector<Object3D*>::const_iterator &itr = sceneObjects.begin(); (itr != sceneObjects.end()) && (!lightOcluded); itr++)
		{
			Object3D *currentObject = *itr;

			// Verifica intersecao
			double intersectionResult = currentObject->checkIntersection( rayFromPointToLight );

			// Checa se o objeto intersectado esta entre a o ponto e a fonte de luz
			// Está levando em consideracao o tiny
			if(intersectionResult > aTiny && intersectionResult < tMax)
			{
				result = 0.0;

				lightOcluded = true;		
			}			
		}
	}

	return result;
}