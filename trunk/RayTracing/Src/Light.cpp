#include "Light.h"

Light::Light( void )
{
	this->initBaseAttributes();
}

Light::Light( const Vector3D &aPosition, const ColorRGBf &aColor )
: SceneObject(aPosition), color(aColor)
{
	this->initBaseAttributes();
}