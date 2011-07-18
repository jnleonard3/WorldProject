/*
 * TextBox.h
 *
 *  Created on: Jul 17, 2011
 *      Author: Jon
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <string>
#include <osgText/Text>
#include <osg/Geode>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/Transform>

class TextBox: public osg::Group {
public:
	TextBox(const std::string& string);
	virtual ~TextBox();

	void setText(const std::string& text);
	void setFont(const std::string& font);

	void setColor(osg::Vec4d color);

	void setPosition(osg::Vec3d position);
	void setTextSize(unsigned int size);
private:

	osg::Geode * textGeode;

	osgText::Text * text;
};

#endif /* TEXTBOX_H_ */
