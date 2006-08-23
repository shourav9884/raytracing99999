#pragma once

#include "Vector3D.h"

class Camera;

class SceneObject
{
protected:
	Vector3D worldPosition;

public:
	SceneObject( void );
	SceneObject( const Vector3D &aPosition );
	virtual ~SceneObject(void);

	inline const Vector3D &getWorldPosition( ) const
	{
		return this->worldPosition;
	}

	inline void setWorldPosition( const Vector3D &aPosition )
	{
		this->worldPosition = aPosition;
	}
};
