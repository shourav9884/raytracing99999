#pragma once
#include "light.h"

class OmniLight : public Light
{
public:
	OmniLight( void );
	OmniLight( const Vector3D &aPosition, const ColorRGBf &aColor = ColorRGBf(1,1,1));

	virtual double evaluateIlumination( const Vector3D& aPoint, const Scene* aScene, double aTiny);
};
