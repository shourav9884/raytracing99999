
#include "OGLRenderSystem.h"

#include "glut.h"
#include <cstdlib> // Devido ao NULL

OGLRenderSystem *OGLRenderSystem::singleton;


OGLRenderSystem::OGLRenderSystem()
{
}

void OGLRenderSystem::init( int aWidth, int aHeight )
{
	// Inicializa atributos
	this->width = aWidth;
	this->height = aHeight;

	// Inicializa OpenGL
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1); 

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	// Reshape de canvas
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );	
	glOrtho( 0.0, aWidth, aHeight, 0.0, 1.0, -1.0);	

	glRasterPos2i(0,aHeight);

	// Inicializa a textura que será utilizada para fazer o efeito de Specular Bloom
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->width, this->height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glReadBuffer( GL_BACK );
	glDrawBuffer( GL_BACK  );
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

void OGLRenderSystem::drawPixels( void *aData )
{
	glClear( GL_COLOR_BUFFER_BIT );

	// Reseta cursor para o inicio da tela
	glRasterPos2i(0,this->height);

	// Desenha pixels
	glDrawPixels( this->width, this->height, GL_RGB, GL_FLOAT, aData );

	glFlush(); // Garante que a operacao de pintar seja completada	
}

void OGLRenderSystem::reshapeCanvas( int aWidth, int aHeight )
{
	float xFactor = aWidth/(float)this->width;
	float yFactor = aHeight/(float)this->height;

	glPixelZoom( xFactor, yFactor );
}

void OGLRenderSystem::drawPixelsOverBuffer( void *aData )
{
	glClear( GL_ACCUM_BUFFER_BIT );

	glAccum(GL_ACCUM, 0.0);

	// Habilita a texturiazacao
	glEnable( GL_TEXTURE_2D );
	// Habilita blending do poligo com o frame-buffer
	glEnable( GL_BLEND );
	// Faz com que a cor da textura substitua a cor do objeto (não faz blending)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	
	//gluScaleImage(GL_RGB,this->width,this->height,GL_FLOAT,aData,widthOut,heightOut,GL_FLOAT, aDataOut);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, GL_RGB, GL_FLOAT, aData);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, widthOut, heightOut, GL_RGB, GL_FLOAT, aDataOut);

	//glBlendFunc( GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA );
	glBlendFunc( GL_ONE, GL_ONE );
	//glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_COLOR );

	//float meio = this->width/2;
	float meio = 00;
	float jitter = 0.4;

	for( int x = -5; x < 6; x++ )
	{
		for( int y = -5; y < 6; y++ )
		{
			//glClear( GL_COLOR_BUFFER_BIT );

			glBegin( GL_QUADS );

			float planeSizeOffset = meio/this->width;

			//glColor4f(0,0,1,1);
			glTexCoord2d( 0 + planeSizeOffset, 1 );				
			glVertex2f( 0+meio + x/jitter, 0 + y/jitter );

			//glColor4f(0,1,0,1);
			glTexCoord2d( 1, 1 );		
			glVertex2f( this->width + x/jitter, 0 + y/jitter );

			//glColor4f(1,0,0,0.5);
			glTexCoord2d( 1, 0 );		
			glVertex2f( this->width + x/jitter, this->height + y/jitter );
			
			//glColor4f(1,0,0,0.5);
			glTexCoord2d( 0 + planeSizeOffset, 0 );		
			glVertex2f( 0+meio + x/jitter, this->height + y/jitter );
			glEnd();

			glAccum(GL_ACCUM, 0.0);
		}
	}

	glAccum (GL_RETURN, 1.0);


	glFlush();
}