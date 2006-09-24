#pragma once

#include "ColorRGBf.h"

class ColorRGBAf
{
public:
	typedef float intensity;
public:
	intensity r;
	intensity g;
	intensity b;
	intensity a;

public:
	inline ColorRGBAf()
		: r(0.5), g(0.5), b(0.5), a(1.0)
	{
	}

	inline ColorRGBAf( intensity aR, intensity aG, intensity aB, intensity aA )
		: r(aR), g(aG), b(aB), a(aA)
	{
	}

	inline ColorRGBAf( ColorRGBf aColorRGBf, intensity aA )
		: r(aColorRGBf.r), g(aColorRGBf.g), b(aColorRGBf.b), a(aA)
	{
	}

	inline ColorRGBAf operator +( const ColorRGBAf &aColor )
	{
		ColorRGBAf result;

		result.r = this->r + aColor.r;
		result.g = this->g + aColor.g;
		result.b = this->b + aColor.b;
		result.a = this->b + aColor.a;

		return result;
	}

	inline ColorRGBAf operator *( float aValue ) const
	{
		ColorRGBAf result;

		result.r = this->r * aValue;
		result.g = this->g * aValue;
		result.b = this->b * aValue;
		result.a = this->a * aValue;

		return result;
	}

	inline ColorRGBAf operator *( const ColorRGBAf &aColor )
	{
		ColorRGBAf result;

		result.r = this->r * aColor.r;
		result.g = this->g * aColor.g;
		result.b = this->b * aColor.b;
		result.a = this->a * aColor.a;

		return result;
	}

	inline ColorRGBAf operator /( float aValue )
	{
		ColorRGBAf result;

		result.r = this->r / aValue;
		result.g = this->g / aValue;
		result.b = this->b / aValue;
		result.a = this->a / aValue;

		return result;
	}
};
