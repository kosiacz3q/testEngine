/*
 * DisplayManager.cpp
 *
 *  Created on: 26 Jan 2014
 *      Author: lucas
 */

#include "DisplayManager.h"

DisplayManager::DisplayManager() {
	lightID[0] = GL_LIGHT0;
	lightID[1] = GL_LIGHT1;
	lightID[2] = GL_LIGHT2;
	lightID[3] = GL_LIGHT3;
	lightID[4] = GL_LIGHT4;
	lightID[5] = GL_LIGHT5;
	lightID[6] = GL_LIGHT6;
	lightID[7] = GL_LIGHT7;

}

DisplayManager::~DisplayManager() {

}

void DisplayManager::display(Scene* contextScene, ResourcesManager* contextResourceManager){
	//<for switch temp var>
		Objects::PlainTexture* _tmp_plainTexture = nullptr;
		Objects::TerrainBlock* _tmp_terrainBlock = nullptr;
		Objects::PlainAnimation* _tmp_plainAnimation = nullptr;
		Objects::Doll* _tmp_doll = nullptr;
		Resource::Model* _tmp_model = nullptr;
		//Resource::Texture* _tmp_texture = nullptr;
		map_uid_pTexture::iterator _tmp_map_uid_pTexture_iter;

		//</for switch temp var>

		//<set up buffer>
		glClearColor( 1.0, 1.0, 1.0, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glMatrixMode( GL_MODELVIEW );

		glEnable( GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glAlphaFunc(GL_GREATER, 0.5);
		glEnable(GL_ALPHA_TEST);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		contextScene->camera->setVision();
		//</set up buffer>

		//<LIGHTING SECTION>
		glEnable(GL_LIGHTING);


		for(int i = 0; i < 8; ++i)
			availableLights[i] = true;
		//availableLights[0] = false;

		int actualLightNum = 0;


		for(map_UID_lights::iterator iter = contextScene->objectContainer->lights->begin(); iter != contextScene->objectContainer->lights->end(); ++iter){
			if(iter->second->visible){

				while( !availableLights[actualLightNum] )
					++actualLightNum;
				availableLights[actualLightNum] = false;

				glEnable( lightID[actualLightNum] );

				glLightfv( lightID[actualLightNum] , GL_POSITION       , iter->second->lightPosition  );
				glLightfv( lightID[actualLightNum] , GL_AMBIENT        , iter->second->ambient );
				glLightfv( lightID[actualLightNum] , GL_SPECULAR       , iter->second->specular );
				glLightfv( lightID[actualLightNum] , GL_DIFFUSE        , iter->second->diffuse);
				glLightf(  lightID[actualLightNum] , GL_SPOT_EXPONENT  , iter->second->spotExponent );
				glLightfv( lightID[actualLightNum] , GL_SPOT_DIRECTION , iter->second->spotDirection );
				glLightf(  lightID[actualLightNum] , GL_SPOT_CUTOFF    , iter->second->spotCutoff );

				//additional
				glLightf( lightID[actualLightNum], GL_CONSTANT_ATTENUATION, 1 );
				glLightf( lightID[actualLightNum], GL_LINEAR_ATTENUATION, 0 );
				glLightf( lightID[actualLightNum], GL_QUADRATIC_ATTENUATION, 0 );
			}

		}
		//</LIGHTING SECTION>

		glNormal3f(0,0,1);

		for(map_UID_pObject::iterator i = contextScene->objectContainer->objects->begin();
			i != contextScene->objectContainer->objects->end();
			++i){

			if(i->second->visible){
				glPushMatrix();

				glTranslatef(i->second->position.x , i->second->position.y , i->second->position.z );

				glRotatef(i->second->rotation.x , 0. , 1. , 0.);
			    glRotatef(i->second->rotation.y , 1. , 0. , 0.);
			    glRotatef(i->second->rotation.z , 0. , 0. , 1.);

				glColor4fv(Colors::Transparent);

				switch (i->second->type) {
					case Objects::ObjectType::ACTOR :
						//TODO actor displaying
						break;

					case Objects::ObjectType::TERRAIN_BLOCK:
						_tmp_terrainBlock = (Objects::TerrainBlock*)(i->second);
						_tmp_model = (*contextResourceManager->models)[_tmp_terrainBlock->brickModelID];

						//<front>
						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_terrainBlock->frontTextureID]->mTextureID);

						//glMaterialfv(GL_FRONT, GL_DIFFUSE, Materials::mat_specular);
						//TODO maybe some materials handling

						glBegin(GL_QUADS);
							//glNormal3f(0 , 0 , 1);
							glTexCoord2f (0.0, 0.0);
							glVertex3f (_tmp_model->vertices[0].x , _tmp_model->vertices[0].y , _tmp_model->vertices[0].z); //upper left
							glTexCoord2f (1.0, 0.0);
							glVertex3f (_tmp_model->vertices[1].x , _tmp_model->vertices[1].y , _tmp_model->vertices[1].z); //upper right
							glTexCoord2f (1.0, 1.0);
							glVertex3f (_tmp_model->vertices[2].x , _tmp_model->vertices[2].y , _tmp_model->vertices[2].z); //bottom right
							glTexCoord2f (0.0, 1.0);
							glVertex3f (_tmp_model->vertices[3].x , _tmp_model->vertices[3].y , _tmp_model->vertices[3].z); //bottom left
						glEnd();

						//<left>
						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_terrainBlock->leftTextureID]->mTextureID);

						glBegin(GL_QUADS);
							glTexCoord2f (0.0, 0.0);
							glVertex3f (_tmp_model->vertices[4].x , _tmp_model->vertices[4].y , _tmp_model->vertices[4].z); //upper left
							glTexCoord2f (1.0, 0.0);
							glVertex3f (_tmp_model->vertices[0].x , _tmp_model->vertices[0].y , _tmp_model->vertices[0].z); //upper right
							glTexCoord2f (1.0, 1.0);
							glVertex3f (_tmp_model->vertices[3].x , _tmp_model->vertices[3].y , _tmp_model->vertices[3].z); //bottom right
							glTexCoord2f (0.0, 1.0);
							glVertex3f (_tmp_model->vertices[5].x , _tmp_model->vertices[5].y , _tmp_model->vertices[5].z); //bottom left
						glEnd();

						//<right>
						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_terrainBlock->rightTectureID]->mTextureID);

						glBegin(GL_QUADS);
							glTexCoord2f (0.0, 0.0);
							glVertex3f (_tmp_model->vertices[1].x , _tmp_model->vertices[1].y , _tmp_model->vertices[1].z); //upper left
							glTexCoord2f (1.0, 0.0);
							glVertex3f (_tmp_model->vertices[6].x , _tmp_model->vertices[6].y , _tmp_model->vertices[6].z); //upper right
							glTexCoord2f (1.0, 1.0);
							glVertex3f (_tmp_model->vertices[7].x , _tmp_model->vertices[7].y , _tmp_model->vertices[7].z); //bottom right
							glTexCoord2f (0.0, 1.0);
							glVertex3f (_tmp_model->vertices[2].x , _tmp_model->vertices[2].y , _tmp_model->vertices[2].z); //bottom left
						glEnd();

						//<up>
						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_terrainBlock->upperTextureID]->mTextureID);

						glBegin(GL_QUADS);
							glTexCoord2f (0.0, 0.0);
							glVertex3f (_tmp_model->vertices[4].x , _tmp_model->vertices[4].y , _tmp_model->vertices[4].z); //upper left
							glTexCoord2f (1.0, 0.0);
							glVertex3f (_tmp_model->vertices[6].x , _tmp_model->vertices[6].y , _tmp_model->vertices[6].z); //upper right
							glTexCoord2f (1.0, 1.0);
							glVertex3f (_tmp_model->vertices[1].x , _tmp_model->vertices[1].y , _tmp_model->vertices[1].z); //bottom right
							glTexCoord2f (0.0, 1.0);
							glVertex3f (_tmp_model->vertices[0].x , _tmp_model->vertices[0].y , _tmp_model->vertices[0].z); //bottom left
						glEnd();

						glBindTexture(GL_TEXTURE_2D , 0);

					break;

					case Objects::ObjectType::PLAIN_TEXTURE:
						_tmp_plainTexture = (Objects::PlainTexture*)(i->second);

						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_plainTexture->textureUID]->mTextureID);

						glBegin(GL_QUADS);
							glTexCoord2f (0.0, 0.0);
							glVertex3f (0 , 0 , 0); //upper left
							glTexCoord2f (1.0, 0.0);
							glVertex3f (_tmp_plainTexture->dimensions.x , 0 , 0); //upper right
							glTexCoord2f (1.0, 1.0);
							glVertex3f (_tmp_plainTexture->dimensions.x , -_tmp_plainTexture->dimensions.y , 0); //bottom right
							glTexCoord2f (0.0, 1.0);
							glVertex3f (0 , -_tmp_plainTexture->dimensions.y , 0); //bottom left
						glEnd();

						glBindTexture(GL_TEXTURE_2D , 0);
						break;

					case Objects::ObjectType::PLAIN_ANIMATION:{
						_tmp_plainAnimation = (Objects::PlainAnimation*)(i->second);

						glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[_tmp_plainAnimation->textureID]->mTextureID);

						float parts = 1. / ( _tmp_plainAnimation->duration_total / _tmp_plainAnimation->duration_perFrame );
						int actualPart = ( (_tmp_plainAnimation->elapsedTime + _tmp_plainAnimation->fixedStart) % _tmp_plainAnimation->duration_total ) / _tmp_plainAnimation->duration_perFrame;

						glBegin(GL_QUADS);
							//glTexCoord2f (0.0, 0.0);
							glTexCoord2f( actualPart * parts , 0 );
							glVertex3f (0 , 0 , 0); //upper left
							//glTexCoord2f (1.0, 0.0);
							glTexCoord2f( (actualPart + 1) * parts , 0 );
							glVertex3f (_tmp_plainAnimation->dimensions.x , 0 , 0); //upper right
							//glTexCoord2f (1.0, 1.0);
							glTexCoord2f( (actualPart + 1) * parts , 1 );
							glVertex3f (_tmp_plainAnimation->dimensions.x , -_tmp_plainAnimation->dimensions.y , 0); //bottom right
							//glTexCoord2f (0.0, 1.0);
							glTexCoord2f( (actualPart ) * parts , 1 );

							glVertex3f (0 , -_tmp_plainAnimation->dimensions.y , 0); //bottom left
						glEnd();

						glBindTexture(GL_TEXTURE_2D , 0);
					}break;

					case Objects::ObjectType::DOLL :{
						_tmp_doll = (Objects::Doll*)(i->second);

						Resource::Skeleton* skeleton = (*contextResourceManager->skeletons)[_tmp_doll->actualSkeletonID];

						for(auto iter = _tmp_doll->bodyParts->begin(); iter != _tmp_doll->bodyParts->end(); ++iter){
							glBindTexture(GL_TEXTURE_2D , (*contextResourceManager->textures)[iter->second.first]->mTextureID);

							glPushMatrix();

							Vector4f mp = skeleton->getMountPoint(iter->first , 0 , _tmp_doll->movementElapsedTime );

							glTranslatef(mp.x , mp.y , mp.z );

							glRotatef(mp.w , 0. , 0. , 1.);

							glBegin(GL_QUADS);
								glTexCoord2f (0.0, 0.0);
								glVertex3f (0 , 0 , 0); //upper left
								glTexCoord2f (1.0, 0.0);
								glVertex3f (iter->second.second.x, 0 , 0); //upper right
								glTexCoord2f (1.0, 1.0);
								glVertex3f (iter->second.second.x , -iter->second.second.y , 0); //bottom right
								glTexCoord2f (0.0, 1.0);
								glVertex3f (0 , -iter->second.second.y , 0); //bottom left
							glEnd();

							glPopMatrix();

							glBindTexture(GL_TEXTURE_2D , 0);
						}

					}break;

					default:

						break;
				}
				glPopMatrix();

			}
		}
		glFlush();
		glutSwapBuffers();
}
