/*
 * Game.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "Game.h"
#include "misc/Colors.h"
#include "misc/materials.h"

#include "misc/pugi/pugixml.hpp"


map_UID_pGameState Game::gameStates;
MessagesHandler* Game::messagesHandler;
GameState* Game::actualGameState;
Timer* Game::gameMainTimer ;
DisplayManager* Game::drawer;


void Game::update(){

	//TODO control

	//<messages Handling>
	messagesHandler->handleMessages( actualGameState->actualScene->objectContainer->objects );
	//</messages Handling>

	//<UPDATING OBJECTS>
	int timeElapsed = gameMainTimer->getNonZeroMSTimeElapsedSinceLastMeasurement();

	for(map_UID_pObject::iterator iter = actualGameState->actualScene->objectContainer->objects->begin();
			iter != actualGameState->actualScene->objectContainer->objects->end();
			++iter){
		iter->second->update(timeElapsed);
	}

	//</UPDATING OBJECTS>

	//<DRAWING>
	drawer->display(actualGameState->actualScene , actualGameState->resources );
	//</DRAWING>
}

void Game::reshape( int width, int height ){
	// obszar renderingu - całe okno
	glViewport( 0, 0, width, height );

	// wybór macierzy rzutowania
	glMatrixMode( GL_PROJECTION );

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// obliczenie aspektu obrazu z uwzględnieniem
	// przypadku, gdy wysokość obrazu wynosi 0
	GLdouble aspect = 1;
	if( height > 0 )
		 aspect = width /( GLdouble ) height;

	// rzutowanie perspektywiczne
	gluPerspective( 90, aspect, 1.0, 5.0 );
}

void Game::checkCollisions(){
	//TODO
}

void Game::loadGameFile(char* path){

	int steps = 0;
	printf("%i.[Loading File] %s\n" , steps++ , path);

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(path);

	printf("%i.[initial] %s\n" ,steps++, result.description());

	//<gameState name>
	pugi::xml_node root = doc.child("GameState");

	UID gameStateUID = hashFun(root.child("Name").child_value());

	if(Game::gameStates.find( gameStateUID ) == Game::gameStates.end())
		Game::gameStates[gameStateUID] = new GameState(); //creating new game state

	printf("%i.[gameState name]  %s\n" , steps++, root.child("Name").child_value());
	//</gameState name>

	//<scene>
	pugi::xml_node sceneRoot = root.child("Scenes");
	for (pugi::xml_node actualScene = sceneRoot.first_child(); actualScene; actualScene = actualScene.next_sibling()){
		//<scene name>
		printf("%i.[SceneName] ================ %s ===============\n" , steps++ , actualScene.child("Name").child_value());
		//</scene name>
		UID sceneID = hashFun(actualScene.child("Name").child_value() );

		if(Game::gameStates[gameStateUID]->scenes.find(sceneID) == Game::gameStates[gameStateUID]->scenes.end())
			Game::gameStates[gameStateUID]->scenes[sceneID] = new Scene(); //creating new scene

		//<camera >
		pugi::xml_node cameraRoot = actualScene.child("CameraStartPosition");
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.x = (float)toReal(cameraRoot.child("x").child_value());
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.y = (float)toReal(cameraRoot.child("y").child_value());
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.z = (float)toReal(cameraRoot.child("z").child_value());

		printf("%i.		[Camera Position] %f %f %f\n" , steps++ ,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.x,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.y,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->position.z);

		pugi::xml_node cameraLookPointRoot = actualScene.child("CameraLookPoint");
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.x = (float)toReal(cameraLookPointRoot.child("x").child_value());
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.y = (float)toReal(cameraLookPointRoot.child("y").child_value());
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.z = (float)toReal(cameraLookPointRoot.child("z").child_value());

		printf("%i.		[Camera LookPoint] %f %f %f\n" , steps++ ,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.x,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.y,
			Game::gameStates[gameStateUID]->scenes[sceneID]->camera->lookPoint.z);

		float cameraScale =  toReal( actualScene.child("CameraScale").child_value());
		if(cameraScale == 0)
			cameraScale = 1;
		printf("%i.		[Camera Scale] %f\n" , steps++ , cameraScale);
		Game::gameStates[gameStateUID]->scenes[sceneID]->camera->scale = cameraScale;
		//</camera >

		//<loading objects>
		pugi::xml_node objectsRoot = actualScene.child("Objects");

		for (pugi::xml_node actualObject = objectsRoot.child("Object"); actualObject; actualObject = actualObject.next_sibling("Object"))
		{
			printf("%i.		[Object Name] %s\n" , steps++ , actualObject.child("Name").child_value());
			UID objectUID = hashFun(  actualObject.child("Name").child_value());
			printf("%i			[Object UID] %u\n", steps++ , objectUID );
			printf("%i.			[Object Type] %s\n" , steps++ , actualObject.child("Type").child_value());
			pugi::xml_node positionRoot = actualObject.child("Position");
			Vector3f objectPosition;
			objectPosition.x = toReal( positionRoot.child("x").child_value() );
			objectPosition.y = toReal( positionRoot.child("y").child_value() );
			objectPosition.z = toReal( positionRoot.child("z").child_value() );
			printf("%i.			[Object Position] %f %f %f\n" , steps++ ,
																objectPosition.x,
																objectPosition.y,
																objectPosition.z);
			Vector2f dimension;
			dimension.x = (float)toReal(actualObject.child("Dimensions").child("x").child_value());
			dimension.y = (float)toReal(actualObject.child("Dimensions").child("y").child_value());
			printf("%i.			[Dimensions] x:%f y:%f\n" , steps++ , dimension.x , dimension.y);


			Vector3f rotation;
			rotation.x = (float)toReal(actualObject.child("Rotation").child("x").child_value());
			rotation.y = (float)toReal(actualObject.child("Rotation").child("y").child_value());
			rotation.z = (float)toReal(actualObject.child("Rotation").child("z").child_value());
			printf("%i.			[Rotation] x:%f y:%f z:%f\n" , steps++ , rotation.x , rotation.y , rotation.z);

			bool visible = (int)toReal(actualObject.child("Visible").child_value()) == 1 ? true : false;
			printf("%i.			[Visibility] %s\n" , steps++ , visible ? "true" : "false");


			if( strcmp( actualObject.child("Type").child_value() , "PlainTexture") == 0  ){

				UID textureUID = hashFun(actualObject.child("TextureID").child_value() );

				printf("%i.			[TextureHandler] %s (%u)\n" , steps++ , actualObject.child("TextureID").child_value() ,textureUID ) ;
				Objects::PlainTexture* plainTexture = new Objects::PlainTexture();
				plainTexture->dimensions = dimension;
				plainTexture->position = objectPosition;
				plainTexture->rotation = rotation;
				plainTexture->textureUID = textureUID;
				plainTexture->visible = visible;
				(*Game::gameStates[gameStateUID]->scenes[sceneID]->objectContainer->objects)[objectUID] = plainTexture;

			}else if( strcmp(actualObject.child("Type").child_value() , "TerrainBlock") == 0 ){
				Objects::TerrainBlock* terrainBlock = new Objects::TerrainBlock();
				terrainBlock->dimensions = dimension;
				terrainBlock->position = objectPosition;
				terrainBlock->visible = visible;

				terrainBlock->frontTextureID = hashFun(actualObject.child("frontTextureID").child_value() );
				terrainBlock->leftTextureID = hashFun(actualObject.child("leftTextureID").child_value() );
				terrainBlock->rightTectureID = hashFun(actualObject.child("rightTectureID").child_value() );
				terrainBlock->upperTextureID = hashFun(actualObject.child("upperTextureID").child_value() );
				terrainBlock->brickModelID = hashFun(actualObject.child("brickModelID").child_value() );

				printf("%i.			[frontTextureID] %s (%u)\n" , steps++ , actualObject.child("frontTextureID").child_value() ,terrainBlock->frontTextureID ) ;
				printf("%i.			[leftTextureID] %s (%u)\n" , steps++ , actualObject.child("leftTextureID").child_value() ,terrainBlock->leftTextureID ) ;
				printf("%i.			[rightTectureID] %s (%u)\n" , steps++ , actualObject.child("rightTectureID").child_value() ,terrainBlock->rightTectureID ) ;
				printf("%i.			[upperTextureID] %s (%u)\n" , steps++ , actualObject.child("upperTextureID").child_value() ,terrainBlock->upperTextureID ) ;
				printf("%i.			[brickModelID] %s (%u)\n" , steps++ , actualObject.child("brickModelID").child_value() ,terrainBlock->brickModelID ) ;

				(*Game::gameStates[gameStateUID]->scenes[sceneID]->objectContainer->objects)[objectUID] = terrainBlock;

			}else if(strcmp( actualObject.child("Type").child_value() , "PlainAnimation") == 0){
				Objects::PlainAnimation* animation = new Objects::PlainAnimation();
				animation->dimensions = dimension;
				animation->position = objectPosition;
				animation->visible = visible;

				animation->textureID = hashFun( actualObject.child("textureID").child_value() );
				animation->duration_total = (int)toReal( actualObject.child("duration_total").child_value() );
				animation->duration_perFrame = (int)toReal( actualObject.child("duration_perFrame").child_value() );
				animation->fixedStart = (int)toReal( actualObject.child("fixedStart").child_value() );

				(*Game::gameStates[gameStateUID]->scenes[sceneID]->objectContainer->objects)[objectUID] = animation;

			}else if(strcmp( actualObject.child("Type").child_value() , "LightSource") == 0){
				Objects::LightSource* tmpLight = new Objects::LightSource();
				tmpLight->position = objectPosition;
				tmpLight->dimensions = dimension;
				tmpLight->visible = visible;

				float isGlobal = toReal( actualObject.child("isSpotLight").child_value());
				tmpLight->lightPosition[0] = objectPosition.x;
				tmpLight->lightPosition[1] = objectPosition.y;
				tmpLight->lightPosition[2] = objectPosition.z;
				tmpLight->lightPosition[3] = isGlobal;

				printf("%i.			[LightPosition] [%f , %f , %f , %f]\n" , steps++ , tmpLight->lightPosition[0] ,tmpLight->lightPosition[1] ,tmpLight->lightPosition[2] ,tmpLight->lightPosition[3]);
				printf("%i.			[LightType] %s\n" , steps++ , (((int)(isGlobal)) ? "spotlight" : "global"));

				pugi::xml_node tmp_crosscut = actualObject.child("ambient");
				tmpLight->ambient[0] = toReal(tmp_crosscut.child("p1").child_value());
				tmpLight->ambient[1] = toReal(tmp_crosscut.child("p2").child_value());
				tmpLight->ambient[2] = toReal(tmp_crosscut.child("p3").child_value());
				tmpLight->ambient[3] = toReal(tmp_crosscut.child("p4").child_value());
				printf("%i.			[Ambient] [%f , %f , %f , %f]\n" , steps++ , tmpLight->ambient[0] ,tmpLight->ambient[1] ,tmpLight->ambient[2] ,tmpLight->ambient[3]);

				tmp_crosscut = actualObject.child("diffuse");
				tmpLight->diffuse[0] = toReal(tmp_crosscut.child("p1").child_value());
				tmpLight->diffuse[1] = toReal(tmp_crosscut.child("p2").child_value());
				tmpLight->diffuse[2] = toReal(tmp_crosscut.child("p3").child_value());
				tmpLight->diffuse[3] = toReal(tmp_crosscut.child("p4").child_value());
				printf("%i.			[Diffuse] [%f , %f , %f , %f]\n" , steps++ , tmpLight->diffuse[0] ,tmpLight->diffuse[1] ,tmpLight->diffuse[2] ,tmpLight->diffuse[3]);

				tmp_crosscut = actualObject.child("specular");
				tmpLight->specular[0] = toReal(tmp_crosscut.child("p1").child_value());
				tmpLight->specular[1] = toReal(tmp_crosscut.child("p2").child_value());
				tmpLight->specular[2] = toReal(tmp_crosscut.child("p3").child_value());
				tmpLight->specular[3] = toReal(tmp_crosscut.child("p4").child_value());
				printf("%i.			[Specular] [%f , %f , %f , %f]\n" , steps++ , tmpLight->specular[0] ,tmpLight->specular[1] ,tmpLight->specular[2] ,tmpLight->specular[3]);

				tmp_crosscut = actualObject.child("spotDirection");
				tmpLight->spotDirection[0] = toReal(tmp_crosscut.child("p1").child_value());
				tmpLight->spotDirection[1] = toReal(tmp_crosscut.child("p2").child_value());
				tmpLight->spotDirection[2] = toReal(tmp_crosscut.child("p3").child_value());
				printf("%i.			[SpotDirection] [%f , %f , %f]\n" , steps++ , tmpLight->spotDirection[0] ,tmpLight->spotDirection[1] ,tmpLight->spotDirection[2] );

				tmp_crosscut = actualObject.child("spotExponent");
				tmpLight->spotExponent = toReal(tmp_crosscut.child("p1").child_value());

				printf("%i.			[SpotExponent] [%f]\n" , steps++ , tmpLight->spotExponent);

				tmp_crosscut = actualObject.child("spotCutoff");
				tmpLight->spotCutoff = toReal(tmp_crosscut.child("p1").child_value());
				printf("%i.			[SpotCutoff] [%f]\n" , steps++ , tmpLight->spotCutoff);

				(*Game::gameStates[gameStateUID]->scenes[sceneID]->objectContainer->lights)[objectUID] = tmpLight;

			}else if(strcmp( actualObject.child("Type").child_value() , "Doll") == 0){
				Objects::Doll* doll = new Objects::Doll();

				pugi::xml_node bodyPartsRoot =  actualObject.child("bodyParts");

				doll->position = objectPosition;
				doll->dimensions = dimension;
				doll->visible = visible;
				doll->actualSkeletonID = hashFun( actualObject.child("defaultSkeletonID").child_value() );

				printf("%i.			[DefaultSkeleton] name: %s (%u) \n" , steps++ , actualObject.child("defaultSkeletonID").child_value() , doll->actualSkeletonID );

				for (pugi::xml_node actualBodyPart = bodyPartsRoot.child("part"); actualBodyPart; actualBodyPart = actualBodyPart.next_sibling("part")){
					UID bodyPartUID = hashFun( actualBodyPart.child("name").child_value());
					UID bodyPartTextureUID = hashFun( actualBodyPart.child("textureID").child_value());

					Vector2f dimm;
					dimm.x = toReal( actualBodyPart.child("Dimensions").child("x").child_value() );
					dimm.y = toReal( actualBodyPart.child("Dimensions").child("y").child_value() );

					printf("%i.			[BodyPart] name: %s (%u) \n" , steps++ , actualBodyPart.child("name").child_value(), bodyPartUID );
					printf("%i.				[Texture] %u\n" , steps++ ,  bodyPartTextureUID);
					printf("%i.				[Dimensions] x:%f y:%f\n" , steps++ , dimm.x , dimm.y);

					(*doll->bodyParts)[bodyPartUID].first = bodyPartTextureUID;
					(*doll->bodyParts)[bodyPartUID].second = dimm;
				}

				(*Game::gameStates[gameStateUID]->scenes[sceneID]->objectContainer->objects)[objectUID] = doll;

			}else{
				printf("%i[Undefined Object Type] %s\n", steps++ , actualObject.child("Type").child_value());
			}
		}
		//</loading objects>


		}
		//</scene>

		//<textures>
		pugi::xml_node texturesRoot = root.child("Textures");

		for (pugi::xml_node actualTexture = texturesRoot.child("Texture"); actualTexture; actualTexture = actualTexture.next_sibling("Texture")){
			printf("%i.[Texture]\n" , steps++);
			Resource::Texture* tex = new Resource::Texture();

			UID textureUID = hashFun(actualTexture.child("Name").child_value());
			printf("%i.		[Name] %s (%u)\n" , steps++ , actualTexture.child("Name").child_value() , textureUID);
			printf("%i.		[Path] %s\n" , steps++ , actualTexture.child("Path").child_value());


			if(!tex->loadTextureFromFile( actualTexture.child("Path").child_value() )){
				printf("%i		[ERROR WHILE LOADING TEXTURE] %s (%u)\n" , steps++ , actualTexture.child("Name").child_value() , textureUID);
			}

			(*Game::gameStates[gameStateUID]->resources->textures)[textureUID] = tex;

		}
		//</textures>

		//<models>
		pugi::xml_node modelsRoot = root.child("Models");
		for (pugi::xml_node actualModel = modelsRoot.child("Model"); actualModel; actualModel = actualModel.next_sibling("Model")){
				printf("%i.[Model]\n" , steps++);

				UID modelID = hashFun(actualModel.child("Name").child_value());
				printf("%i.		[Name] %s (%i)\n" , steps++ , actualModel.child("Name").child_value() , modelID);
				Resource::Model* model = new Resource::Model();

				model->vertices[0].x =  (float)toReal(actualModel.child("_1").child("x").child_value());
				model->vertices[0].y =  (float)toReal(actualModel.child("_1").child("y").child_value());
				model->vertices[0].z =  (float)toReal(actualModel.child("_1").child("z").child_value());

				model->vertices[1].x =  (float)toReal(actualModel.child("_2").child("x").child_value());
				model->vertices[1].y =  (float)toReal(actualModel.child("_2").child("y").child_value());
				model->vertices[1].z =  (float)toReal(actualModel.child("_2").child("z").child_value());

				model->vertices[2].x =  (float)toReal(actualModel.child("_3").child("x").child_value());
				model->vertices[2].y =  (float)toReal(actualModel.child("_3").child("y").child_value());
				model->vertices[2].z =  (float)toReal(actualModel.child("_3").child("z").child_value());

				model->vertices[3].x =  (float)toReal(actualModel.child("_4").child("x").child_value());
				model->vertices[3].y =  (float)toReal(actualModel.child("_4").child("y").child_value());
				model->vertices[3].z =  (float)toReal(actualModel.child("_4").child("z").child_value());

				model->vertices[4].x =  (float)toReal(actualModel.child("_5").child("x").child_value());
				model->vertices[4].y =  (float)toReal(actualModel.child("_5").child("y").child_value());
				model->vertices[4].z =  (float)toReal(actualModel.child("_5").child("z").child_value());

				model->vertices[5].x =  (float)toReal(actualModel.child("_6").child("x").child_value());
				model->vertices[5].y =  (float)toReal(actualModel.child("_6").child("y").child_value());
				model->vertices[5].z =  (float)toReal(actualModel.child("_6").child("z").child_value());

				model->vertices[6].x =  (float)toReal(actualModel.child("_7").child("x").child_value());
				model->vertices[6].y =  (float)toReal(actualModel.child("_7").child("y").child_value());
				model->vertices[6].z =  (float)toReal(actualModel.child("_7").child("z").child_value());

				model->vertices[7].x =  (float)toReal(actualModel.child("_8").child("x").child_value());
				model->vertices[7].y =  (float)toReal(actualModel.child("_8").child("y").child_value());
				model->vertices[7].z =  (float)toReal(actualModel.child("_8").child("z").child_value());

				for(int i = 0; i < 8; ++i)
					printf("%i.		[Coord %i] [%f.%f,%f]\n" , steps++ , i , model->vertices[i].x , model->vertices[i].y ,model->vertices[i].z);

				(*Game::gameStates[gameStateUID]->resources->models)[modelID] = model;

		}
		//</models>


		//<Skeletons>
		pugi::xml_node skeletonsRoot = root.child("Skeletons");
		for (pugi::xml_node actualSkeleton= skeletonsRoot.child("Skeleton"); actualSkeleton; actualSkeleton = actualSkeleton.next_sibling("Skeleton")){
			printf("%i.[Skeleton]\n" , steps++);

			Resource::Skeleton* skeleton = new Resource::Skeleton();

			UID skeletonID = hashFun( actualSkeleton.child("Name").child_value());
			printf("%i.		[Name] %s (%u)\n" , steps++ , actualSkeleton.child("Name").child_value() , skeletonID);

			skeleton->LCMofAnimTimes = toReal(actualSkeleton.child("AnimTime").child_value() );
			printf("%i.		[AnimationTotalTime] %i\n" , steps++ , skeleton->LCMofAnimTimes );
			printf("%i.		[Parts]\n" , steps++ );
			for (pugi::xml_node actualPart= actualSkeleton.child("parts").child("part"); actualPart; actualPart = actualPart.next_sibling("part")){
				UID partUID = hashFun(actualPart.child("name").child_value());
				(*skeleton->mountPoints)[partUID] = new vpipf();
				(*skeleton->mountPoints)[partUID]->clear();

				printf("%i.			[partName] %s (%u)\n" , steps++ , actualPart.child("name").child_value() , partUID);
				for (pugi::xml_node actualTimeSpan= actualPart.child("position"); actualTimeSpan; actualTimeSpan = actualTimeSpan.next_sibling("position")){
					float* tab = new float[4];
					int time;
					tab[0] = toReal(actualTimeSpan.child("x").child_value());
					tab[1] = toReal(actualTimeSpan.child("y").child_value());
					tab[2] = toReal(actualTimeSpan.child("z").child_value());
					tab[3] = toReal(actualTimeSpan.child("r").child_value());

					time = (int)toReal(actualTimeSpan.child("time").child_value());


					printf("%i.				[time] %i\n" , steps++ , time);
					printf("%i.				[position] [%f,%f,%f] \n" , steps++  , tab[0] , tab[1] , tab[2]);
					printf("%i.				[rotation] [%f] \n" , steps++  , tab[3] );

					(*skeleton->mountPoints)[partUID]->push_back( pipf( time , tab  ) );
				}
			}

			(*Game::gameStates[gameStateUID]->resources->skeletons)[skeletonID] = skeleton;
		}

		//</Skeletons>

	printf("%i.[EOF] %s\n" , steps, path);
}

void Game::changeGameState(UID newGameStateID ){
	//TODO
}


void Game::init(){
	messagesHandler = new MessagesHandler();
	Objects::Object::msgHandler = messagesHandler;
	drawer = new DisplayManager();
	actualGameState = nullptr;
	gameMainTimer = nullptr;
}

void Game::close(){

	for(auto i = gameStates.begin(); i != gameStates.end(); ++i){
		delete i->second;
	}
	gameStates.clear();

	delete messagesHandler;
	delete drawer;
}

void Game::performKeyboardInput( unsigned char key, int x, int y ){

	if( (int)key < 97)
        key += 32;

    switch( key )
    {
        case 'q':
        case 'Q':
        	glutLeaveMainLoop();
        	break;

        default: break;
    }
}

void Game::performSpecialKeyboardInput(  int key, int x, int y  ){

	//mainBrick->controlInfo->glutKey = (short)key;
	switch(key){
	case GLUT_KEY_LEFT:
		actualGameState->actualScene->camera->position.x -= 0.1;
		actualGameState->actualScene->camera->lookPoint.x -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		actualGameState->actualScene->camera->position.x += 0.1;
		actualGameState->actualScene->camera->lookPoint.x += 0.1;
		break;
	case GLUT_KEY_UP:
		actualGameState->actualScene->camera->position.y += 0.1;
		actualGameState->actualScene->camera->lookPoint.y += 0.1;
		break;
	case GLUT_KEY_DOWN:
		actualGameState->actualScene->camera->position.y -= 0.1;
		actualGameState->actualScene->camera->lookPoint.y -= 0.1;
		break;
	default: break;
	}

}

void Game::performMouseDragg( int x, int y ){
	/*
	mouse.setMousePosition(x , y);

	mainBrick->mainBrick->rotation.x -= (mouse.lastPosition.x - mouse.actualPosition.x);
	mainBrick->mainBrick->rotation.y -= (mouse.lastPosition.y - mouse.actualPosition.y);
	*/
}

void Game::performMouseAction(int button, int state, int x, int y){
    /*
	if(button == GLUT_LEFT_BUTTON)
    	mouse.leftButtonState = state;
    else if(button == GLUT_RIGHT_BUTTON )
    	mouse.rightButtonState = state;

    mouse.setMousePosition(x , y);
    */
}

void Game::performMouseMove( int x, int y ){
	//mouse.setMousePosition(x , y);
}

void Game::initClock(){
	gameMainTimer = new Timer();
}

Game::Game() {

}

Game::~Game() {

}
