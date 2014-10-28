/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the UIWindow class.
****************************************************************************/
//Includes
#include "UIWindow.h"

//Macro definitions
#define mCircleVertices(x, y, r, segs) for(int _i = 0; _i < (segs); _i++){ glVertex2d((x) + (r) * cos(2 * M_PI * _i / (segs)), (y) + (r) * sin(2 * M_PI * _i / (segs))); }

//Static member definitions
/*!
* @brief the table used to generate the fractal
*/
vector<vector<double> > UIWindow::CoordTable;

/*!
* @brief the shape drawn in the UIWindow
*/
vector<Point> UIWindow::DrawnShape;

/*!
* @brief pointer the the Generate function
*/
UIWindow::GEN_FUNC_PTR UIWindow::_generate = NULL;

/*!
* @brief the window id to draw to
*/
int UIWindow::_windowID = 0;

/*!
* @brief the id of the menu used in the UIWindow
*/
int UIWindow::_menuID = 0;

/*!
* @brief the height of the window
*/
int UIWindow::Height = 0;

/*!
* @brief the width of the window
*/
int UIWindow::Width = 0;

/*!
* @brief the state of the UIWindow's menu
*/
bool UIWindow::_menuState = false;

/*!
* @brief whether or not the "Generate fractal" option is available in the menu
*/
bool UIWindow::_generateEnabled = false;

/*!
* @brief the reference points for the fractal
*/
UIWindow::PointSet UIWindow::_referencePoints;

/*!
* @brief the transform points for the fractal
*/
vector<UIWindow::PointSet> UIWindow::_transformPoints;

/*!
* @brief current state of the window
*/
UIWindow::State UIWindow::_state = UIWindow::NONE;

/*!
* @brief the color of the drawn shape
*/
double UIWindow::ShapeColor[3] = { 1.0, 1.0, 1.0 };

/*!
* @brief defined colors used for drawing and transform points
*/
double UIWindow::_colors[7][3] = {
		0.0, 0.0, 1.0, //Blue
		0.0, 1.0, 0.0, //Green
		0.0, 1.0, 1.0, //Cyan
		1.0, 0.0, 0.0, //Red
		1.0, 0.0, 1.0, //Purple
		1.0, 1.0, 0.0, //Yellow
		1.0, 1.0, 1.0  //White
};

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The init function which initializes the window used for User input.
*
* @param[in] x - the x position to place the window
* @param[in] y - the y position to place the window
* @param[in] width - the width of the window
* @param[in] height - the height of the window
*
*****************************************************************************/
void UIWindow::Init(int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x , y);
	_windowID = glutCreateWindow("Draw");
 
	_menuID = CreateMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMenuStateFunc(MenuState);
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calls the Generate function.
*
*****************************************************************************/
void UIWindow::GenerateFractal()
{
	_generate();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Stores the function pointer to the Generate function.
*
* @param[in] generate - the pointer the the Generate function
*
*****************************************************************************/
void UIWindow::GenerateFunction(void(*generate)(void))
{
	_generate = generate;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The callback to display the window
*
*****************************************************************************/
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
		str << "Add (" << 2 - _referencePoints.Index << ") Reference Points";
		message = str.str();
		break;
	}
	case UIWindow::ADDING_TRANSFORM:
	{
		stringstream str;
		str << "Add (" << 2 - _transformPoints[_transformPoints.size() - 1].Index << ") Transform Points";
		message = str.str();
		break;
	}
	case UIWindow::NONE:
	{
		message = "Right click to select mode";
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

	glutSwapBuffers();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The reshape callback for the window
*
* @param[in] height - the height of the window
* @param[in] width - the width of the window
*
*****************************************************************************/
void UIWindow::Reshape(int width, int height)
{
	glutSetWindow(_windowID);

	Height = height;
	Width = width;

	//Set the coordinate system to a 100 X 100 grid
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	//Preserve the aspect ratio of the window as 1:1
	if (float(width) / height > 1)
		glViewport((width - height) / 2, 0, height, height);
	else
		glViewport(0, (height - width) / 2, width, width);
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The mouse callback for the window.
*
* @param[in] button - mouse button pressed (left or right)
* @param[in] state - the state of the button (up or down)
* @param[in] x - the x position of the mouse state change
* @param[in] y - the y position of the mouse state change
*
*****************************************************************************/
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
			//Increment which point is being modified
			if (_referencePoints.Index < 2)
			{
				_referencePoints.Index++;
			}

			//Reset the state to none on the completion of the PointSet
			if (_referencePoints.Index == 2)
			{
				_state = NONE;
			}

			//Store the next point in the PointSet
			_referencePoints.Points[_referencePoints.Index].x = (100.0 / Width * x);
			_referencePoints.Points[_referencePoints.Index].y = 100 - (100.0 / Height * y);
			break;
		}
		case UIWindow::ADDING_TRANSFORM:
		{
			//Increment which point is being modified
			if (_transformPoints[_transformPoints.size() - 1].Index < 2)
			{
				_transformPoints[_transformPoints.size() - 1].Index++;
			}

			//Reset the state to none on the completion of the PointSet
			if (_transformPoints[_transformPoints.size() - 1].Index == 2)
			{
				_state = NONE;
			}

			//Store the next point in the PointSet
			_transformPoints[_transformPoints.size() - 1].Points[_transformPoints[_transformPoints.size() - 1].Index].x = (100.0 / Width * x);
			_transformPoints[_transformPoints.size() - 1].Points[_transformPoints[_transformPoints.size() - 1].Index].y = 100 - (100.0 / Height * y);
			break;
		}
		}

		//If the user has input enough information to create a fractal and generate
		//option hasn't already been added, add the generate option to the menu
		if (_generateEnabled == false &&
			_transformPoints.size() >= 1 &&
			_transformPoints[_transformPoints.size() - 1].Index == 2 &&
			_referencePoints.Index == 2)
		{
			glutAddMenuEntry("Generate Fractal", 40);
			_generateEnabled = true;
		}
	}
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The motion callback for the window. Used for drawing on the screen.
*
* @param[in] x - the x position of the mouse
* @param[in] y - the y position of the mouse
*
*****************************************************************************/
void UIWindow::Motion(int x, int y)
{
	if (_menuState == false)
	{
		switch (_state)
		{
		case UIWindow::DRAWING:
		{
			if (x >= 0 && x <= Width && y >= 0 && y <= Height)
			{
				DrawnShape.push_back(Point((100.0 / Width * x), 100 - (100.0 / Height * y)));
			}
			break;
		}
		}
	}

	glutSetWindow(_windowID);
	glutPostRedisplay();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The callback for a change in menu state
*
* @param[in] state - the state of the menu (in use, or not in use)
*
*****************************************************************************/
void UIWindow::MenuState(int state)
{
	_menuState = (state == GLUT_MENU_IN_USE);
	if (_menuState == true)
	{
		_state = NONE;
	}
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The menu callback for the window. The menu is set up to have a main menu and
* various submenus for choosing color.
*
* @param[in] value - the value returned from the selected menu. In the tens
*					 place is the menu index, the color selection is in the
*					 ones position.
*
*****************************************************************************/
void UIWindow::Menu(int value)
{
	int menuIndex = value / 10;
	int submenuIndex = value % 10;

	switch (menuIndex)
	{
	case 1: //Draw color selected
		//Set to drawing mode
		_state = DRAWING;

		//Set the color
		for (int i = 0; i < 3; i++)
			ShapeColor[i] = _colors[submenuIndex][i];

		break;
	case 2: //Add Reference selected
		//Set to reference adding mode
		_state = ADDING_REFERENCE;

		break;
	case 3: //Add Transform selected
		//Create a new PointSet if there are no transforms, or the current transform is full
		if (_transformPoints.size() == 0 || _transformPoints[_transformPoints.size() - 1].Index == 2)
		{
			_transformPoints.push_back(PointSet());
		}
		
		//Set color of the current transform PointSet
		for (int i = 0; i < 3; i++)
			_transformPoints[_transformPoints.size() - 1].Color[i] = _colors[submenuIndex][i];

		//Set to transform adding mode
		_state = ADDING_TRANSFORM;

		break;
	case 4://Generate fractal selected
		//Create Coordinates table
		CoordTable.clear();

		//Create original/reference point and color
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

		//Create transform points
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
		GenerateFractal();
		break;
	}

	glutSetWindow(_windowID);
	glutPostRedisplay();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Creates a color submenu
*
* @param[in] menuIndex - the index of the menu (placed in tens place)
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Creates the initial menu without the "Generate fractals" option
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Private constructor to help emulate a "static" class
*
*****************************************************************************/
UIWindow::UIWindow()
{
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Private deconstructor to help emulate a "static" class
*
*****************************************************************************/
UIWindow::~UIWindow()
{
}