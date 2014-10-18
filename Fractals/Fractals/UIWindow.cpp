#include "UIWindow.h"

//Static member definitions
UIWindow::GEN_FUNC_PTR UIWindow::_generate = NULL;
int UIWindow::_windowID = 0;

void UIWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	_windowID = glutCreateWindow("Draw");
}

void UIWindow::GenerateFractal()
{
	_generate();
}

void UIWindow::GenerateFunction(void(*generate)(void))
{
	_generate = generate;
}

void UIWindow::Display()
{
	glutSetWindow(_windowID);

	glClear(GL_COLOR_BUFFER_BIT);

	//glFlush();
	glutSwapBuffers();
}

void UIWindow::Reshape(int width, int height)
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

void UIWindow::Mouse(int button, int state, int x, int y)
{

}

void UIWindow::Motion(int x, int y)
{

}

UIWindow::UIWindow()
{
}

UIWindow::~UIWindow()
{
}