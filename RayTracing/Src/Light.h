#pragma once

#include "Ray.h"
#include "Object3D.h"
#include "ColorRGBf.h"
#include "Vector3D.h"
#include "SceneObject.h"
class Scene; // Se der include vai dar pau, pais assim teria um include recursivo

class Light : public SceneObject
{
protected:
	ColorRGBf color;
	float intensity;
	bool castShadow;
	
protected:
	virtual inline void initBaseAttributes()
	{
		this->intensity = 1.0f;
		this->castShadow = true;
	}

public:
	Light( void );
	Light( const Vector3D &aPosition, const ColorRGBf &aColor = ColorRGBf(1,1,1));

	virtual float evaluateIlumination( const Vector3D& aPoint, const Scene* aScene, double aTiny) = 0;

	inline const ColorRGBf &getColor()
	{
		return this->color;
	}

	inline void setColor( const ColorRGBf &aColor )
	{
		this->color = aColor;
	}

	inline const float getIntensity()
	{
		return this->intensity;
	}

	inline void setIntensity( float aIntensity )
	{
		this->intensity = aIntensity;
	}

	inline bool getCastShadow()
	{
		return this->castShadow;
	}

	inline void setCastShadow( bool aCastShadow )
	{
		this->castShadow = aCastShadow;
	}
};
