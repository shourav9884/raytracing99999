#pragma once

class OGLRenderSystem
{
private: // Atributos estaticos
	static OGLRenderSystem *singleton;

private:
	OGLRenderSystem( );
	~OGLRenderSystem( );	

public: // Metodos estaticos
	static OGLRenderSystem *getSingletonPtr( );
	static OGLRenderSystem &getSingleton( );

	void init( int aWidth, int aHeight );

public:
	void drawPixels( int aWidth, int aHeight, void *aData );
	void reshapeCanvas( int aWidth, int aHeight );
};