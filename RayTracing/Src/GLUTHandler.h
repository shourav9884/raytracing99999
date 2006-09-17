#pragma once

#include "glut.h"
#include "AppRoot.h"
#include "TimeCounter.h"

class GLUTHandler
{
private: // Atributos
	static AppRoot *listener;
	static bool showFPS;
	static int windowWidth;
	static int windowHeight;
	
private:
	// CallBacks
	static void displayFunc( );
	static void idleFunc( );
	static void reshapeFunc( int aWidth, int aHeight  );
	static void keyboardFunc(unsigned char key, int x, int y);
	static void keyboardUpFunc(unsigned char key, int x, int y);
	static void motionFunc( int x, int y );
	static void mouseFunc( int button, int state, int x, int y );

	//
	static void registerCallBacks( );
	static void printFPS(double aDeltaTime);

public:

	static void startGLUT( int argc, char** args, int width = 640, int height = 480 );
	static void setListener( AppRoot *listener );
};