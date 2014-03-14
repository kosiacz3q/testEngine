/*
 * ResourcesManager.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "ResourcesManager.h"

ResourcesManager::ResourcesManager() {
	 textures = new  map_uid_pTexture();
	 models = new map_uid_pModel();
	 skeletons = new map_uid_pSkeleton();
}

ResourcesManager::~ResourcesManager() {
	for(auto i = textures->begin() ; i != textures->end(); ++i ){
		i->second->freeTexture();
		delete i->second;
	}

	delete textures;

	for(auto i = models->begin() ; i != models->end(); ++i ){
			delete i->second;
	}

	delete models;

	for(auto i = skeletons->begin() ; i != skeletons->end(); ++i ){


				for(auto outerIter = i->second->mountPoints->begin(); outerIter != i->second->mountPoints->end(); ++outerIter)
					for(auto innerIter = outerIter->second->begin(); innerIter != outerIter->second->end(); ++innerIter)
						delete[] innerIter->second;

				delete i->second;
	}

	delete skeletons;
}

