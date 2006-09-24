#pragma once

#include <cstdlib>


class PixelPosition
{
public:
	int x;
	int y;

public:
	PixelPosition( )
		: x(0), y(0)
	{
	}

	PixelPosition( int aX, int aY )
		: x(aX), y(aY)
	{
	}
};

class CoCBorder
{
private:
	int size;
	PixelPosition pixelsPositions[30];

	int currentPosition;

public:
	CoCBorder( );
	CoCBorder( int aSize, PixelPosition *aPixelsPosition );
	
	PixelPosition *next(  )
	{
		if( this->currentPosition < size )
			return &this->pixelsPositions[this->currentPosition++];
		else 
			return NULL;
	}
};
