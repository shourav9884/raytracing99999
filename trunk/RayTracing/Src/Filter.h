#pragma once

#include "ColorRGBf.h"
#include "FrameBuffer.h"

class Filter
{
private:
	struct ColorAmount
	{
		ColorRGBf color;
		float amount;
	};

private:
	// Tamanho da imagem
	int width;
	int height;

	ColorAmount *bufferDoF;

	// Tamanho maximo que um CoC pode ter
	static const int CoCMaxRay = 30;
	int pixelsAmountInCoCWithRay[CoCMaxRay+1];


public:
	Filter( int aMaskSize, int aWidth, int aHeight );

	void filterDoF( FrameBuffer* aFrameBuffer, float aDoFFocusedDistance, float aDoFLensAperture, float aDoFProjectionPlanedistance , float aZNear, float aZFar);

	void uniformDistribution( float aCoCDiameter, float aFocusedDistance, int aXPixel, int aYPixel, FrameBuffer* aSrcBuffer , Filter::ColorAmount* aDstBuffer, float aZNear, float aZFar);

};
