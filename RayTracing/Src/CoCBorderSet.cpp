#include "CoCBorderSet.h"

CoCBorderSet::CoCBorderSet( )
{
	PixelPosition temp0[] = {PixelPosition(0,0)};
	this->CoCBorders[0] = CoCBorder(1, temp0);

	
	PixelPosition temp1[] = {PixelPosition(0,1), PixelPosition(1,1), PixelPosition(1,0),
							 PixelPosition(1,-1),PixelPosition(0,-1),PixelPosition(-1,-1),
							 PixelPosition(-1,0), PixelPosition(-1,1)};
	this->CoCBorders[1] = CoCBorder(8, temp1);

	
	
	PixelPosition temp2[] = {PixelPosition(0,2), PixelPosition(1,2),  PixelPosition(2,1),
							 PixelPosition(2,0), PixelPosition(2,-1), PixelPosition(1,-2),
							 PixelPosition(0,-2),PixelPosition(-1,-2),PixelPosition(-2,-1),
							 PixelPosition(-2,0),PixelPosition(-2,1), PixelPosition(-1,2)};
	this->CoCBorders[2] = CoCBorder(12, temp2);

}
