/*
 * MessageLogger.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#include "MessageLogger.h"

#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

#include <OpenThreads/Thread>

MessageLogger* MessageLogger::instance = 0;

struct MessageNode {
	MessageNode *next, *prev;
	char * message;
};

class TextUpdateCallback : public osg::Drawable::Drawable::UpdateCallback {
public:
	TextUpdateCallback(MessageNode *&rootNode, osgText::Text *&osgtext):
		frameSkip(0),
		rootMessageNode(rootNode),
		text(osgtext)
	{

	}

	virtual void update(osg::NodeVisitor*, osg::Drawable*)
	{
		frameSkip++;
		if(frameSkip > 500) {
			MessageNode *mNode = rootMessageNode;
			unsigned int size =
					MessageLogger::getInstance()->getMessageBufferSize();
			std::string string = "";

			while (mNode != 0 && size > 0) {
				string = std::string(mNode->message) + "\n" + string;
				size--;
				mNode = mNode->prev;
			}

			if (mNode == 0) {
				std::string emptySpace;
				while (size > 0) {
					emptySpace += "\n";
					size--;
				}
				string = emptySpace + string;
			} else if (size == 0) {
				mNode->next->prev = 0;
				while (mNode != 0) {
					MessageNode *next = mNode->prev;
					delete mNode->message;
					delete mNode;
					mNode = next;
				}
			}
			text->setText(string);
			frameSkip = 0;
		}
	}

private:
	unsigned int frameSkip;
	MessageNode *&rootMessageNode;
	osgText::Text *&text;
};

MessageLogger* MessageLogger::getInstance() {
	if(instance == 0) {
		instance = new MessageLogger();
	}
	return instance;
}

void MessageLogger::print(std::string msg) {
	MessageLogger::getInstance()->printMessage(msg);
}

osg::Group* MessageLogger::getGroup() {
	return MessageLogger::getInstance()->textGroup;
}

unsigned int MessageLogger::getMessageBufferSize() {
	return messageBufferSize;
}

MessageLogger::MessageLogger():
		textGroup(new osg::Group()),
		textGeode(new osg::Geode()),
		text(new osgText::Text()),
		rootMessageNode(0),
		messageBufferSize(20)
{
    text->setFont("VeraSe.ttf");
    text->setCharacterSize(14.0);
    messageBufferSize = (1060/text->getCharacterHeight());

    text->setPosition(osg::Vec3(10,10+messageBufferSize*text->getCharacterHeight(),0));

    text->setText("");
    text->setUpdateCallback(new TextUpdateCallback(rootMessageNode,text));

    textGeode->addDrawable(text);

    textGroup->addChild(textGeode);
}

MessageLogger::~MessageLogger() {
}

void MessageLogger::printMessage(std::string msg) {
	MessageNode *newNode = new MessageNode();
	newNode->message = new char[msg.size()+1];
	strcpy(newNode->message, msg.c_str());
	newNode->next = 0;
	while(true) {
		if(rootMessageNode == 0) {
			newNode->prev = 0;
			bool res = __sync_bool_compare_and_swap(&rootMessageNode, 0, newNode);
			if(res == true) {
				break;
			}
		} else {
			newNode->prev = rootMessageNode;
			bool res = __sync_bool_compare_and_swap(&rootMessageNode, rootMessageNode, newNode);
			if(res == true) {
				newNode->prev->next = newNode;
				break;
			}
		}
	}
}
