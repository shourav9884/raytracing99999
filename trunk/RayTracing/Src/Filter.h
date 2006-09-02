#pragma once

#include "ColorRGBf.h"

class Filter
{
private:
	int width;
	int height;
	int maskSize;
	ColorRGBf *imageBuffer;

	// 
	ColorRGBf *maskBuffer;
	float *mask;

private:

	inline void getMaskData( ColorRGBf *aBuffer, ColorRGBf *aImage, int aXPixel, int aYPixel, int aWidth, int aHeight, int aMaskSize )
	{
		int offset = aMaskSize/2;

		for( int x = 0; x < aMaskSize; x++ )		
		{
			for( int y = 0; y < aMaskSize; y++ )
			{
				int imageX = (aXPixel-offset+x);
				int imageY = (aYPixel-offset+y);

				if(imageX < 0)
					imageX = 0;
				else if(imageX >= aWidth)
					imageX = aWidth-1;
				if(imageY < 0)
					imageY = 0;
				else if(imageY >= aHeight)
					imageY = aHeight-1;

				aBuffer[x + y*aMaskSize] = aImage[ imageX + imageY*aWidth];
			}
		}
	}

public:
	Filter( int aMaskSize, int aWidth, int aHeight );

	ColorRGBf *scanImage( ColorRGBf *aImage );

};
