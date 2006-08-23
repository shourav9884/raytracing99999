
#include "OGLRenderSystem.h"

#include "glut.h"
#include <cstdlib> // Devido ao NULL

OGLRenderSystem *OGLRenderSystem::singleton;


OGLRenderSystem::OGLRenderSystem()
{
}

OGLRenderSystem::~OGLRenderSystem()
{
}

void OGLRenderSystem::init( int aWidth, int aHeight )
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1); 

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	this->reshapeCanvas(aWidth, aHeight);

	glRasterPos2i( 0, 0 );
}

OGLRenderSystem *OGLRenderSystem::getSingletonPtr( )
{
	if( singleton != NULL )
	{
		return OGLRenderSystem::singleton ;
	}
	else
	{
		singleton = new OGLRenderSystem( );
		return OGLRenderSystem::singleton;
	}
}

OGLRenderSystem &OGLRenderSystem::getSingleton( )
{
	if( singleton != NULL )
		return *OGLRenderSystem::singleton ;
	else
	{
		singleton = new OGLRenderSystem( );
		return *OGLRenderSystem::singleton;
	}

}

//    ----------------
//    |(0,0)         |(width,0)
//    |              |
//    |              |
//    |              |
//    |              |
//  y |(0,Height)    |(width,height)
//  | ----------------
//   - x

void OGLRenderSystem::drawPixels( int aWidth, int aHeight, void *aData )
{
	glClear( GL_COLOR_BUFFER_BIT );

	// Reseta cursor para o inicio da tela
	glRasterPos2i(0,aHeight);

	// Desenha pixels
	glDrawPixels( aWidth, aHeight, GL_RGB, GL_FLOAT, aData );

	glFlush(); // Garante que a operacao de pintar seja completada	
}

void OGLRenderSystem::reshapeCanvas( int aWidth, int aHeight )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );	
	glOrtho( 0.0, aWidth, aHeight, 0.0, 1.0, -1.0);	
}