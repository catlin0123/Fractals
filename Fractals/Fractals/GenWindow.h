/*************************************************************************//**
* @file
*
* @brief The header file for the GenWindow class which generates a fractal
* draws that fractal on the screen. 
****************************************************************************/
#ifndef __GENWINDOW_H__
#define __GENWINDOW_H__

//includes
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>
#include "Structs.h"
using namespace std;


class GenWindow
{
public:
	//Functions
	static void Init(int x, int y, int width, int height);
    static void Idle(); 
	static void Display();
	static void Reshape(int width, int height);
    static void GenerateFractal(vector<vector<double> > transforms, vector<Point>, double color[]);

private:
	//Members
    /*!
    * @brief the window id to draw to
    */
	static int _windowID;

    /*!
    * @brief the newest point to be generated using ISF
    */
    static ColorPoint idle;

    /*!
    * @brief tells whether to generate points or not
    */
    static bool generate;

    /*!
    * @brief the color of the object points
    */
    static double color[3];

    /*!
    * @brief the list of transforms to perform
    */
    static vector<TransformMatrix> Transforms;

    /*!
    * @brief the points that make up the object drawn
    */
    static vector<Point> points; 

    /*!
    * @brief a list of generated points 
    */
    static vector<ColorPoint> genPoints; 

    //Private Functions
    static void SolveEquations(vector<vector<double> > transforms);
    static ColorPoint TransformPoint(ColorPoint p, TransformMatrix m);
    GenWindow();
    ~GenWindow();
};
#endif

