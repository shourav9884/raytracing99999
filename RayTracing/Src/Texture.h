#pragma once

#include "Image.h"

#include "ColorRGBf.h"

class Texture
{
private:
	typedef char InterpolationType;

private:
	Image image;
	InterpolationType interpolationType;

public:
	
	const static InterpolationType NEAREST = 0;
	const static InterpolationType BILINEAR = 1;

public:
	Texture( const char *aFileName, InterpolationType aInterpolationType );
	~Texture( void );

	inline ColorRGBf getPixel( float aXNormalized, float aYNormalized )
	{
		ColorRGBf result(0,0,0);

		if(aXNormalized < 1.0 && aXNormalized >= 0.0 && aYNormalized < 1.0 && aYNormalized >= 0.0)
		{
			if( this->interpolationType == Texture::BILINEAR)
			{
				int width = this->image.getWidth();
				int height = this->image.getHeight();

				float x = aXNormalized * width;
				float y = aYNormalized * height;

				// 
				int x1 = static_cast<int>(x);
				int y1 = static_cast<int>(y);

				// 
				int x2 = x1+1;
				int y2 = y1+1;

				// Peso do segundo pixel
				float xFactor = x2 - x;			
				float yFactor = y2 - y;

				//////////////
				// p1 // p2 //
				//////////////
				// p3 // p4 // 
				//////////////
				ColorRGBf pixel1 = this->image.getPixel(x1,y1).toColorRGBf();
				ColorRGBf pixel2 = this->image.getPixel(x2,y1).toColorRGBf();
				ColorRGBf pixel3 = this->image.getPixel(x1,y2).toColorRGBf();
				ColorRGBf pixel4 = this->image.getPixel(x2,y2).toColorRGBf();

				ColorRGBf temp1 = (pixel1 * (xFactor)) + (pixel2 * (1-xFactor));
				ColorRGBf temp2 = (pixel3 * (xFactor)) + (pixel4 * (1-xFactor));

				result = (temp1 * (yFactor)) + (temp2 * (1-yFactor));
			}
			else
			{
				int width = this->image.getWidth();
				int height = this->image.getHeight();

				result = this->image.getPixel(static_cast<int>(aXNormalized*width),
					static_cast<int>(aYNormalized*height)).toColorRGBf();
			}
		}

		return result;
	}
};
