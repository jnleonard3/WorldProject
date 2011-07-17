/*
 * CommonGeometry.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#include "CommonGeometry.h"

Point::Point():xVal(0),yVal(0),zVal(0) {
}

Point::Point(double x, double y, double z):xVal(x),yVal(y),zVal(z) {
}

Vector::Vector():iVal(0),jVal(0),kVal(0) {
}

Vector::Vector(double i, double j, double k):iVal(i),jVal(j),kVal(k) {
}

Vector::Vector(Point from, Point to):iVal(to.x()-from.x()),jVal(to.y()-from.y()),kVal(to.z()-from.z()) {
}

Triangle::Triangle(Point one, Point two, Point three):first(one),second(two),third(three){
};
