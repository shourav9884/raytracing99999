
#include "OGLRenderSystem.h"
#include "ColorRGBf.h"

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

void OGLRenderSystem::drawPixelsOverBuffer( void *aData, bool aFullScreen, float aMaxSpreadFactor, float aIntensity, int aSamples )
{
//	glClear( GL_ACCUM_BUFFER_BIT );

//	glAccum(GL_ACCUM, 1.0);

	int leftVertexsOffset = 0;
	if( !aFullScreen )
	{
		leftVertexsOffset = this->width/2;
	}
//	int specularBloomSamples = 11;
//	float maxSpreadFactor = 0.05;
//	float specularBloomIntensity = 2.0;

	// Habilita a texturiazacao
	glEnable( GL_TEXTURE_2D );
	// Habilita blending do poligo com o frame-buffer
	glEnable( GL_BLEND );
	// Faz com que a cor da textura substitua a cor do objeto (não faz blending)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	float tempSpecularBloomFactor = ((float)aIntensity/(aSamples*aSamples));
	ColorRGBf *tempImageDataPointer = reinterpret_cast<ColorRGBf *>(aData);
	for( int i = 0; i < (this->width*this->height); i++ )
	{
		tempImageDataPointer[i] = tempImageDataPointer[i] * tempSpecularBloomFactor;
	}

	
	//gluScaleImage(GL_RGB,this->width,this->height,GL_FLOAT,aData,widthOut,heightOut,GL_FLOAT, aDataOut);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, GL_RGB, GL_FLOAT, aData);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, widthOut, heightOut, GL_RGB, GL_FLOAT, aDataOut);

	//glBlendFunc( GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA );
	glBlendFunc( GL_ONE, GL_ONE );
	//glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_COLOR );

	// Quando a coordenada da textura deve mudar a cada camanda desenhada
	float textureUVOffset = (2*aMaxSpreadFactor)/(aSamples-1);

	for( int x = 0; x < aSamples; x++ )
	{
		for( int y = 0; y < aSamples; y++ )
		{
			// Limpa o color buffer para desenhar uma nova camanda nele
			//glClear( GL_COLOR_BUFFER_BIT );

			// Desenha camada (cada camada é um plano colado com plano de projeção)
			glBegin( GL_QUADS );				

				glTexCoord2d( (0+aMaxSpreadFactor)-(textureUVOffset*x) + (double)leftVertexsOffset/this->width, (1+aMaxSpreadFactor)-(textureUVOffset*y));				
				glVertex2f( 0 + leftVertexsOffset, 0 );

				glTexCoord2d( (1+aMaxSpreadFactor)-(textureUVOffset*x), (1+aMaxSpreadFactor)-(textureUVOffset*y));		
				glVertex2f( this->width, 0 );

				glTexCoord2d( (1+aMaxSpreadFactor)-(textureUVOffset*x), (0+aMaxSpreadFactor)-(textureUVOffset*y) );		
				glVertex2f( this->width, this->height );
				
				glTexCoord2d( (0+aMaxSpreadFactor)-(textureUVOffset*x) + (double)leftVertexsOffset/this->width, (0+aMaxSpreadFactor)-(textureUVOffset*y) );		
				glVertex2f( 0 + leftVertexsOffset, this->height );
				
			glEnd();

			// Adiciona camada ao accumulation buffer
			//glAccum(GL_ACCUM, specularBloomIntensity/(specularBloomSamples*specularBloomSamples));
		}
	}

	// Retorna imagem final que estava armazenada no accumulatio buffer para o color buffer
	//glAccum (GL_RETURN, 1.0);

	glFlush();
}