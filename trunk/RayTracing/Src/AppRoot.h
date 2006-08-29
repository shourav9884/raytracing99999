#pragma once

#include "RayTracer.h"
#include "CameraController.h"
#include "ColorRGBf.h"
#include "FrameBuffer.h"

class AppRoot
{
private:
	RayTracer rayTracer;
	Scene scene;
	CameraController cameraController;

	// Buffer onde a imagem final será armazenada
	FrameBuffer *frameBuffer;

	///////////////////////////////////////////////////////////////////////////////////
	// Teclas do teclado
	///////////////////////////////////////////////////////////////////////////////////
	const static unsigned char keyFORWARD = 'w', keyBACKWARD = 's', keyLEFT = 'a', 
							   keyRIGHT = 'd', keyUP = 'r', keyDOWN = 'f';

	
	bool pressedKeyFORWARD, pressedKeyBACKWARD, pressedKeyLEFT, pressedKeyRIGHT, 
		 pressedKeyUP, pressedKeyDOWN;
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
};
