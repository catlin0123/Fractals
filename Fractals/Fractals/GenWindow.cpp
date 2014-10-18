#include "GenWindow.h"

//Static member definitions
int GenWindow::_windowID = 0;

void GenWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	_windowID = glutCreateWindow("Fractal");
}

void GenWindow::Display()
{
	glutSetWindow(_windowID);

	glClear(GL_COLOR_BUFFER_BIT);

	//glFlush();
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
