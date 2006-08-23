#include "SceneObject.h"
#include "Camera.h"

SceneObject::SceneObject(void)
{
}
SceneObject::SceneObject( const Vector3D &aPosition )
: worldPosition(aPosition)
{
}

SceneObject::~SceneObject(void)
{
}