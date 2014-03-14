/*
 * Message.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#include "Message.h"


Message::Message(UID from , UID to , MSG_TYPE::type msgType) {
	this->to = to;
	this->from = from;
	this->type = msgType;
}

Message::~Message() {

}

