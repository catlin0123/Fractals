/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the GenWindow class. 
****************************************************************************/
//includes 
#include "GenWindow.h"
#include <stdlib.h>
#include <time.h>

//Static member definitions
/*!
* @brief the window id to draw to
*/
int GenWindow::_windowID = 0;

/*!
* @brief the newest point to be generated using ISF
*/
ColorPoint GenWindow::idle = ColorPoint(); 

/*!
* @brief tells whether to generate points or not
*/
bool GenWindow::generate = false; 

/*!
* @brief the color of the object points
*/
double GenWindow::color[3] = { 0.0, 0.0, 0.0 }; 

/*!
* @brief the list of transforms to perform
*/
vector<TransformMatrix> GenWindow::Transforms = vector<TransformMatrix>(); 

/*!
* @brief the points that make up the object drawn
*/
vector<Point> GenWindow::points = vector<Point>(); 

/*!
* @brief a list of generated points
*/
vector<ColorPoint> GenWindow::genPoints = vector<ColorPoint>(); 

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The init function which initializes the window used for the generated fractal.
*
* @param[in] x - the x position to place the window
* @param[in] y - the y position to place the window
* @param[in] width - the width of the window
* @param[in] height - the height of the window
*
*****************************************************************************/
void GenWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	_windowID = glutCreateWindow("Fractal");
    srand(time(NULL));
    generate = false;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The Display function which is the callback for displaying the generated fractal
* window. 
*****************************************************************************/
void GenWindow::Display()
{
    //set the appropriate window and cleat the screen
	glutSetWindow(_windowID);
	glClear(GL_COLOR_BUFFER_BIT);

    //draw the object
    glBegin(GL_LINE_STRIP);
        glColor3dv(color);
        for (unsigned int i = 0; i < points.size(); i++)
        {
            glVertex2d(points[i].x, points[i].y);
        }
     glEnd(); 

     //draw the generated points 
     glBegin(GL_POINTS);
         for (unsigned int i = 0; i < genPoints.size(); i++)
         {
             ColorPoint pnt = genPoints[i]; 
             glColor3d(pnt.r, pnt.g, pnt.b);
             glVertex2d(pnt.x, pnt.y);
         }
     glEnd(); 

    //swap buffers 
	glutSwapBuffers();
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The reshape callback for the generated fractal window. 
* 
* @param[in] width - the new width of the window
* @param[in] height - the new height of the window. 
*****************************************************************************/
void GenWindow::Reshape(int width, int height)
{
    //set the window 
	glutSetWindow(_windowID);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

    //keep the aspect ratio at one to one 
	if (float(width) / height > 1)
		glViewport((width - height) / 2, 0, height, height);
	else
		glViewport(0, (height - width) / 2, width, width);
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The constructor for the GenWindow class. It is empty and private because 
* we didn't want this class to be instaniated and instead wanted it to be a 
* "static" class. 
*****************************************************************************/
GenWindow::GenWindow()
{
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The destructor for the GenWindow class. It is empty and private for the same 
* reason the constructor is empty and private. 
*****************************************************************************/
GenWindow::~GenWindow()
{
}


/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* This point takes a point and a transform matrix and gives the point that is 
* generated by multiplying them together. 
*
* @param p - the point that will be transforms
* @param m - the transform matrix to use. 
* 
* @returns the point that has been transformed 
*****************************************************************************/
ColorPoint GenWindow::TransformPoint(ColorPoint p, TransformMatrix m)
{
    ColorPoint v; //the transformed point

    //transform the point
    v.x = m.a * p.x + m.b * p.y + m.c; 
    v.y = m.d * p.x + m.e * p.y + m.f; 
    return v; 
}

/**************************************************************************//**
* @author Dr. John Weiss, edited by Caitlin Taggart
*
* @par Description:
* This solves the system of equations that is needed to get a list of
* transforms. There are 3 input points, and then a list of transform points 
* which each consists of three points.
* 
* @param[in] transforms - the list of points needed to find the transforms 
*   with the input points in the 0 position and the transform points there 
*   there forward in the list. 
*****************************************************************************/
void GenWindow::SolveEquations(vector<vector<double> > transforms)
{
    double x1 = transforms[0][0]; double y1 = transforms[0][1];
    double x2 = transforms[0][2]; double y2 = transforms[0][3];
    double x3 = transforms[0][4]; double y3 = transforms[0][5];

    // for each affine transform
    for (unsigned int i = 1; i < transforms.size(); i++)
    {
        // 3 transformed points
        double r1 = transforms[i][0]; double s1 = transforms[i][1];
        double r2 = transforms[i][2]; double s2 = transforms[i][3];
        double r3 = transforms[i][4]; double s3 = transforms[i][5];

        // solve for the affine coefficients
        TransformMatrix m;
        double denom = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2); 
        m.a = r1 * (y2 - y3) + r2 * (y3 - y1) + r3 * (y1 - y2); 
        m.a = m.a / denom; 
        m.b = r1 * (x2 - x3) + r2 * (x3 - x1) + r3 * (x1 - x2); 
        m.b = m.b /  - denom; 
        m.c = r1 * (x2 * y3 - y2 * x3) + r2 * (x3 * y1 - y3 * x1) + r3 *(x1 * y2 - x2 * y1);
        m.c = m.c / denom; 

        m.d = s1 * (y2 - y3) + s2 * (y3 - y1) + s3 * (y1 - y2);
        m.d = m.d / denom;
        m.e = s1 * (x2 - x3) + s2 * (x3 - x1) + s3 * (x1 - x2);
        m.e = m.e / - denom;
        m.f = s1 * (x2 * y3 - y2 * x3) + s2 * (x3 * y1 - y3 * x1) + s3 *(x1 * y2 - x2 * y1);
        m.f = m.f / denom;

        //add the color to the transfrom
        m.red = transforms[i][6]; 
        m.green = transforms[i][7];
        m.blue = transforms[i][8]; 

        //add the transform to the list 
        Transforms.push_back(m); 
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* This is the idle call back function. This generates the points that create
* the fractal and then calls redisplay. Does this ten points at a time. Once
* this function is called and worked on for more than 100000 points it stops. 
*****************************************************************************/
void GenWindow::Idle()
{
    static int j = 0; 
    if (generate && j < 100000)
    {
        for (int i = 0; i < 10; i++)
        {
            //find a random transform
            int random = rand() % Transforms.size();

            //transform the last point 
            idle = TransformPoint(idle, Transforms[random]);

            //add a color based on the transform
            idle.r = Transforms[random].red;
            idle.g = Transforms[random].green;
            idle.b = Transforms[random].blue;
            
            //add it to the generated points list 
            genPoints.push_back(idle);
            j++; 
        }
        //ask glut to redisplay
        glutSetWindow(_windowID);
        glutPostRedisplay(); 
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Generates the fractal by solving the equations and goes through the first 
* couple transformed points. 
*****************************************************************************/
void GenWindow::GenerateFractal(vector<vector<double> > transforms, vector<Point> p, double c[])
{
    //get the transfroms 
    SolveEquations(transforms); 

    //copy the data needed
    points = p; 
    for (int i = 0; i < 3; i++)
    {
        color[i] = c[i];
    }

    //initialize the transforms
    idle.x = 0; 
    idle.y = 0; 

    //generate the first few tranformed points 
    for (int i = 0; i < 16; i++)
    {
        int random = rand() % Transforms.size();
        idle = TransformPoint(idle, Transforms[random]);
    }
    //let the idle function know it can generate 
    generate = true; 

    //tell glut that it should redisplay points
    glutSetWindow(_windowID);
    glutPostRedisplay(); 
}
