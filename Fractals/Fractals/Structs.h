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
    double red, green, blue; 
};

struct ColorPoint
{
    double x, y, r, g, b; 

    ColorPoint::ColorPoint(double xpnt, double ypnt, double rcol, double gcol, double bcol)
    {
        x = xpnt;
        y = ypnt; 
        r = rcol;
        g = gcol; 
        b = bcol; 
    }

    ColorPoint::ColorPoint()
    {
        ColorPoint(0, 0, 0, 0, 0); 
    }
};

#endif