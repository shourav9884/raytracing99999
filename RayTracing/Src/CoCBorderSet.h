#pragma once

#include "CoCBorder.h"

class CoCBorderSet
{
private:
	CoCBorder CoCBorders[3];

public:
	CoCBorderSet( );

	CoCBorder &getCoCBorder( int aN )
	{
		return this->CoCBorders[aN];
	}
};
