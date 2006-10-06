#pragma once

#include "ColorRGBf.h"
#include "FrameBuffer.h"

class Filter
{
private:
	struct ColorAmount
	{
		ColorRGBf color;
		int amount;
	};

private:
	int width;
	int height;
	//int maskSize;
	//ColorRGBf *imageBuffer;

	//ColorRGBf *maskBuffer;
	//float *mask;

	ColorAmount *bufferDoF;

private:

	//inline void getMaskData( ColorRGBf *aBuffer, ColorRGBf *aImage, int aXPixel, int aYPixel, int aWidth, int aHeight, int aMaskSize )
	//{
	//	int offset = aMaskSize/2;

	//	for( int x = 0; x < aMaskSize; x++ )		
	//	{
	//		for( int y = 0; y < aMaskSize; y++ )
	//		{
	//			int imageX = (aXPixel-offset+x);
	//			int imageY = (aYPixel-offset+y);

	//			if(imageX < 0)
	//				imageX = 0;
	//			else if(imageX >= aWidth)
	//				imageX = aWidth-1;
	//			if(imageY < 0)
	//				imageY = 0;
	//			else if(imageY >= aHeight)
	//				imageY = aHeight-1;

	//			aBuffer[x + y*aMaskSize] = aImage[ imageX + imageY*aWidth];
	//		}
	//	}
	//}

	inline void uniformDistribution( float c, int xPoint, int yPoint, ColorRGBf *buffer1, ColorAmount *buffer2 )
	{
		int r = (int)(c/2);

		ColorRGBf intensity = buffer1[xPoint + yPoint * 300];

		for( int x = xPoint-r; x <= xPoint+r; x++ )
		{
			for( int y = yPoint-r; y <= yPoint+r; y++ )
			{
				if( x >= 0 && x < 300 && y >= 0 && y < 300 )
				{
					int pointDistance = (x-xPoint)*(x-xPoint) + (y-yPoint)*(y-yPoint);

					if( pointDistance <= r*r )
					{
						buffer2[x + y * 300].color = intensity + buffer2[x + y * 300].color;
						buffer2[x + y * 300].amount += 1;
					}
				}
			}
		}
	}

public:
	Filter( int aMaskSize, int aWidth, int aHeight );

	//ColorRGBf *scanImage( ColorRGBf *aImage );

	void filterDoF( FrameBuffer *aFrameBuffer );
};
