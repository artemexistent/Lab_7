#include <iostream>
#include <cmath>

#include "geometry.h"

using namespace std;



/*
	About me
*/

void profile (){
	cout << "Calculate distance from Triangle to Line" << endl;
	cout << "Input : " << endl;
	cout << "  first 3 lines define vertices of Triangle" << endl;
	cout << "  next, every 2 lines define a Line, " << endl;
	cout << "  the distance to that if needed to calculate" << endl;
	cout << "  (if Triangle and Line intersect, then answer = 0)" << endl;
	cout << "====================================================" << endl;
	cout << endl << endl;
}

void close(){
	cout << "END" << endl;
}




/*
	class Point
*/

Point::Point(){
	x = 0.0;
	y = 0.0;
}

Point::Point(double x1, double y1){
	x = x1;
	y = y1;
}

double Point::getX(){
	return x;
}

double Point::getY(){
	return y;
}

void Point::operator = (Point& p1){
	x = p1.getX();
	y = p1.getY();
}

bool Point::operator == (const Point& p1){
	return (x == p1.x && y == p1.y);
}






/*
	class Triangle
*/

Triangle::Triangle(){
	Point a1(0, 0); p1 = a1;
	Point a2(1, 0); p2 = a2;
	Point a3(0, 1); p3 = a3;
}

Triangle::Triangle(Point a1, Point a2, Point a3){
	p1 = a1;
	p2 = a2;
	p3 = a3;
}

void Triangle::setTriangle(Point a1, Point a2, Point a3){
	p1 = a1;
	p2 = a2;
	p3 = a3;
}

Point Triangle::getP1(){
	return p1;
}

Point Triangle::getP2(){
	return p2;
}

Point Triangle::getP3(){
	return p3;
}




/*
	class Line
*/

Line::Line(){
	A = 1;
	B = 2;
	C = 3;
}

Line::Line(Point a1, Point a2){
	A = a1.y - a2.y;
	B = a2.x - a1.x;
	C = -A*a1.x - B*a1.y;
}

void Line::setLine(Point a1, Point a2){
	A = a1.y - a2.y;
	B = a2.x - a1.x;
	C = -A*a1.x - B*a1.y;
}

double Line::getA(){
	return A;
}

double Line::getB(){
	return B;
}

double Line::getC(){
	return C;
}







/*
	class Section
*/


Section::Section(){
	Point a1(0, 0); p1 = a1;
	Point a2(1, 1); p2 = a2;
}

Section::Section(Point a1, Point a2){
	p1 = a1;
	p2 = a2;
}

void Section::setSection(Point a1, Point a2){
	p1 = a1;
	p2 = a2;
}

Point Section::getP1(){
	return p1;
}

Point Section::getP2(){
	return p2;
}

bool Section::pointOnSection(Point P){
	return (min(p1.x, p2.x) <= P.x
		 && max(p1.x, p2.x) >= P.x
		 && min(p1.y, p2.y) <= P.y
		 && max(p1.y, p2.y) >= P.y);
}








/*
	class Math
*/

double Math::min3(double a, double b, double c){
	return min (a, min (b, c));
}

double Math::det (double a, double b, double c, double d) {
	return a * d - b * c;
}

bool Math::intersect (Line m, Line n, Point & res) {
	double zn = det (m.A, m.B, n.A, n.B);
	if (fabs (zn) < EPS)
		return false;
	res.x = - det (m.C, m.B, n.C, n.B) / zn;
	res.y = - det (m.A, m.C, n.A, n.C) / zn;
	return true;
}

bool Math::parallel (Line m, Line n) {
	return fabs (det (m.A, m.B, n.A, n.B)) < EPS;
}

bool Math::equivalent (Line m, Line n) {
	return fabs (det (m.A, m.B, n.A, n.B)) < EPS
		&& fabs (det (m.A, m.C, n.A, n.C)) < EPS
		&& fabs (det (m.B, m.C, n.B, n.C)) < EPS;
}

bool Math::checkCrossSectionAndLine(Section S, Line L){

	Line fakeS(S.p1, S.p2);

	if (Math::equivalent(fakeS, L))
		return true;

	if (Math::parallel(fakeS, L))
		return false;

	Point res;
	Math::intersect(fakeS, L, res);

	return S.pointOnSection(res);
}

bool Math::checkCrossTriangleAndLine(Triangle T, Line L){
	Section s1(T.p1, T.p2);
	Section s2(T.p1, T.p3);
	Section s3(T.p2, T.p3);

	return(Math::checkCrossSectionAndLine(s1, L)
		|| Math::checkCrossSectionAndLine(s2, L)
		|| Math::checkCrossSectionAndLine(s3, L));

}

double Math::distancePointToLine(Point P, Line L){
	return fabs (P.x * L.A + P.y * L.B + L.C) / sqrt (L.A*L.A + L.B*L.B);
}

double Math::distanceTriangleToLine(Triangle T, Line L){

	if (Math::checkCrossTriangleAndLine(T, L))
		return 0;

	return min3(Math::distancePointToLine(T.p1, L), Math::distancePointToLine(T.p2, L), Math::distancePointToLine(T.p3, L));

}








/*
	overload operators >> and << for classes :
		Point,
		Triangle,
		Line,
		Section.
*/

istream& operator >> (istream& in, Point& p){
	in >> p.x >> p.y;
	return in;
}

ostream& operator << (ostream& out, Point& p){
    return out << "<Point> : (" << p.x << ", " << p.y << ")";
}

istream& operator >> (istream& in, Triangle& T){
	Point a1, a2, a3;
	in >> a1;
	in >> a2;
	in >> a3;
	T.setTriangle(a1, a2, a3);
	return in;
}

ostream& operator << (ostream& out, Triangle& T){
	out << "<Triangle> : (" << T.p1 << ", " << T.p2 << ", " << T.p3 << ")";
	return out;
}

istream& operator >> (istream& in, Line& L){
	Point a1, a2;
	in >> a1;
	in >> a2;
	L.setLine(a1, a2);
	return in;
}

ostream& operator << (ostream& out, Line& L){
	out << "<Line> : (" << L.A << ", " << L.B << ", " << L.C << ")";
	return out;
}


istream& operator >> (istream& in, Section& S){
	Point a1, a2;
	in >> a1;
	in >> a2;
	S.setSection(a1, a2);
	return in;
}

ostream& operator << (ostream& out, Section& S){
	out << "<Section> : (" << S.p1 << ", " << S.p2 << ")";
	return out;
}




