#pragma once

#include "RayTracer.h"
#include "CameraController.h"
#include "ColorRGBf.h"
#include "FrameBuffer.h"
#include "Filter.h"

class AppRoot
{
private:
	RayTracer rayTracer;
	Scene scene;
	CameraController cameraController;
	Filter *filter;

	// Variaveis que controlam o specular bloom
	bool SBEnable;
	bool SBFullScreen;
	int SBSamples;
	float SBmaxSpreadFactor;
	float SBIntensity;

	// Buffer onde a imagem final será armazenada
	FrameBuffer *frameBuffer;

	///////////////////////////////////////////////////////////////////////////////////
	// Teclas do teclado
	///////////////////////////////////////////////////////////////////////////////////
	const static unsigned char keyFORWARD = 'w', keyBACKWARD = 's', keyLEFT = 'a', 
							   keyRIGHT = 'd', keyUP = 'r', keyDOWN = 'f';

	
	bool pressedKeyFORWARD, pressedKeyBACKWARD, pressedKeyLEFT, pressedKeyRIGHT, 
		 pressedKeyUP, pressedKeyDOWN;

	float velocity;
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	// Botoes do mouse
	///////////////////////////////////////////////////////////////////////////////////
	bool pressedButtonLEFT, pressedButtonRIGHT;
	int xOldPosition, yOldPosition;
	///////////////////////////////////////////////////////////////////////////////////

private:
	void handleKeyboardInputs( double deltaTime );

public:
	AppRoot(void);
	~AppRoot(void);

	void init( int argc, char **args );

	// CallBacks
	void idleFunc( double deltaTime );
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void motionFunc( int x, int y );
	void mouseFunc( int button, int state, int x, int y );

	void setSBEnable( bool aEnable )
	{
		this->SBEnable = aEnable;
	}

	void setSBFullScreen( bool aFullScreen )
	{
		this->SBFullScreen = aFullScreen;
	}

	void setSBSamples( int aSamples )
	{
		this->SBSamples = aSamples;
	}

	void setSBmaxSpreadFactor( float aMaxSpreadFactor )
	{
		this->SBmaxSpreadFactor = aMaxSpreadFactor;
	}

	void setSBIntensity( float aIntensity )
	{
		this->SBIntensity = aIntensity;
	}
};
