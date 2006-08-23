#include "AppRoot.h"

#include "GLUTHandler.h"
#include "Scene.h"

#include "Filter.h"
#include "Image.h"
#include "Sphere.h"
#include "Plane.h"
#include "Quaternion.h"

#include <cstdio>
using namespace std;

AppRoot::AppRoot(void)
: width(200), 
height(200), 
pressedKeyFORWARD(false),
pressedKeyBACKWARD(false),
pressedKeyLEFT(false),
pressedKeyRIGHT(false),
pressedKeyUP(false),
pressedKeyDOWN(false),
pressedButtonLEFT(false),
pressedButtonRIGHT(false)
{
	this->frameBuffer = new FrameBuffer(this->width, this->height);
}

AppRoot::~AppRoot(void)
{
	delete[] this->frameBuffer;
}

void AppRoot::init( int argc, char **args )
{
	Quaternion tempQuaternion(3.14/4,Vector3D(1,0,0));

	Vector3D tempVector(0,0,1);
	tempVector.normalize();
	
	Vector3D resultVector = tempQuaternion.rotate(tempVector);
	resultVector.normalize();

	int i = 0;

	//Image image1("images/teste1.bmp");

	//ILubyte *imageData = image1.getImageData();
	//for( int i = 0; i < image1.getWidth() * image1.getHeight() * image1.getBytesPerPixel(); i ++ )
	//{
	//	printf("%u, ", *imageData);

	//	imageData++;
	//}

	//printf("\n\n");
	//for( int y = 0; y < image1.getHeight(); y++ )
	//{
	//	printf("{");
	//	for( int x = 0; x <image1.getWidth(); x++ )
	//	{
	//		PixelRGBub pixel = image1.getPixel(x, y);

	//		printf("{%u,", pixel.r );
	//		printf("%u,", pixel.g );
	//		printf("%u} ", pixel.b );
	//	}
	//	printf("}\n");
	//}


	this->rayTracer.init( );
	this->scene.init( );
	this->cameraController.setCamera( &this->scene.getCamera() );

	// Inicializa o GLUT (sistema de janelas)
	GLUTHandler::setListener( this );
	GLUTHandler::startGLUT( argc, args, this->width, this->height);
	////////////////////////////////////////////////////////////
	// ESTE TRECHO S� � ALCANCADO QUANDO O PROGRAMA � FINALIZADO
	////////////////////////////////////////////////////////////
}

void AppRoot::idleFunc( double deltaTime )
{
	// Executa ray tracing
	this->rayTracer.executeRayTracer( this->width, this->height, this->frameBuffer, &scene );

	//Filter::scanImage( this->frameBuffer->colorBuffer, this->width, this->height, 3);

	GLUTHandler::drawPixels( this->width, this->height, this->frameBuffer->colorBuffer );

	this->handleKeyboardInputs( deltaTime );

	/////////////////////////////////////////////////////////////////////////////////////
	// Lixo
	////////////////////////////////////////////////////////////////////////////////////
	static float angle = 0;
	angle += 0.1;
	float alplitude = 4;

	Light * light =  scene.getSceneLights().at(0);
	light->setWorldPosition(Vector3D(alplitude*sin(angle),alplitude*cos(angle)+5,-3));	
	/////////////////////////////////////////////////////////////////////////////////////
}

void AppRoot::handleKeyboardInputs( double deltaTime )
{	
	float offset = 0.1;

	// Translacoes
	if( this->pressedKeyFORWARD )		
		this->cameraController.moveOverVector(offset, CameraController::VECTOR_N );		
	if( this->pressedKeyBACKWARD )
		this->cameraController.moveOverVector(-offset, CameraController::VECTOR_N );
	if( this->pressedKeyLEFT )
		this->cameraController.moveOverVector(offset, CameraController::VECTOR_U );
	if( this->pressedKeyRIGHT )
		this->cameraController.moveOverVector(-offset, CameraController::VECTOR_U );
	if( this->pressedKeyUP )
		this->cameraController.moveOverVector(offset, CameraController::VECTOR_V );
	if( this->pressedKeyDOWN )
		this->cameraController.moveOverVector(-offset, CameraController::VECTOR_V );
}

void AppRoot::keyboardFunc(unsigned char key, int x, int y)
{
	switch( key )
	{
	case AppRoot::keyFORWARD:
		this->pressedKeyFORWARD = true;
		break;
	case AppRoot::keyBACKWARD:
		this->pressedKeyBACKWARD = true;
		break;
	case AppRoot::keyLEFT:
		this->pressedKeyLEFT = true;
		break;
	case AppRoot::keyRIGHT:
		this->pressedKeyRIGHT = true;
		break;
	case AppRoot::keyUP:
		this->pressedKeyUP = true;
		break;
	case AppRoot::keyDOWN:
		this->pressedKeyDOWN = true;
		break;
	}
	//printf("Pressed = %c\n", key);
}

void AppRoot::keyboardUpFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case AppRoot::keyFORWARD:
		this->pressedKeyFORWARD = false;
		break;
	case AppRoot::keyBACKWARD:
		this->pressedKeyBACKWARD = false;
		break;
	case AppRoot::keyLEFT:
		this->pressedKeyLEFT = false;
		break;
	case AppRoot::keyRIGHT:
		this->pressedKeyRIGHT = false;
		break;
	case AppRoot::keyUP:
		this->pressedKeyUP = false;
		break;
	case AppRoot::keyDOWN:
		this->pressedKeyDOWN = false;
		break;

	default:
		break;
	}
	//printf("Released = %c\n", key);
}

void AppRoot::motionFunc( int x, int y )
{
	float degree = 1;
	float rad = 2*3.1415*degree/360.0;

	// Deltas
	int deltaX = (x - this->xOldPosition);
	int deltaY = (y - this->yOldPosition);

	if( this->pressedButtonLEFT )
	{
		//
		this->cameraController.rotateAroundVector( -deltaX*rad, CameraController::VECTOR_V );
		this->cameraController.rotateAroundVector( deltaY*rad, CameraController::VECTOR_U );
		
		this->xOldPosition = x;
		this->yOldPosition = y;
	}
	else if( this->pressedButtonRIGHT )
	{
		//
		this->cameraController.rotateAroundVector( deltaX*rad, CameraController::VECTOR_N );
		
		this->xOldPosition = x;
	}

	//printf("MotionFunc\n");
}

void AppRoot::mouseFunc( int button, int state, int x, int y )
{
	// Se for o botao esquerdo
	if( button == GLUT_LEFT_BUTTON )
	{
		// Se soltou o botao
		if( state == GLUT_UP )
		{
			this->pressedButtonLEFT = false;
		}
		else
		{
			this->xOldPosition = x;
			this->yOldPosition = y;

			this->pressedButtonLEFT = true;
			//printf( "xLEFTClick = %i, yLEFTClick = %i\n", this->xOldPosition, this->yOldPosition );
		}
	}
	else if( button == GLUT_RIGHT_BUTTON )
	{
		if( state == GLUT_UP )
		{
			this->pressedButtonRIGHT = false;
		}
		else
		{
			this->xOldPosition = x;

			this->pressedButtonRIGHT = true;
			//printf( "xRIGHTClick = %i\n", this->xOldPosition );
		}
	}
	//printf("MouseFunc\n");
}
