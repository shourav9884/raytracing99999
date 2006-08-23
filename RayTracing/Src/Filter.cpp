#include "Filter.h"

void Filter::getMaskData( ColorRGBf *aBuffer, ColorRGBf *aImage, int aXPixel, int aYPixel, int aWidth, int aHeight, int aMaskSize )
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

void Filter::scanImage( ColorRGBf *aImage, int aWidth, int aHeight, int aMaskSize )
{
	ColorRGBf *maskData = new ColorRGBf[aMaskSize*aMaskSize];

	for( int y = 0; y < aHeight; y++ )
	{
		
		for( int x = 0; x < aWidth; x++ )
		{
			
			Filter::getMaskData(maskData, aImage, x, y, aWidth, aHeight, aMaskSize);

			ColorRGBf tempPixelResult(0,0,0);

			// Faz a convolucao
			for( int yMask = 0; yMask < aMaskSize; yMask++ )
			{
				for( int xMask = 0; xMask < aMaskSize; xMask++ )	
				{
					tempPixelResult = tempPixelResult + maskData[xMask + yMask*aMaskSize];
				}
			}
			aImage[x + y*aWidth] = tempPixelResult/static_cast<float>(aMaskSize*aMaskSize);
		}
	}

	delete maskData;
}
