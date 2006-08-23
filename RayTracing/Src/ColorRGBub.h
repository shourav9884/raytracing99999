#pragma once

#include "ColorRGBf.h"

class ColorRGBub
{
public:
	typedef unsigned char intensity;
public:
	intensity r;
	intensity g;
	intensity b;

public:
	inline ColorRGBub()
		: r(125), g(125), b(125)
	{
	}

	inline ColorRGBub( intensity aR, intensity aG, intensity aB )
		: r(aR), g(aG), b(aB)
	{
	}

	inline ColorRGBf toColorRGBf()
	{
		return ColorRGBf( this->r/255.0f, this->g/255.0f, this->b/255.0f );
	}

	inline static intensity putInRange( float aValue )
	{
		return static_cast<intensity>((aValue*255) + 0.5);
	}
};