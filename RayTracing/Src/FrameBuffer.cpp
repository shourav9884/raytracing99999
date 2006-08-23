#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int aWidth, int aHeight)
{
	this->colorBuffer = new ColorRGBf[aWidth * aHeight];
	this->zBuffer = new float[aWidth * aHeight];
	this->highIntensityBuffer = new ColorRGBf[aWidth * aHeight];
}

FrameBuffer::~FrameBuffer(void)
{
	delete[] this->colorBuffer;
	delete[] this->zBuffer;
	delete[] this->highIntensityBuffer;
}
