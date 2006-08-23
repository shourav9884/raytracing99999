#include "Object3D.h"

Object3D::Object3D(void)
{
}

Object3D::Object3D(const Vector3D &aPosition, const Material &aMaterial )
: SceneObject(aPosition), material(aMaterial)
{
}

void Object3D::getIntersectionResults( const Ray& aRay, IntersectionResult& aResult )
{
	double resultT = this->checkIntersection( aRay );

	// Ponto onde houve a intersecao
	Vector3D intersectionPoint( aRay.point.x + (aRay.vector.x*resultT),
							    aRay.point.y + (aRay.vector.y*resultT),
							    aRay.point.z + (aRay.vector.z*resultT) );

	// Vetor normal do ponto onde houve a intersecao
	Vector3D resultNormal = this->getNormalVector(intersectionPoint, resultT);
	// Normaliza o vetor normal
	resultNormal.normalize();

	aResult.textureUVCoordinates = this->getTextureUVCoordinates(intersectionPoint, resultNormal);

	// Coloca o point de intersexao no retorno
	aResult.point = intersectionPoint;
	// Coloca o o vetor normal no retorno
	aResult.normal = resultNormal;

	aResult.t = resultT;
}