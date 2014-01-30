/*
 * CommonGeometry.h
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#ifndef COMMONGEOMETRY_H_
#define COMMONGEOMETRY_H_

#include "MessageLogger.h"

class Point {
public:
	Point();
	Point(double x, double y, double z);

	double x() const { return xVal; };
	void x(double x){ xVal = x; };

	double y() const { return yVal; };
	void y(double y){ yVal = y; };

	double z() const { return zVal; };
	void z(double z){ zVal = z; };

	Point add(const Point& rhs) const;

	double distance(const Point& rhs) const;

	friend MessageLogger& operator<<(MessageLogger &stream, const Point pt){
		stream << "(" << pt.x() << "," << pt.y() << "," << pt.z() << ")";
		return stream;
	};

private:
	double xVal, yVal, zVal;
};

class Vector {
public:
	Vector();
	Vector(double i, double j, double k);
	Vector(Point from, Point to);

	double i() const { return iVal; };
	void i(double i){ iVal = i; };

	double j() const { return jVal; };
	void j(double j){ jVal = j; };

	double k() const { return kVal; };
	void k(double k){ kVal = k; };

	double dotProduct(const Vector& rhs) const;
	
	Vector scale(double val) const;
	
	Point translate(const Point& pt) const;

	double magnitude() const;

	Vector normalize() const;

	Vector crossProduct(const Vector& rhs) const;

	double angleBetween(const Vector &rhs) const;

	bool equals(const Vector &rhs, double precision) const;

	friend MessageLogger& operator<<(MessageLogger &stream, const Vector vec){
		stream << "[" << vec.i() << "," << vec.j() << "," << vec.k() << "]";
		return stream;
	};

private:
	double iVal, jVal, kVal;
};

class Plane {
public:
	Plane(Point point, Vector first, Vector second);

private:
	Point origin;
	Vector v1, v2;
};

class Triangle {
public:
	Triangle(){};
	Triangle(Point one, Point two, Point three);
	Triangle(double sideLength);

	Point firstPoint() const { return first; };
	void firstPoint(Point pt) { first = pt; };

	Point secondPoint() const { return second; };
	void secondPoint(Point pt) { second = pt; };

	Point thirdPoint() const { return third; };
	void thirdPoint(Point pt) { third = pt; };

	Point center() const;

	Plane toPlane() const;

	Vector normal() const;

private:
	Point first, second, third;
};

#endif /* COMMONGEOMETRY_H_ */
