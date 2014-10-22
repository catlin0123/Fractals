#include "GenWindow.h"
#include <stdlib.h>
#include <time.h>

//Static member definitions
int GenWindow::_windowID = 0;
Point GenWindow::idle = Point(0, 0); 
bool GenWindow::generate = false; 
vector<TransformMatrix> GenWindow::Transforms = vector<TransformMatrix>(); 
vector<Point> GenWindow::points = vector<Point>(); 

void GenWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	_windowID = glutCreateWindow("Fractal");
    srand(1943203);
    generate = false; 
    _windowID = 0; 
}

void GenWindow::Display()
{
	glutSetWindow(_windowID);

	glClear(GL_COLOR_BUFFER_BIT);

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
    //set window? 
    for (auto p : points)
    {
        //set the color to the color of the point
        glColor3d(1, 1, 1);
        glBegin(GL_POINT); 
            glVertex2d(p.x, p.y); 
        glEnd();
    }
}

GenWindow::~GenWindow()
{
}

Point GenWindow::TransformPoint(Point p, TransformMatrix m)
{
    Point v; 
    v.x = m.a * p.x + m.b * p.y + m.c; 
    v.y = m.d * p.x + m.e * p.y + m.f; 
    return v; 
}

void GenWindow::SolveEquations()
{
    double x1 = 0;// = CoordsTable[0][0];
    double y1 = 0;// = CoordsTable[0][1];
    double x2 = 0;// = CoordsTable[0][2];
    double y2 = 0;// = CoordsTable[0][3];
    double x3 = 0;// = CoordsTable[0][4];
    double y3 = 0;// = CoordsTable[0][5];
    // for each affine transform
    for (int i = 1; i < 0/*CoordsTable.size()*/; i++)
    {
        // 3 transformed points
        double r1 = 0;// = CoordsTable[i + 1][0];
        double s1 = 0;// = CoordsTable[i + 1][1];
        double r2 = 0;// = CoordsTable[i + 1][2];
        double s2 = 0;// = CoordsTable[i + 1][3];
        double r3 = 0;// = CoordsTable[i + 1][4];
        double s3 = 0;// = CoordsTable[i + 1][5];
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
        //m.color = CoordsTable[i + 1][6];

        Transforms.push_back(m); 
    }

}

void GenWindow::Idle()
{
    if (generate)
    {
        int random = rand() % Transforms.size();
        idle = TransformPoint(idle, Transforms[random]);
        points.push_back(idle); 
        //if needed add the color to another vector
    }
}

void GenWindow::GenerateFractal()
{
    SolveEquations(); 
    idle.x = 0; 
    idle.y = 0; 

    //set the window
    //plot the original graph in the original color; 

    for (int i = 0; i < 16; i++)
    {
        int random = rand() % Transforms.size();
        idle = TransformPoint(idle, Transforms[random]);
    }

    generate = true; 
}
