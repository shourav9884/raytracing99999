#pragma once

#include "glut.h"
#include "FrameBuffer.h"

class OGLRenderSystem
{
private: // Atributos estaticos
	static OGLRenderSystem *singleton;

	int width;
	int height;
	float xScale;
	float yScale;

	GLuint posProcTexIDs[2];

private:
	OGLRenderSystem( );

public: // Metodos estaticos
	static OGLRenderSystem *getSingletonPtr( );
	static OGLRenderSystem &getSingleton( );

	void init( int aWidth, int aHeight );

public:
	void drawPixels( void *aData );
	void reshapeCanvas( int aWidth, int aHeight );

	void drawPixelsOverBufferSB( void *aData, bool aFullScreen, float aMaxSpreadFactor, float aIntensity, int aSamples );
	void drawPixelsOverBufferDoF( FrameBuffer *aFrameBuffer, bool aFullScreen, float aFocusPlaneDistance );
};