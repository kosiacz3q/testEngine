//============================================================================
// Name        : SomePlatformGame.cpp
// Author      : Lucas Edward Kosiak
// Version     : 0.0
// Copyright   :
// Description : Simple Platform Game , OpenGL , C++
//============================================================================

#include "Game.h"


int main(int argc, char **argv) {

	//<ENVIROMENT INIT>
	glutInit( & argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize( 800, 600);
	glutInitWindowPosition(250,100);

	glEnable( GL_DEPTH_TEST);

	glDepthFunc( GL_GREATER );

	glEnable(GL_ALPHA);
	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);

	glShadeModel (GL_SMOOTH);

	glutCreateWindow( "SomePlatformGame" );

	//glutEnterGameMode();



	ilInit();
	ilClearColour( 255, 255, 255, 000 );

		//<GLUT FUNCTIONS BINDING>
		glutIdleFunc( Game::update );
		glutReshapeFunc(Game::reshape);

		glutKeyboardFunc(Game::performKeyboardInput);
		glutSpecialFunc(Game::performSpecialKeyboardInput);
		glutMouseFunc(Game::performMouseAction);
		glutMotionFunc(Game::performMouseDragg);
		glutPassiveMotionFunc(Game::performMouseMove);
		//</GLUT FUNCTIONS BINDING>

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//</ENVIROMENT INIT>

	//<LOAD RESOURCES>
		Game::init();
		Game::loadGameFile("scripts/tutorialMap");
		Game::loadGameFile("scripts/skeleton_tut");
		Game::loadGameFile("scripts/textures");

		UID actualState =  hashFun("Tutorial");
		Game::actualGameState = Game::gameStates[actualState];
		UID actualScene = hashFun("Scene1");
		Game::actualGameState->actualScene = Game::actualGameState->scenes[actualScene];
	//</LOAD RESOURCES>

	Game::initClock();
	glutMainLoop();

	Game::close();

	printf("[SUCCESFULL EXIT]\n");

	return 0;
}
