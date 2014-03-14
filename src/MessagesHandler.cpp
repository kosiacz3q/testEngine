/*
 * MessagesHandler.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "MessagesHandler.h"

MessagesHandler::MessagesHandler() {
	mainGame = nullptr;
}

MessagesHandler::~MessagesHandler() {

	for(auto i = messages.begin(); i != messages.end(); ++i){
		delete *i;
	}
	messages.clear();
}

void MessagesHandler::putMessage(Message* msg){
	messages.push_back(msg);
}

void MessagesHandler::clearMessages(){
	messages.clear();
}

void MessagesHandler::handleMessages(map_UID_pObject* targetObjects){
	for(vec_pMsg::iterator i = messages.begin(); i != messages.end(); ++i){
		( (*targetObjects)[(*i)->to] )->getMessage(*i);
		delete *i;
	}

	messages.clear();
}
