#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct Point
{
	double x, y;

    Point::Point(double dx, double dy)
    {
        x = dx; 
        y = dy; 
    }

    Point::Point()
    {
        Point(0, 0); 
    }
};

struct TransformMatrix
{
	double a, b, c, d, e, f;
};

#endif