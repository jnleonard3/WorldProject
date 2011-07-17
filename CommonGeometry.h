/*
 * CommonGeometry.h
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#ifndef COMMONGEOMETRY_H_
#define COMMONGEOMETRY_H_

class Point {
public:
	Point();
	Point(double x, double y, double z);

	double x() const { return xVal; };
	void x(double x){ xVal = x; };

	double y() const { return xVal; };
	void y(double y){ xVal = y; };

	double z() const { return zVal; };
	void z(double z){ zVal = z; };

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

	Point firstPoint() const { return first; };

	Point secondPoint() const { return second; };

	Point thirdPoint() const { return third; };

	Plane toPlane() const;

private:
	Point first, second, third;
};

#endif /* COMMONGEOMETRY_H_ */
