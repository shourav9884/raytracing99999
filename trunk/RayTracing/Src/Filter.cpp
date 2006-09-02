#include "Filter.h"

#include <cmath>
using namespace std;

Filter::Filter( int aMaskSize, int aWidth, int aHeight )
: maskSize(aMaskSize), width(aWidth), height(aHeight)
{
	this->imageBuffer = new ColorRGBf[aWidth*aHeight];
	this->maskBuffer = new ColorRGBf[this->maskSize*this->maskSize];

	// Preenche os valores da mascara
	this->mask = new float[this->maskSize*this->maskSize];
	for( int x = 0; x < this->maskSize; x ++ )
	{
		for( int y = 0; y < this->maskSize; y ++ )
		{
			//this->mask[x + y*this->maskSize] = sin() + sin();
		}
	}

}

ColorRGBf *Filter::scanImage( ColorRGBf *aImage )
{
	for( int y = 0; y < this->height; y++ )
	{
		
		for( int x = 0; x < this->width; x++ )
		{
			
			Filter::getMaskData(this->maskBuffer, aImage, x, y, this->width, this->height, this->maskSize);

			ColorRGBf tempPixelResult(0,0,0);

			// Faz a convolucao
			for( int yMask = 0; yMask < this->maskSize; yMask++ )
			{
				for( int xMask = 0; xMask < this->maskSize; xMask++ )	
				{
					tempPixelResult = tempPixelResult + this->maskBuffer[xMask + yMask*this->maskSize];
				}
			}
			this->imageBuffer[x + y*this->width] = tempPixelResult/static_cast<float>(this->maskSize*this->maskSize);
		}
	}

	return this->imageBuffer;
}