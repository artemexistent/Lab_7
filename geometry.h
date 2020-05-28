#include<stdio.h>
#include<math.h>
#include<iostream>
#include<fstream>

using namespace std;



void profile();
void close();


class Triangle;
class Line;
class Section;

class Math;



class Point{
	
	public:
		Point();
		Point(double x1, double y1);
		
		double getX();
		double getY();
		
		void operator = (Point& p1);
		bool operator == (const Point& p1);
		
		friend istream& operator >> (istream& in, Point& p);
		friend ostream& operator << (ostream& os, Point& p);
		
		friend Triangle;				
		friend Line;
		friend Math;
		friend Section;
		
	private:
		double x, y;
	
};



class Triangle{
	
	public:
		Triangle();
		Triangle(Point a1, Point a2, Point p3);
		void setTriangle(Point a1, Point a2, Point p3);
		
		Point getP1();
		Point getP2();
		Point getP3();
	
		friend istream& operator >> (istream& in, Triangle& T);
		friend ostream& operator << (ostream& os, Triangle& T);
		
		friend Math;
		
	private:
		Point p1, p2, p3;
			
};

class Line{
	public:
		Line();
		Line(Point a1, Point a2);
		void setLine(Point a1, Point a2);
		
		double getA();
		double getB();
		double getC();
		
		friend istream& operator >> (istream& in, Line& L);
		friend ostream& operator << (ostream& os, Line& L);
		
		friend Triangle;
		friend Math;
		
	private:
		double A, B, C;
			
};


class Section{
	public:
		Section();
		Section(Point a1, Point a2);
		void setSection(Point a1, Point a2);
		
		Point getP1();
		Point getP2();
		
		bool pointOnSection(Point p);
		
		friend istream& operator >> (istream& in, Section& S);
		friend ostream& operator << (ostream& os, Section& S);
		
		friend Math;
	
	private:
		Point p1, p2;
};

class Math{
	
	public:
		static const double EPS = 1e-6;
		
		static double min3(double a, double b, double c);
		static double det(double a, double b, double c, double d);
		
		static bool intersect(Line m, Line n, Point & res);
		static bool parallel(Line m, Line n);
		static bool equivalent(Line m, Line n);
		
		static bool checkCrossSectionAndLine(Section S, Line L);
		static bool checkCrossTriangleAndLine(Triangle T, Line L);
		static double distancePointToLine(Point P, Line L);
		
		static double distanceTriangleToLine(Triangle T, Line L);

};
