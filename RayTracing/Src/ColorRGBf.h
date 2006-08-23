#pragma once

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

	inline ColorRGBf operator *( float aValue )
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
};