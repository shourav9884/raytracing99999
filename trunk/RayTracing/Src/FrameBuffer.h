#pragma once

#include "ColorRGBf.h"

class FrameBuffer
{
public:
	ColorRGBf *colorBuffer;
	float *zBuffer;
	ColorRGBf *highIntensityBuffer;

public:
	FrameBuffer(int aWidth, int aHeight);
	~FrameBuffer(void);
};