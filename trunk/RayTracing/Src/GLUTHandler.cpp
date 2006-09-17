
#include "GLUTHandler.h"

#include "OGLRenderSystem.h"
#include <cstdio>

// Inicializacao dos atributos
AppRoot *GLUTHandler::listener;
bool GLUTHandler::showFPS = true;
int GLUTHandler::windowWidth;
int GLUTHandler::windowHeight;


// Definicao das funcoes

void GLUTHandler::displayFunc( )
{
	glutSwapBuffers(); // Alternar entre o back e o front buffer
}

void GLUTHandler::idleFunc( )
{
	double deltaTime = TimeCounter::getDeltaTime();

	GLUTHandler::listener->idleFunc( deltaTime );

	printFPS(deltaTime);

	glutSwapBuffers(); // Alternar entre o back e o front buffer
}

void GLUTHandler::printFPS(double aDeltaTime)
{
	// Imprime na tela o FPS
	if( GLUTHandler::showFPS )
	{
		// Faz com que o FPS nao altere a cada frame impresso (facilita na hora de ver)
		////////////////////////////////////////////////
		static double timeBuffer = 0;
		timeBuffer += aDeltaTime;

		static double deltaTimeUsed = aDeltaTime;

		if( timeBuffer >= 0.2 )
		{
			deltaTimeUsed = aDeltaTime;
			timeBuffer = 0;
		}
		////////////////////////////////////////////////

		const int stringLenght = 13;

		char stringFPS[stringLenght];
		sprintf_s( stringFPS, "FPS = %.3f", (1.0/deltaTimeUsed) );

		glDisable(GL_TEXTURE_2D);
		glColor3f(1,0,1);
		glRasterPos2i(2,GLUTHandler::windowHeight-5);

		for( int i = 0; i < stringLenght-2; i++ )
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , stringFPS[i] );		
		}
	}
}

void GLUTHandler::reshapeFunc( int aWidth, int aHeight  )
{
	OGLRenderSystem &renderSystem = OGLRenderSystem::getSingleton( );

	renderSystem.reshapeCanvas( aWidth, aHeight );
}
void GLUTHandler::keyboardFunc(unsigned char key, int x, int y)
{	
	GLUTHandler::listener->keyboardFunc(key, x, y);
}

void GLUTHandler::keyboardUpFunc(unsigned char key, int x, int y)
{	
	GLUTHandler::listener->keyboardUpFunc(key, x, y);
}

void GLUTHandler::motionFunc( int x, int y )
{
	GLUTHandler::listener->motionFunc(x, y);
}

void GLUTHandler::mouseFunc( int button, int state, int x, int y )
{
	GLUTHandler::listener->mouseFunc(button, state, x, y);
}

void GLUTHandler::registerCallBacks( )
{
	glutDisplayFunc( &GLUTHandler::displayFunc );
	glutIdleFunc( &GLUTHandler::idleFunc );
	glutKeyboardFunc( &GLUTHandler::keyboardFunc );
	glutKeyboardUpFunc( &GLUTHandler::keyboardUpFunc );
	glutReshapeFunc( &GLUTHandler::reshapeFunc );

	// mouse
	glutMotionFunc( motionFunc );
	glutMouseFunc( mouseFunc );
}

void GLUTHandler::startGLUT( int argc, char** args, int aWidth, int aHeight )
{
	GLUTHandler::windowWidth = aWidth;
	GLUTHandler::windowHeight = aHeight;

	// Inicializa o Glut
	glutInit( &argc, args);

	// Modo que será inicializado
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

	// Posição inicial da janela
	glutInitWindowPosition( 10, 10 );	

	glutInitWindowSize( aWidth, aHeight );

	// Cria a janela
	glutCreateWindow( "RayTracing v0.00001" );

	registerCallBacks();

	OGLRenderSystem::getSingleton().init(aWidth, aHeight);

	glutMainLoop();
}

void GLUTHandler::setListener( AppRoot *listener )
{
	GLUTHandler::listener = listener;
}