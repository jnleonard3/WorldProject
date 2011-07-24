/*
 * CommonGeometry.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#include "CommonGeometry.h"

#include "math.h"

Point::Point():xVal(0),yVal(0),zVal(0) {
}

Point::Point(double x, double y, double z):xVal(x),yVal(y),zVal(z) {
}

Point Point::add(const Point& rhs) const {
	return Point(this->x()+rhs.x(),this->y()+rhs.y(),this->z()+rhs.z());
}

double Point::distance(const Point& rhs) const {
	return sqrt(pow(this->x()-rhs.x(),2)+pow(this->y()-rhs.y(),2)+pow(this->z()-rhs.z(),2));
}

Vector::Vector():iVal(0),jVal(0),kVal(0) {
}

Vector::Vector(double i, double j, double k):iVal(i),jVal(j),kVal(k) {
}

Vector::Vector(Point from, Point to):iVal(to.x()-from.x()),jVal(to.y()-from.y()),kVal(to.z()-from.z()) {
}

double Vector::dotProduct(const Vector& rhs) const {
	return this->i()*rhs.i() + this->j()*rhs.j() + this->k()*rhs.k();
}

Vector Vector::scale(double val) const {
	return Vector(this->i()*val,this->j()*val,this->k()*val);
}

Point Vector::translate(const Point& pt) const {
	return Point(pt.x()+this->i(),pt.y()+this->j(),pt.z()+this->k());
}

double Vector::magnitude() const {
	return sqrt(this->i()*this->i()+this->j()*this->j()+this->k()*this->k());
}

Vector Vector::normalize() const {
	return this->scale(1/this->magnitude());
}

Vector Vector::crossProduct(const Vector& rhs) const {
	return Vector(	this->j()*rhs.k()-rhs.j()*this->k(),
					this->k()*rhs.i()-rhs.k()*this->i(),
					this->i()*rhs.j()-rhs.i()*this->j());
}

double Vector::angleBetween(const Vector &rhs) const {
	Vector v1 = *this, v2 = rhs;

	double mag1 = this->magnitude();
	double mag2 = rhs.magnitude();

	if(mag1 != 1) {
		v1.scale(1/mag1);
	}

	if(mag2 != 1) {
		v2.scale(1/mag2);
	}

	return acos(v1.dotProduct(v2));
}

bool Vector::equals(const Vector &rhs, double precision) const {
	if(fabs(this->i() - rhs.i()) < precision) {
		if(fabs(this->j() - rhs.j()) < precision) {
			if(fabs(this->k() - rhs.k()) < precision) {
				return true;
			}
		}
	}
	return false;
}

Triangle::Triangle(Point one, Point two, Point three):first(one),second(two),third(three){
};

Triangle::Triangle(double sideLength) {
	double radius = (sqrt(3)/3.0)*sideLength;
	first = Point(0,radius,0);
	second = Point(radius*cos(3.665),radius*sin(3.665),0);
	third = Point(radius*cos(5.7596),radius*sin(5.7596),0);
}

Point Triangle::center() const {
	Vector midBottom(secondPoint(),thirdPoint());
	midBottom = midBottom.scale(0.5);
	Point bottomMidPoint = midBottom.translate(secondPoint());
	Vector midVector(bottomMidPoint,firstPoint());
	midVector = midVector.scale(0.33333);
	return midVector.translate(bottomMidPoint);
}

Vector Triangle::normal() const {
	Vector v1(first,second), v2(first,third);
	return v1.crossProduct(v2);
}
