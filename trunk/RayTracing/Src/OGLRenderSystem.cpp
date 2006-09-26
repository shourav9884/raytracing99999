
#include "OGLRenderSystem.h"
#include "ColorRGBf.h"
#include "ColorRGBAf.h"
#include "CoCBorderSet.h"

#include "glut.h"
#include <cstdlib> // Devido ao NULL

#include <cstdio>

OGLRenderSystem *OGLRenderSystem::singleton;


OGLRenderSystem::OGLRenderSystem()
: width(300),
  height(300),
  xScale(1.0),
  yScale(1.0),
  SBTextureSize(32)
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

	// Cria texturas que serão utilizadas para os efeitos de pos-processamento
	glGenTextures(2, this->posProcTexIDs);

	glBindTexture(GL_TEXTURE_2D, this->posProcTexIDs[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Inicializa a textura que será utilizada para fazer o efeito de Specular Bloom
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->SBTextureSize, this->SBTextureSize, 0, GL_RGB, GL_FLOAT, NULL);


	glBindTexture(GL_TEXTURE_2D, this->posProcTexIDs[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Inicializa a textura que será utilizada para fazer o efeito de Specular Bloom
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_FLOAT, NULL);
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

void OGLRenderSystem::drawPixelsOverBufferSB( void *aData, bool aFullScreen, float aMaxSpreadFactor, float aIntensity, int aSamples )
{
//	glClear( GL_ACCUM_BUFFER_BIT );

//	glAccum(GL_ACCUM, 1.0);
	const GLubyte *temp = glGetString(GL_VENDOR);
	temp = glGetString(GL_RENDERER);
	temp = glGetString(GL_EXTENSIONS);
	temp = glGetString(GL_VERSION);

	GLint tempInt = -10;

	glGetIntegerv(GL_RED_BITS, &tempInt);
	glGetIntegerv(GL_STENCIL_BITS, &tempInt);
	glGetIntegerv(GL_ALPHA_BITS, &tempInt);
	glGetIntegerv(GL_ACCUM_BLUE_BITS, &tempInt);



	int leftVertexsOffset = 0;
	if( !aFullScreen )
	{
		leftVertexsOffset = this->width/2;
	}
//	int specularBloomSamples = 11;
//	float maxSpreadFactor = 0.05;
//	float specularBloomIntensity = 2.0;

	glBindTexture(GL_TEXTURE_2D, this->posProcTexIDs[0]);
	// Habilita a texturiazacao
	glEnable( GL_TEXTURE_2D );
	// Habilita blending do poligo com o frame-buffer
	glEnable( GL_BLEND );
	// Faz com que a cor da textura substitua a cor do objeto (não faz blending)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	float tempSpecularBloomFactor = ((float)aIntensity/(aSamples*aSamples));
	ColorRGBf *tempImageDataPointer = reinterpret_cast<ColorRGBf *>(aData);
	for( int i = 0; i < (this->width*this->height); i++ )
	{
		tempImageDataPointer[i] = tempImageDataPointer[i] * tempSpecularBloomFactor;
	}

	gluScaleImage(GL_RGB,this->width,this->height,GL_FLOAT,aData,this->SBTextureSize,this->SBTextureSize,GL_FLOAT, aData);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, GL_RGB, GL_FLOAT, aData);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->SBTextureSize, this->SBTextureSize, GL_RGB, GL_FLOAT, aData);

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

			if( pow((double)aMaxSpreadFactor-(textureUVOffset*x),2.0) + pow((double)aMaxSpreadFactor-(textureUVOffset*y),2.0) < pow((double)aMaxSpreadFactor,2.0))
			{
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
			}

			// Adiciona camada ao accumulation buffer
			//glAccum(GL_ACCUM, specularBloomIntensity/(specularBloomSamples*specularBloomSamples));
		}
	}

	// Retorna imagem final que estava armazenada no accumulatio buffer para o color buffer
	//glAccum (GL_RETURN, 1.0);

	glFlush();
}

void OGLRenderSystem::drawPixelsOverBufferDoF( FrameBuffer *aFrameBuffer, bool aFullScreen, float aFocusPlaneDistance )
{
	glClear(GL_COLOR_BUFFER_BIT);

	int leftVertexsOffset = 0;
	if( aFullScreen )
	{
		leftVertexsOffset = this->width/2;
	}

	// Habilita alpha teste que será utilizado para saber se um pixel pertence a um CoC
	glEnable(GL_ALPHA_TEST);
	// Habilita texturizacao
	glEnable( GL_TEXTURE_2D );
	// Habilita blending do poligo com o frame-buffer
	glEnable( GL_BLEND );
	// Faz com que a cor da textura substitua a cor do objeto (não faz blending)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Ativa a seguna textura criada na inicializacao
	glBindTexture(GL_TEXTURE_2D, this->posProcTexIDs[1]);

	ColorRGBf *tempImageDataPointer = reinterpret_cast<ColorRGBf *>(aFrameBuffer->colorBuffer);
	ColorRGBAf *tempImageDataPointerFinal = new ColorRGBAf[this->width*this->height];

	float E = 10.0;
	static float df = 5.0;
	//df += 0.01;
	float dr = 1.0;
	float f = 1.0/(1.0/df + 1.0/dr);
	float Vf = (f*df)/(df-f);	
	float maxCoCDiameter = (Vf/(f*f/E)) - (E);	
	for( int i = 0; i < (this->width*this->height); i++ )
	{
		//float d = aFrameBuffer->zBuffer[i];
		float d = 20;

		float Vd = (f*d)/(d-f);

		//float CoCDiameter = abs(a*(s*(1.0/f - 1.0/depth) - 1.0));
		//float CoCDiameter = (abs(Vd - Vf) * E/Vd)*1.0; 
		float CoCDiameter = (Vf - Vd) * E/Vd;

		// [0.5,1.0] pixel está atras do plano de foco
		// [0.5,0.0] pixel está na frente do plano de foco
		float CoCDiameterMapped = (CoCDiameter/maxCoCDiameter)/2 + 0.5;

		//tempImageDataPointerFinal[i] = ColorRGBAf( tempImageDataPointer[i] * (1 - (abs(CoCDiameterMapped-0.5)*2))*0.1, CoCDiameterMapped );
		tempImageDataPointerFinal[i] = ColorRGBAf( tempImageDataPointer[i] * 0.1, CoCDiameterMapped );
		//printf("CoC = %f\n", CoCDiameter);
	}

	// Atualiza textura
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, GL_RGBA, GL_FLOAT, tempImageDataPointerFinal);

	int directionFactor = 1;
	CoCBorderSet tempCoCBorderSet;
	for( int CoCSize = 2; CoCSize < 3; CoCSize -= directionFactor )
	//for( int CoCSize = 0; CoCSize < 3; CoCSize++ )
	{
		// A borda de um CoC de tamanho CoCSize
		CoCBorder tempCoCBorder = tempCoCBorderSet.getCoCBorder( CoCSize );

		if(directionFactor == 1)
		{
			glAlphaFunc(GL_GEQUAL, (CoCSize/maxCoCDiameter)/2 + 0.5);
			
			//glBlendFunc( GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA );
		}
		else
		{
			glAlphaFunc(GL_LEQUAL, (CoCSize/maxCoCDiameter)/2 + 0.5);

			//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		// Função de blending
		glBlendFunc( GL_ONE, GL_ONE );

		// Varre todos os pixels da borda do CoC anterior
		for( PixelPosition *CoCPixel = tempCoCBorder.next(); CoCPixel != NULL; CoCPixel = tempCoCBorder.next() )
		{
			// Quanto a coordenada da textura deve mudar a cada camanda desenhada
			float UOffset = 2* static_cast<float>(CoCPixel->x)/this->width;
			float VOffset = 2* static_cast<float>(CoCPixel->y)/this->height;

			// Desenha camada (cada camada é um plano colado com plano de projeção)
			glBegin( GL_QUADS );				

				glTexCoord2d( 0 + UOffset + (double)leftVertexsOffset/this->width, 1 + VOffset);				
				glVertex2f( 0 + leftVertexsOffset, 0 );

				glTexCoord2d( 1 + UOffset, 1 + VOffset );		
				glVertex2f( this->width, 0 );

				glTexCoord2d( 1 + UOffset, 0 + VOffset );		
				glVertex2f( this->width, this->height );
				
				glTexCoord2d( 0 + UOffset + (double)leftVertexsOffset/this->width, 0 + VOffset );		
				glVertex2f( 0 + leftVertexsOffset, this->height );
				
			glEnd();
		}

		// Se ja fez todos os CoC que estão atras do plano de foco entao faz agora os CoC que estão a frente
		if( CoCSize == 0 )
		{
			directionFactor = -1;
			break;
		}
	}

	glFlush();

	glDisable(GL_ALPHA_TEST);
}


void OGLRenderSystem::setSBTextureResolution( int aSBTextureSize )
{
	this->SBTextureSize = aSBTextureSize;
}