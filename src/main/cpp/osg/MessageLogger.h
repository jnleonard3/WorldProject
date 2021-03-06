/*
 * MessageLogger.h
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#ifndef MESSAGELOGGER_H_
#define MESSAGELOGGER_H_

#include <osg/Group>
#include <osg/Geode>
#include <osgText/Text>

#include <string>

struct MessageNode;

class MessageLogger {
public:
	static MessageLogger& getInstance();

	static void print(std::string msg);

	static osg::Group* getGroup();

	unsigned int getMessageBufferSize();

	MessageLogger& operator<< (bool val);
	MessageLogger& operator<< (unsigned int val);
	MessageLogger& operator<< (double val);
	MessageLogger& operator<< (const char * val);

private:
	static MessageLogger* instance;

	MessageLogger();
	virtual ~MessageLogger();

	void printMessage(std::string msg);

	osg::Group* textGroup;

	osg::Geode* textGeode;

	osgText::Text* text;

	std::string bufferMsg;

	MessageNode* rootMessageNode;

	unsigned int messageBufferSize;
};

#endif /* MESSAGELOGGER_H_ */
