#include "GenWindow.h"
#include <stdlib.h>
#include <time.h>

//Static member definitions
int GenWindow::_windowID = 0;
ColorPoint GenWindow::idle = ColorPoint(); 
bool GenWindow::generate = false; 
double GenWindow::color[3] = { 0.0, 0.0, 0.0 }; 
vector<TransformMatrix> GenWindow::Transforms = vector<TransformMatrix>(); 
vector<Point> GenWindow::points = vector<Point>(); 
vector<ColorPoint> GenWindow::genPoints = vector<ColorPoint>(); 

void GenWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	_windowID = glutCreateWindow("Fractal");
    srand(1943203);
    generate = false;
}

void GenWindow::Display()
{
	glutSetWindow(_windowID);
	glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
        glColor3dv(color);
        for (unsigned int i = 0; i < points.size(); i++)
        {
            glVertex2d(points[i].x, points[i].y);
        }
     glEnd(); 

     glBegin(GL_POINTS);
         for (unsigned int i = 0; i < genPoints.size(); i++)
         {
             ColorPoint pnt = genPoints[i]; 
             glColor3d(pnt.r, pnt.g, pnt.b);
             glVertex2d(pnt.x, pnt.y);
         }
     glEnd(); 

	glutSwapBuffers();
}

void GenWindow::Reshape(int width, int height)
{
	glutSetWindow(_windowID);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	if (float(width) / height > 2)
		glViewport((width - 2 * height) / 2, 0, 2 * height, height);
	else
		glViewport(0, (height - width / 2) / 2, width, width / 2);
}

void GenWindow::Mouse(int button, int state, int x, int y)
{

}

GenWindow::GenWindow()
{
}

GenWindow::~GenWindow()
{
}

ColorPoint GenWindow::TransformPoint(ColorPoint p, TransformMatrix m)
{
    ColorPoint v; 
    v.x = m.a * p.x + m.b * p.y + m.c; 
    v.y = m.d * p.x + m.e * p.y + m.f; 
    return v; 
}

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
        m.b = m.b / denom; 
        m.c = r1 * (x2 * y3 - y2 * x3) + r2 * (x3 * y1 - y3 * x1) + r3 *(x1 * y2 - x2 * y1);
        m.c = m.c / denom; 

        m.d = s1 * (y2 - y3) + s2 * (y3 - y1) + s3 * (y1 - y2);
        m.d = m.d / denom;
        m.e = s1 * (x2 - x3) + s2 * (x3 - x1) + s3 * (x1 - x2);
        m.e = m.e / denom;
        m.f = s1 * (x2 * y3 - y2 * x3) + s2 * (x3 * y1 - y3 * x1) + s3 *(x1 * y2 - x2 * y1);
        m.f = m.f / denom;

        m.red = transforms[i][6]; 
        m.green = transforms[i][7];
        m.blue = transforms[i][8]; 

        Transforms.push_back(m); 
    }
}

void GenWindow::Idle()
{
    if (generate)
    {
        int random = rand() % Transforms.size();
        idle = TransformPoint(idle, Transforms[random]);
        idle.r = Transforms[random].red;
        idle.g = Transforms[random].green; 
        idle.b = Transforms[random].blue; 
        genPoints.push_back(idle); 
    }
}

void GenWindow::GenerateFractal(vector<vector<double> > transforms, vector<Point>, double color[])
{
    SolveEquations(transforms); 
    idle.x = 0; 
    idle.y = 0; 



    for (int i = 0; i < 16; i++)
    {
        int random = rand() % Transforms.size();
        idle = TransformPoint(idle, Transforms[random]);
    }
    idle.r = color[0]; 
    idle.g = color[1]; 
    idle.b = color[2]; 

    generate = true; 
}
