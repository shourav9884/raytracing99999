#include "Camera.h"

Camera::Camera(void)
: v(Vector3D(0,1,0)),
  n(Vector3D(0,0,1)), 
  d(1.0f), 
  Hx(0.5f), 
  Hy(0.5f), 
  SceneObject(Vector3D(0,0,0))
{
	this->updateCoordinateSystemBase();
}

Camera::Camera( const Vector3D &aV, const Vector3D &aN, float aD, float aHx, float aHy, const Vector3D &aPosition)
: v(aV),
  n(aN), 
  d(aD), 
  Hx(aHx), 
  Hy(aHy), 
  SceneObject(aPosition)
{
	this->updateCoordinateSystemBase();
}

Camera::~Camera(void)
{
}