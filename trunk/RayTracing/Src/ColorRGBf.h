#pragma once

#include "Vector3D.h"

class ColorRGBf
{
public:
	typedef float intensity;
public:
	intensity r;
	intensity g;
	intensity b;

public:
	inline ColorRGBf()
		: r(0.5), g(0.5), b(0.5)
	{
	}

	inline ColorRGBf( intensity aR, intensity aG, intensity aB )
		: r(aR), g(aG), b(aB)
	{
	}

	inline ColorRGBf operator +( const ColorRGBf &aColor )
	{
		ColorRGBf result;

		result.r = this->r + aColor.r;
		result.g = this->g + aColor.g;
		result.b = this->b + aColor.b;

		return result;
	}

	inline ColorRGBf operator *( float aValue ) const
	{
		ColorRGBf result;

		result.r = this->r * aValue;
		result.g = this->g * aValue;
		result.b = this->b * aValue;

		return result;
	}

	inline ColorRGBf operator *( const ColorRGBf &aColor )
	{
		ColorRGBf result;

		result.r = this->r * aColor.r;
		result.g = this->g * aColor.g;
		result.b = this->b * aColor.b;

		return result;
	}

	inline ColorRGBf operator /( float aValue )
	{
		ColorRGBf result;

		result.r = this->r / aValue;
		result.g = this->g / aValue;
		result.b = this->b / aValue;

		return result;
	}

	inline Vector3D toNormalizedVector3D()
	{
		Vector3D result( (this->r-0.5)*2.0, (this->g-0.5)*2.0, (this->b-0.5)*2.0 );
		result.normalize();

		return result;
	}
};