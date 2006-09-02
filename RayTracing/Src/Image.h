#pragma once

//#include <string>
//using namespace std;
#include "ColorRGBub.h"

#include <cstdio>
using namespace std;

#include "IL/IL.h"

class Image
{
	// Membros estaticos para o DevIL
private:
	static bool DevILInitialized;
	static ILuint DevILImageName;

private:
	ILubyte *imageData;

	int width;
	int height;
	int bytesPerPixel;
	int format;
	int type;

public:
	Image( void );
	Image( const char *aFileName );
	~Image( void );

	inline int getWidth() const
	{
		return width;
	}

	inline int getHeight() const
	{
		return height;
	}

	inline int getBytesPerPixel() const
	{
		return bytesPerPixel;
	}

	inline ILubyte *getImageData()
	{
		return this->imageData;
	}

	inline ColorRGBub getPixel( int xPosition, int yPosition )
	{
		ColorRGBub result(0,0,0);		

		if( xPosition < this->width && yPosition < this->height )
		{
			// Se a imagem foi inicializa
			if(this->imageData != NULL)
			{	
				const int deslocX = xPosition*this->bytesPerPixel;
				const int deslocY = yPosition*this->width*this->bytesPerPixel;

				// Lembrar que BMP além de serem escritos de cabeca para baixo, eles tambem
				// possuem um pixel format diferente (BGR ao inves de RGB)
				result.r = this->imageData[deslocX + deslocY + 0];
				result.g = this->imageData[deslocX + deslocY + 1];
				result.b = this->imageData[deslocX + deslocY + 2];				
			}
		}

		return result;
	}
};
