#include "Filter.h"

#include <cmath>
using namespace std;

Filter::Filter( int aMaskSize, int aWidth, int aHeight )
: width(aWidth), height(aHeight)//, maskSize(aMaskSize)
{
//	this->imageBuffer = new ColorRGBf[aWidth*aHeight];
//	this->maskBuffer = new ColorRGBf[aMaskSize*aMaskSize];
//	this->mask = new float[aMaskSize*aMaskSize];

	this->bufferDoF = new ColorAmount[aWidth*aHeight];

	for( int i = 0 ; i < this->width*this->height; i++ )
	{
		this->bufferDoF[i].color = ColorRGBf(0.0,0.0,0.0);
		this->bufferDoF[i].amount = 0;
	}
}

//ColorRGBf *Filter::scanImage( ColorRGBf *aImage )
//{
//	for( int y = 0; y < this->height; y++ )
//	{
//		
//		for( int x = 0; x < this->width; x++ )
//		{
//			
//			Filter::getMaskData(this->maskBuffer, aImage, x, y, this->width, this->height, this->maskSize);
//
//			ColorRGBf tempPixelResult(0,0,0);
//
//			// Faz a convolucao
//			for( int yMask = 0; yMask < this->maskSize; yMask++ )
//			{
//				for( int xMask = 0; xMask < this->maskSize; xMask++ )	
//				{
//					tempPixelResult = tempPixelResult + this->maskBuffer[xMask + yMask*this->maskSize];
//				}
//			}
//			this->imageBuffer[x + y*this->width] = tempPixelResult/static_cast<float>(this->maskSize*this->maskSize);
//		}
//	}
//
//	return this->imageBuffer;
//}

void Filter::filterDoF( FrameBuffer *aFrameBuffer )
{
	int imageSize = this->width * this->height;

	//for( int i = 0; i < imageSize; i++ )
	//{
	//	this->bufferDoF[i].color = ColorRGBf(0.0,0.0,0.0);
	//	this->bufferDoF[i].amount = 0;
	//}

	static float df = 7.0;
	for( int x = 0; x < this->width; x++ )
	{
		for( int y = 0; y < this->height; y++ )
		{	
			float E = 100.0;
			float dr = 1.0;
			float f = 1.0f/(1.0f/df + 1.0f/dr);

			float d = aFrameBuffer->zBuffer[x + y*300];

			float Vd = (f*d)/(d-f);
			float Vf = (f*df)/(df-f);

			float CoCDiameter = (abs(Vd - Vf) * E/Vd);

			this->uniformDistribution( CoCDiameter, x, y, aFrameBuffer->colorBuffer, this->bufferDoF);
		}
	}

	for( int i = 0; i < imageSize; i++ )
	{
		aFrameBuffer->colorBuffer[i] = this->bufferDoF[i].color/(float)this->bufferDoF[i].amount;

		// Reseta buffer temporário
		this->bufferDoF[i].color = ColorRGBf(0.0,0.0,0.0);
		this->bufferDoF[i].amount = 0;
	}
}