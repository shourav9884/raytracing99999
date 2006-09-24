#include "CoCBorder.h"

CoCBorder::CoCBorder( )
: size(0), currentPosition(0)
{
}

CoCBorder::CoCBorder( int aSize, PixelPosition *aPixelsPosition )
: size(aSize), currentPosition(0)
{
	for( int i = 0; i < this->size; i++ )
	{
		this->pixelsPositions[i] = aPixelsPosition[i];
	}
}