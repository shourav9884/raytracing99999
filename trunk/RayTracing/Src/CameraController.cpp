#include "CameraController.h"

#include "Base.h"
#include "Quaternion.h"

CameraController::CameraController(void)
{
}

CameraController::~CameraController(void)
{
}

void CameraController::moveOverVector( float aOffset, CameraVector aVector )
{
	const Base &base= this->camera->getBase();

	if( CameraController::VECTOR_U == aVector)
		camera->setWorldPosition( this->camera->getWorldPosition() + (base.U*aOffset));
	else if( CameraController::VECTOR_V == aVector)
		camera->setWorldPosition( this->camera->getWorldPosition() + (base.V*aOffset));
	else if( CameraController::VECTOR_N == aVector)
		camera->setWorldPosition( this->camera->getWorldPosition() + (base.N*aOffset));
}

void CameraController::rotateAroundVector( float aDegree, CameraVector aVector )
{
	const Base &base= this->camera->getBase();

	if( CameraController::VECTOR_U == aVector)
	{
		Quaternion rotation(aDegree, base.U);

		Vector3D resultVector = rotation.rotate(base.N);
		resultVector.normalize();

		camera->setN( resultVector );
	}
	else if( CameraController::VECTOR_V == aVector)
	{
		Quaternion rotation(aDegree, base.V);

		Vector3D resultVector = rotation.rotate(base.N);
		resultVector.normalize();

		camera->setN( resultVector );
	}
	else if( CameraController::VECTOR_N == aVector)
	{
		Quaternion rotation(aDegree, base.N);

		Vector3D resultVector = rotation.rotate(base.V);
		resultVector.normalize();

		camera->setV( resultVector );
	}
}

