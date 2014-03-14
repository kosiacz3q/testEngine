/*
 * Message.h
 *
 *  Created on: Jan 18, 2014
 *      Author: lucas
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

typedef unsigned int UID;

namespace MSG_TYPE{
	enum type{
		NORMAL = 0,
	};
}

class Message {
public:
	Message(UID from , UID to , MSG_TYPE::type msgType);
	virtual ~Message();

	MSG_TYPE::type type;
	UID from;
	UID to;
};

#endif /* MESSAGE_H_ */
