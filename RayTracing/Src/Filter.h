#pragma once

#include "ColorRGBf.h"

class Filter
{
private:
	static void getMaskData( ColorRGBf *aBuffer, ColorRGBf *aImage, int aXPixel, int aYPixel, int aWidth, int aHeight, int aMaskSize );

public:
	static void scanImage( ColorRGBf *aImage, int aWidth, int aHeight, int aMaskSize );
};
