/*
 * Game.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "misc/hashFun.h"
#include "misc/TypeHandlers.h"
#include "misc/Model.h"
#include "misc/Timer.h"

#include "DisplayManager.h"

typedef std::map<UID , GameState*> map_UID_pGameState;

class Game {
public:
	static map_UID_pGameState gameStates;
	static MessagesHandler* messagesHandler;
	static GameState* actualGameState;
	static DisplayManager* drawer;
	static Timer* gameMainTimer;

	static void init();
	static void close();


	static void checkCollisions();
	static void loadGameFile(char* path);
	static void changeGameState(UID newGameStateID );
	static void initClock();

	//GLUT's methods
	static void reshape( int width, int height );
	static void update();
	static void performMouseMove( int x, int y );
	static void performMouseAction(int button, int state, int x, int y);
	static void performMouseDragg( int x, int y );
	static void performSpecialKeyboardInput(  int key, int x, int y  );
	static void performKeyboardInput( unsigned char key, int x, int y );

private:
	Game();
	virtual ~Game();
};

#endif /* GAME_H_ */
