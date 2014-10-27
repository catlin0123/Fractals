#include "UIWindow.h"

#define mCircleVertices(x, y, r, segs) for(int _i = 0; _i < (segs); _i++){ glVertex2d((x) + (r) * cos(2 * M_PI * _i / (segs)), (y) + (r) * sin(2 * M_PI * _i / (segs))); }

//Static member definitions
vector<vector<double> > UIWindow::CoordTable;
vector<Point> UIWindow::DrawnShape;
UIWindow::GEN_FUNC_PTR UIWindow::_generate = NULL;
int UIWindow::_windowID = 0;
int UIWindow::_menuID = 0;
int UIWindow::Height = 0;
int UIWindow::Width = 0;
bool UIWindow::_menuState = false;
bool UIWindow::_generateEnabled = false;
UIWindow::PointSet UIWindow::_referencePoints;
vector<UIWindow::PointSet> UIWindow::_transformPoints;
UIWindow::State UIWindow::_state = UIWindow::DRAWING;

double UIWindow::ShapeColor[3] = { 1.0, 1.0, 1.0 };
double UIWindow::_colors[7][3] = {
		0.0, 0.0, 1.0, //Blue
		0.0, 1.0, 0.0, //Green
		0.0, 1.0, 1.0, //Cyan
		1.0, 0.0, 0.0, //Red
		1.0, 0.0, 1.0, //Purple
		1.0, 1.0, 0.0, //Yellow
		1.0, 1.0, 1.0  //White
};

void UIWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x , y);
	_windowID = glutCreateWindow("Draw");
 
	_menuID = CreateMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMenuStateFunc(MenuState);
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

	//Create background grid
	glColor3d(.3, .3, .3);
	glBegin(GL_LINES);
	for (int i = 1; i < 10; i++)
	{
		glVertex2i(i * 10, Height);
		glVertex2i(i * 10, 0);

		glVertex2i(0, i * 10);
		glVertex2i(Width, i * 10);
	}
	glEnd();

	//Draw current shape
	glColor3dv(ShapeColor);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < DrawnShape.size(); i++)
	{
		glVertex2d(DrawnShape[i].x, DrawnShape[i].y);
	}
	glEnd();

	//Draw Reference points
	for (int i = 0; i <= _referencePoints.Index; i++)
	{
		glBegin(GL_LINE_LOOP);
			mCircleVertices(_referencePoints.Points[i].x, _referencePoints.Points[i].y, 1, C_SEGS);
		glEnd();
	}

	//Draw Transform points
	for (int i = 0; i < _transformPoints.size(); i++)
	{
		glColor3dv(_transformPoints[i].Color);
		for (int j = 0; j <= _transformPoints[i].Index; j++)
		{
			glBegin(GL_LINE_LOOP);
				mCircleVertices(_transformPoints[i].Points[j].x, _transformPoints[i].Points[j].y, 1, C_SEGS);
			glEnd();
		}
	}

	//Draw instruction message
	string message = "How did you get in this state?";
	switch (_state)
	{
	case UIWindow::DRAWING:
	{
		message = "Drawing...";
		break;
	}
	case UIWindow::ADDING_REFERENCE:
	{
		stringstream str;
		str << "Add (" << 2 - _referencePoints.Index << ") Reference Points.";
		message = str.str();
		break;
	}
	case UIWindow::ADDING_TRANSFORM:
	{
		stringstream str;
		str << "Add (" << 2 - _transformPoints[_transformPoints.size() - 1].Index << ") Transform Points.";
		message = str.str();
		break;
	}
	}

	int x_off, y_off;
	x_off = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*)message.c_str()) + 5;
	y_off = glutBitmapHeight(GLUT_BITMAP_TIMES_ROMAN_10) + 2;

	glColor3f(0.0, 0.0, 0.0);
	glRectf(100 - (100.0 / Width * (x_off + 5)), (100.0 / Height * (y_off + 5)), 100, 0);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(100 - (100.0/Width * x_off), 2);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*)message.c_str());

	//glFlush();
	glutSwapBuffers();
}

void UIWindow::Reshape(int width, int height)
{
	glutSetWindow(_windowID);

	Height = height;
	Width = width;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	if (float(width) / height > 1)
		glViewport((width - height) / 2, 0, height, height);
	else
		glViewport(0, (height - width) / 2, width, width);
}

void UIWindow::Mouse(int button, int state, int x, int y)
{
	if (_menuState == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		switch (_state)
		{
		case UIWindow::DRAWING:
		{
			break;
		}
		case UIWindow::ADDING_REFERENCE:
		{
			if (_referencePoints.Index < 2)
			{
				_referencePoints.Index++;
			}
			if (_referencePoints.Index == 2)
			{
				_state = DRAWING;
			}

			_referencePoints.Points[_referencePoints.Index].x = (100.0 / Width * x);
			_referencePoints.Points[_referencePoints.Index].y = 100 - (100.0 / Height * y);
			break;
		}
		case UIWindow::ADDING_TRANSFORM:
		{
			if (_transformPoints[_transformPoints.size() - 1].Index < 2)
			{
				_transformPoints[_transformPoints.size() - 1].Index++;
			}
			if (_transformPoints[_transformPoints.size() - 1].Index == 2)
			{
				_state = DRAWING;
			}

			_transformPoints[_transformPoints.size() - 1].Points[_transformPoints[_transformPoints.size() - 1].Index].x = (100.0 / Width * x);
			_transformPoints[_transformPoints.size() - 1].Points[_transformPoints[_transformPoints.size() - 1].Index].y = 100 - (100.0 / Height * y);
			break;
		}
		}

		if (_generateEnabled == false && _transformPoints.size() >= 1 && _transformPoints[_transformPoints.size() - 1].Index == 2 && _referencePoints.Index == 2 && DrawnShape.size() != 0)
		{
			glutAddMenuEntry("Generate Fractal", 40);
			_generateEnabled = true;
		}
	}
}

void UIWindow::Motion(int x, int y)
{
	if (_menuState == false)
	{
		switch (_state)
		{
		case UIWindow::DRAWING:
		{
			DrawnShape.push_back(Point((100.0 / Width * x), 100 - (100.0 / Height * y)));
			break;
		}
		case UIWindow::ADDING_REFERENCE:
		{
			break;
		}
		case UIWindow::ADDING_TRANSFORM:
		{
			break;
		}
		}
	}

	glutPostRedisplay();
}

void UIWindow::MenuState(int state)
{
	_menuState = (state == GLUT_MENU_IN_USE);
}

void UIWindow::Menu(int value)
{
	int menuIndex = value / 10;
	int submenuIndex = value % 10;

	switch (menuIndex)
	{
	//Clearing deprecated
	case 0:
		//Clear screen and data
		CoordTable.clear();
		DrawnShape.clear();
		_referencePoints = PointSet();
		_transformPoints.clear();
		_state = DRAWING;
		break;
	case 1:
		//Set to drawing mode, set color
		_state = DRAWING;

		for (int i = 0; i < 3; i++)
			ShapeColor[i] = _colors[submenuIndex][i];

		break;
	case 2:
		_state = ADDING_REFERENCE;

		break;
	case 3:
		if (_transformPoints.size() == 0 || _transformPoints[_transformPoints.size() - 1].Index == 2)
		{
			_transformPoints.push_back(PointSet());
		}
		
		//Set color
		for (int i = 0; i < 3; i++)
			_transformPoints[_transformPoints.size() - 1].Color[i] = _colors[submenuIndex][i];

		_state = ADDING_TRANSFORM;

		break;
	case 4:

		//Create Coordinates table
		CoordTable.clear();
		CoordTable.push_back(vector<double>());
		for (int i = 0; i < 3; i++)
		{
			CoordTable[0].push_back(_referencePoints.Points[i].x);
			CoordTable[0].push_back(_referencePoints.Points[i].y);
		}
		for (int i = 0; i < 3; i++)
		{
			CoordTable[0].push_back(ShapeColor[i]);
		}
		for (int i = 0; i < _transformPoints.size(); i++)
		{
			CoordTable.push_back(vector<double>());
			for (int j = 0; j < 3; j++)
			{
				CoordTable[i + 1].push_back(_transformPoints[i].Points[j].x);
				CoordTable[i + 1].push_back(_transformPoints[i].Points[j].y);
			}
			for (int j = 0; j < 3; j++)
			{
				CoordTable[i + 1].push_back(_transformPoints[i].Color[j]);
			}
		}

		//Generate the fractal
		_generate();
		break;
	}

	glutPostRedisplay();
}

int UIWindow::CreateColorsMenu(int menuIndex)
{
	int id = glutCreateMenu(Menu);
	glutAddMenuEntry("White", 10 * menuIndex + 6);
	glutAddMenuEntry("Blue", 10 * menuIndex);
	glutAddMenuEntry("Green", 10 * menuIndex + 1);
	glutAddMenuEntry("Cyan", 10 * menuIndex + 2);
	glutAddMenuEntry("Red", 10 * menuIndex + 3);
	glutAddMenuEntry("Purple", 10 * menuIndex + 4);
	glutAddMenuEntry("Yellow", 10 * menuIndex + 5);

	return id;
}

int UIWindow::CreateMenu()
{
	int drawMenu = CreateColorsMenu(1);
	int transPointsMenu = CreateColorsMenu(3);

	int mainMenu = glutCreateMenu(Menu);

	//glutAddMenuEntry("Clear", 0);

	glutAddSubMenu("Draw", drawMenu);
	
	glutAddMenuEntry("Add Reference Points", 20);

	glutAddSubMenu("Add Transform Points", transPointsMenu);

	return mainMenu;
}

UIWindow::UIWindow()
{
}

UIWindow::~UIWindow()
{
}