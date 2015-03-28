/*
 *  Geometry.h
 *  
 *
 *  Created by Samwell Freeman on 3/8/2015 for LucidTronix.
 * For instructions details and schematic, See:
 *   http://www.lucidtronix.com/products/11
 *
 */
#ifndef LucidGeometry_h
#define LucidGeometry_h

#define HUGE_VALUE 9e9

class Point
{
  public:
  	// Constructors
  	Point() : x(0), y(0), z(0) {};
  	Point(float _x, float _y) : x(_x), y(_y), z(0) {} // support use as 2d point too
  	Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} // direct initialization lil faster
  	
  	// Overloaded Operators
  	Point operator+(const Point &p){
  		Point s;
  		s.x = this->x + p.x; s.y = this->y + p.y; s.z = this->z + p.z;
  		return s;
  	}
  	Point operator-(const Point &p) const{
  		Point s;
  		s.x = this->x - p.x; s.y = this->y - p.y; s.z = this->z - p.z;
  		return s;
  	}

  	// Basic Vector Operations
  	float dot(const Point &p){
  		return this->x*p.x + this->y*p.y + this->z*p.z;
  	}
  	float angle(const Point &p){
  		Point tmp(*this);
  		return acos(tmp.dot(p) / (tmp.length()*p.length()));
  	}
  	Point cross(const Point &p){
  		Point s;
  		s.x = this->y*p.y - this->z*p.y;
  		s.y = -this->x*p.z + this->z*p.x;
  		s.z = this->x*p.y - this->y*p.x;
  		return s;
  	}
  	float length() const {
  		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
  	}
  	float distance(const Point &p){
  		Point tmp(*this);
  		tmp = tmp - p;
  		return tmp.length();
  	}

  	// Coordinate data is public for ease of access and to keep library lean
	float x, y, z;
};

class Line
{
  public:
  	Line(){}
  	Line(Point p0, Point p1) : p_start(p0), p_stop(p1) {}

  	Point normal() const{
      Point tmp = p_start - p_stop;
      return tmp;
  	}

  	bool intersect(Line &l, Point *ip){
  	  Point n1 = this->normal();
  	  Point n2 = l.normal();
  	  if(n1.dot(n2) == 1.0) return false; // The lines are parallel no intersection (or all intersection)	  
  	  float m1 = n1.x ? n1.y / n1.x : HUGE_VALUE;
  	  float m2 = n2.x ? n2.y / n2.x : HUGE_VALUE;
  	  float b1 = p_start.y - ((p_start.x*n1.y) / n1.x);
  	  float b2 = l.p_start.y - ((l.p_start.x*n2.y) / n2.x);
  	  ip->x = (b2-b1) / (m1-m2);
  	  ip->y = m1*ip->x + b1;
  	  return true;
  	}

    Point p_start;
    Point p_stop;
};


#endif