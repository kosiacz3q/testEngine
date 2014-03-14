/*
 * ResourcesManager.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef RESOURCESMANAGER_H_
#define RESOURCESMANAGER_H_

#include <map>
#include "misc/Texture.h"
#include "misc/Model.h"
#include "misc/Skeleton.h"
#include "MessagesHandler.h"

typedef std::map<UID, Resource::Texture*> map_uid_pTexture;
typedef std::map<UID, Resource::Model*> map_uid_pModel;
typedef std::map<UID, Resource::Skeleton*> map_uid_pSkeleton;

class ResourcesManager {
public:
	ResourcesManager();

	map_uid_pTexture* textures;
	map_uid_pModel* models;
	map_uid_pSkeleton* skeletons;

	virtual ~ResourcesManager();
};

#endif /* RESOURCESMANAGER_H_ */
