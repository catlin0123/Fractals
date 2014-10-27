/*************************************************************************//**
* @file
*
* @brief This file contains the definition of the structures used throughout
* the program. 
****************************************************************************/
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

/*!
* @brief A point in double coordinates. 
*/
struct Point
{
	double x, y;

    /**************************************************************************//**
    * @author Caitlin Taggart
    *
    * @par Description:
    * A constructor for a point
    *
    * @param dx - the x coordinate of the point. 
    * @param dy - the y coordinate of the point.
    *****************************************************************************/
    Point::Point(double dx, double dy)
    {
        x = dx; 
        y = dy; 
    }

    /**************************************************************************//**
    * @author Caitlin Taggart
    *
    * @par Description:
    * The default constructor for a point. Sets the point to the origin. 
    *****************************************************************************/
    Point::Point()
    {
        Point(0, 0); 
    }
};

/*!
* @brief a transformation matrix described by 
* |a b c|
* |d e f|
* |0 0 1|
* with a color as well. 
*/
struct TransformMatrix
{
	double a, b, c, d, e, f;
    double red, green, blue; 
};

/*!
* @brief A point with a color 
*/
struct ColorPoint
{
    double x, y, r, g, b; 

    /**************************************************************************//**
    * @author Caitlin Taggart
    *
    * @par Description:
    * The constructor for a point and the color of a point. 
    * 
    * @param xpnt - the x coordinate for the point
    * @param ypnt - the y coordinate for the point 
    * @param rcol - the red color for the point 
    * @param gcol - the green color for the point 
    * @param bcol - the blue color for the point 
    *****************************************************************************/
    ColorPoint::ColorPoint(double xpnt, double ypnt, double rcol, double gcol, double bcol)
    {
        x = xpnt;
        y = ypnt; 
        r = rcol;
        g = gcol; 
        b = bcol; 
    }

    /**************************************************************************//**
    * @author Caitlin Taggart
    *
    * @par Description:
    * A default constructor for the point. Sets the point to the origin with the 
    * color black.
    *****************************************************************************/
    ColorPoint::ColorPoint()
    {
        ColorPoint(0, 0, 0, 0, 0); 
    }
};

#endif