#include "RayTracer.h"

#include "Object3D.h"
#include "Sphere.h"
#include "Ray.h"
#include "ColorRGBf.h"
#include "Box.h"
#include "Base.h"

#include <vector>
using namespace std;

RayTracer::RayTracer(void)
: zNear(0.0), zFar(50.0), tiny(0.1), width(200), height(200), clearColor(0.0f,0.0f,0.0f), recursionLevel(1)
{
}

RayTracer::~RayTracer(void)
{
}

void RayTracer::init( )
{
}

void RayTracer::executeRayTracer( FrameBuffer* aFrameBuffer, Scene* aScene )
{
	Camera &camera = aScene->getCamera();

	// Atributos da camera (colocados aqui para otimizar)
	float hx = camera.getHx();
	float hy = camera.getHy();
	const Vector3D &position = camera.getWorldPosition();
	float d = camera.getD();

	// Atributos da camera trabalhados
	double incrementXt = 1.0/(this->width-1);
	double incrementYt = 1.0/(this->height-1);

	double currentXt = 0.0;
	double currentYt = 0.0;

	///////////////////////////////////////////////////////////////////////////
	// Converte quatro pontos do plano de projecao da camera (expressos no sistema de vista) para o sistema mundial
	///////////////////////////////////////////////////////////////////////////
	Vector3D upLeftPoint;
	Vector3D upRightPoint;
	Vector3D downLeftPoint;
	Vector3D downRightPoint;

	Base &cameraBase = camera.getBase();

	// Systema de coordenadas mundiais expresso em funcao do sistema de vista (como se o de vista fosse o canonico)
	Vector3D worldOriginInViewSystem = cameraBase.changeFromCanonicalBase( Vector3D(0,0,0) - camera.getWorldPosition());		
	Base worldBaseInViewSystem = cameraBase.changeFromCanonicalBase( Base(Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(0,0,1)));

	upLeftPoint = worldBaseInViewSystem.changeFromCanonicalBase(Vector3D(hx, hy, d) - worldOriginInViewSystem);
	upRightPoint = worldBaseInViewSystem.changeFromCanonicalBase(Vector3D(-hx, hy, d) - worldOriginInViewSystem);
	downLeftPoint = worldBaseInViewSystem.changeFromCanonicalBase(Vector3D(hx, -hy, d) - worldOriginInViewSystem);
	downRightPoint = worldBaseInViewSystem.changeFromCanonicalBase(Vector3D(-hx, -hy, d) - worldOriginInViewSystem);

	// Vetores que serviram para computar os pontos do plano de projecao da camera
	Vector3D horizontal = upRightPoint - upLeftPoint;
	//Vector3D vertical = downRight - upRight;
	Vector3D vertical = upRightPoint - downRightPoint;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	for( int i = aHeight-1; i >= 0; i-- ) // Tem que ser subtraindo pois OPENGL desenha
	for( int i = 0; i < this->height; i++ )    // os pixel DE BAIXO PARA CIMA
	{   
		currentXt = 0.0;

		for( int j = 0; j < this->width; j++ )
		{	
			//Vector3D xPoint = upLeft + (horizontal * currentXt);
			Vector3D xPoint = downLeftPoint + (horizontal * currentXt);
			Vector3D finalPointOnProjectionPlane = xPoint + (vertical * currentYt);

			// Raio que sai da camera (ja considerando sistema de coordenas da camera)
			Ray ray( finalPointOnProjectionPlane - camera.getWorldPosition(), camera.getWorldPosition() );

			Fragment fragment = this->traceRay( ray, aScene , this->recursionLevel);
			
			aFrameBuffer->colorBuffer[(this->width*i) + j] = fragment.color;
			aFrameBuffer->zBuffer[(this->width *i) + j] = fragment.zValue;

			currentXt += incrementXt;
		}
		currentYt += incrementYt;
	}
}

RayTracer::Fragment RayTracer::traceRay( const Ray& aRay, Scene* aScene , int aRecursionCurrentLevel)
{
	// Equivalente ao clearcolor de OpenGL
	ColorRGBf finalColor = this->clearColor;

	Fragment result = {finalColor, static_cast<float>(this->zFar) };

	const vector<Object3D*> &sceneObjects = aScene->getSceneObjects();	

	// Varre a lista de objetos da cena
	for( vector<Object3D*>::const_iterator &itrObject = sceneObjects.begin(); itrObject != sceneObjects.end(); itrObject++)
	{
		Object3D *currentObject = *itrObject;

		// Armazenara o restultado da intersecao do raio com o currentObject
		IntersectionResult intersectionResult;

		// Atualiza a variavel intersectionResult com o real resultado
		currentObject->getIntersectionResults( aRay, intersectionResult );

		// Teste da distância e a tolerancia no calculo das intersecoes
		if( intersectionResult.t > this->zNear && 
			intersectionResult.t < result.zValue && 
			intersectionResult.t > this->tiny )
		{
			result.zValue = static_cast<float>(intersectionResult.t);

			result.color = this->shadePixel( intersectionResult, currentObject, aScene , aRecursionCurrentLevel);
		}
	}

	// Normaliza o zBuffer
	result.zValue = static_cast<float>( (result.zValue - this->zNear)/(this->zFar - this->zNear));

	return result;
}

ColorRGBf RayTracer::shadePixel( IntersectionResult& aIntersectionResult, Object3D* aCurrentObject, Scene* aScene , int aRecursionCurrentLevel)
{
	const vector<Light*> &sceneLights = aScene->getSceneLights();	

	Material &material = aCurrentObject->getMaterial();

	ColorRGBf Ia(0,0,0);
	ColorRGBf Id(0,0,0);
	ColorRGBf Is(0,0,0);	

	// Calculo da iluminacao AMBIENTAL
	Ia = aScene->getAmbientLight() * material.getAmbientResult(aIntersectionResult.textureUVCoordinates);

	// Percorre todas a luzes da cena
	for( vector<Light*>::const_iterator &itrLight = sceneLights.begin(); itrLight != sceneLights.end(); itrLight++)
	{
		Light *currentLight = *itrLight;

		// Se a sombra estiver habilitada e houver objeto projetando
		float lightAmount =  currentLight->evaluateIlumination( aIntersectionResult.point, aScene, this->tiny);
		if( lightAmount != 0.0f )
		{
			Vector3D lightVector = currentLight->getWorldPosition() - aIntersectionResult.point;
			lightVector.normalize();
			
			double coeficient = lightVector.dotProduct(aIntersectionResult.normal);

			// Se estiver virada para o lado da luz
			if(coeficient > 0.0)
			{
				ColorRGBf lightResult = currentLight->getColor() * currentLight->getIntensity() * lightAmount;

				// Cor DIFUSA (tem que adicionar o resultado de cada Light)
				Id = Id + material.getDiffuseResult(aIntersectionResult.textureUVCoordinates) * lightResult * static_cast<float>(coeficient);

				// Cor SPACULAR (tem que adicionar o resultado de cada Light)
				Vector3D R = (aIntersectionResult.normal * 2 * lightVector.dotProduct(aIntersectionResult.normal)) - lightVector;
				R.normalize();

				// Vetor de vista que será utilzado no calculo da componente specular
				Vector3D V = aIntersectionResult.point - aScene->getCamera().getWorldPosition();
				V.invertDirection();
				V.normalize();

				double specularCoeficiente = V.dotProduct(R);

				// Fator que suaviza o specular quando o raio refletido tende a fazer 90 graus com o vetor normal
				float softenCoeficient = 1.0;
				if( material.getSoften() > 0.0 )
				{
					softenCoeficient = static_cast<float>(pow( R.dotProduct(aIntersectionResult.normal) , 
						static_cast<double>(material.getSoften())));
				}

				specularCoeficiente = specularCoeficiente * softenCoeficient;

				if(specularCoeficiente  > 0)
				{
					Is = Is + (material.getSpecularResult(aIntersectionResult.textureUVCoordinates) * lightResult * material.getSpecularLevel() * static_cast<float>(pow(specularCoeficiente, material.getGlossiness())));
				}
			}
		}
	}

	// Reflexao
	float reflect = material.getReflect();
	ColorRGBf reflectionResult(0,0,0);
	if( reflect > 0.0 && aRecursionCurrentLevel > 0 )
	{
		Vector3D viewVector = aIntersectionResult.point - aScene->getCamera().getWorldPosition();
		viewVector.invertDirection();

		Vector3D reflectedVector = (aIntersectionResult.normal * 2 * viewVector.dotProduct(aIntersectionResult.normal)) - viewVector;
		reflectedVector.normalize();

		reflectionResult = this->traceRay(Ray(reflectedVector,aIntersectionResult.point), aScene, aRecursionCurrentLevel-1 ).color;
	}
	//// Refacao
	//float refract = material.getRefract();
	//ColorRGBf refractionResult(0,0,0);
	//if( refract > 0.0 && aRecursionCurrentLevel > 0 )
	//{
	//	Vector3D viewVector = aIntersectionResult.point - aScene->getCamera().getWorldPosition();
	//	viewVector.normalize();
	//	
	//	Vector3D normalVectorInverted = aIntersectionResult.normal;
	//	normalVectorInverted.invertDirection();

	//	float indexOfRefractionRatio = 1.0f/material.getIndexOfRafraction();		

	//	double cosi = normalVectorInverted.dotProduct(viewVector);
	//	double cosj = sqrt(1.0 - pow(indexOfRefractionRatio, 2) * (1.0- pow(cosi,2)) );

	//	Vector3D refractedVector = (viewVector * (1.0f/indexOfRefractionRatio)) +
	//							   (normalVectorInverted * (cosj - (indexOfRefractionRatio * cosi)));
	//	refractedVector.normalize();

	//	refractionResult = this->traceRay(Ray(refractedVector,aIntersectionResult.point), aScene, aRecursionCurrentLevel-1 ).color;
	//}

	// Refacao
	float refract = material.getRefract();
	ColorRGBf refractionResult(0,0,0);
	if( refract > 0.0 && aRecursionCurrentLevel > 0 )
	{
		Vector3D viewVector = aScene->getCamera().getWorldPosition() - aIntersectionResult.point;
		viewVector.normalize();
		
		Vector3D normalVectorInverted = aIntersectionResult.normal;
		//normalVectorInverted.invertDirection();

		float indexOfRefractionRatio = 1.0f/material.getIndexOfRafraction();		

		double cosi = normalVectorInverted.dotProduct(viewVector);
		double tempValue = sqrt(1.0 - (pow(indexOfRefractionRatio, 2) * (1.0 - pow(cosi,2))) );

		Vector3D refractedVector =  (normalVectorInverted * ((indexOfRefractionRatio* cosi) - tempValue)) -
								   (viewVector * indexOfRefractionRatio);

		refractedVector.normalize();

		refractionResult = this->traceRay(Ray(refractedVector,aIntersectionResult.point), aScene, aRecursionCurrentLevel-1 ).color;
	}

	ColorRGBf result = ((Ia + Id + Is)*(1-reflect) + reflectionResult*reflect)*(1-refract) +
					   refractionResult*refract;

	return result;
}