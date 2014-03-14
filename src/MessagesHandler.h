/*
 * MessagesHandler.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef MESSAGESHANDLER_H_
#define MESSAGESHANDLER_H_


#include <vector>
#include "msg/Message.h"
#include "ObjectContainer.h"

typedef std::vector<Message*> vec_pMsg;

// UID 0 is for mainGameInstance
class Game;

class MessagesHandler {
public:
	MessagesHandler();
	virtual ~MessagesHandler();

	vec_pMsg messages;
	Game* mainGame;

	void putMessage(Message* msg);
	void clearMessages();
	void handleMessages(map_UID_pObject* targetObjects);
};

#endif /* MESSAGESHANDLER_H_ */
