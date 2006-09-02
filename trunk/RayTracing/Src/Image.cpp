#include "Image.h"

#include <string>
using namespace std;

bool Image::DevILInitialized = false;
ILuint Image::DevILImageName = 0; // Variavel que guardara o identificador gerado pelo devil

Image::Image(void)
{
	if( !Image::DevILInitialized )
	{
		ilInit();
		ilGenImages(1, &DevILImageName);
		Image::DevILInitialized = true;
	}
}

Image::Image( const char *aFileName )
{
	if( !Image::DevILInitialized )
	{
		ilInit();
		ilGenImages(1, &Image::DevILImageName);
		Image::DevILInitialized = true;
	}

	ilBindImage(Image::DevILImageName);
	ILboolean imageLoaded = ilLoadImage(ILstring(aFileName));

	if( imageLoaded )
	{
		this->width = ilGetInteger(IL_IMAGE_WIDTH);
		this->height= ilGetInteger(IL_IMAGE_HEIGHT);
		this->bytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		this->format = ilGetInteger(IL_IMAGE_FORMAT);
		this->type = ilGetInteger(IL_IMAGE_TYPE);

		this->imageData = new ILubyte[this->width * this->height* this->bytesPerPixel];

		// Flip Vertical
		//iluMirror();
		memcpy( this->imageData, ilGetData(), this->width * this->height * this->bytesPerPixel);
	}
}

Image::~Image(void)
{
	delete this->imageData;
}
