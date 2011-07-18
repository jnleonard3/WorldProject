/*
 * TextBox.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: Jon
 */

#include "TextBox.h"

#include <osg/StateSet>

TextBox::TextBox(const std::string& string):
textGeode(new osg::Geode()),
text(new osgText::Text()) {
	textGeode->addDrawable(text);
	text->setAxisAlignment(osgText::Text::SCREEN);
	text->setText(string);
	this->addChild(textGeode);
}

TextBox::~TextBox() {
	// TODO Auto-generated destructor stub
}

void TextBox::setText(const std::string& t){
    text->setText(t);
}

void TextBox::setFont(const std::string& font){
    text->setFont(font);
}

void TextBox::setColor(osg::Vec4d color){
    text->setColor(color);
}

void TextBox::setPosition(osg::Vec3d position){
    text->setPosition(position);
}

void TextBox::setTextSize(unsigned int size){
    text->setCharacterSize(size);
}
