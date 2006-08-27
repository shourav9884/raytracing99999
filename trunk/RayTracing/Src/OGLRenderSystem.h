#pragma once

class OGLRenderSystem
{
private: // Atributos estaticos
	static OGLRenderSystem *singleton;

	int width;
	int height;
	float xScale;
	float yScale;

private:
	OGLRenderSystem( );

public: // Metodos estaticos
	static OGLRenderSystem *getSingletonPtr( );
	static OGLRenderSystem &getSingleton( );

	void init( int aWidth, int aHeight );

public:
	void drawPixels( void *aData );
	void reshapeCanvas( int aWidth, int aHeight );
};