/*************************************************************************//**
* @file
*
* @brief Contains the declaration of the UIWindow class.
****************************************************************************/
#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

//Includes
#include <GL\freeglut.h>
#include <GL\GLU.h>
#include <vector>
#include <sstream>
#include <cmath>

#include "Structs.h"

//Namespace
using namespace std;

//Definitions
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define C_SEGS 20


class UIWindow
{
public:
	//Definition of the function pointer type for the Generate function
	typedef void(*GEN_FUNC_PTR)(void);

	//Struct to make storing sets of points for reference and transform points
	struct PointSet
	{
		Point Points[3];
		double Color[3];
		int Index;

		PointSet() { Index = -1; }
	};

	//The different states that the UI Window can be in
	enum State
	{
		NONE,
		DRAWING,
		ADDING_REFERENCE,
		ADDING_TRANSFORM
	};

	//Members
	/*!
	* @brief the table used to generate the fractal
	*/
	static vector<vector<double> > CoordTable;

	/*!
	* @brief the shape drawn in the UIWindow
	*/
	static vector<Point> DrawnShape;

	/*!
	* @brief the color of the drawn shape
	*/
	static double ShapeColor[3];


	/*!
	* @brief the height of the window
	*/
	static int Height;

	/*!
	* @brief the width of the window
	*/
	static int Width;

	//Functions
	static void Init(int x, int y, int width, int height);
	static void GenerateFunction(void(*generate)(void));

	static void Display();
	static void Reshape(int width, int height);
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);
	static void MenuState(int state);

private:
	//Constructor and deconstructor are private to emulate a "static" class
	UIWindow();
	~UIWindow();

	//Members
	/*!
	* @brief the window id to draw to
	*/
	static int _windowID;

	/*!
	* @brief the id of the menu used in the UIWindow
	*/
	static int _menuID;


	/*!
	* @brief the state of the UIWindow's menu
	*/
	static bool _menuState;

	/*!
	* @brief whether or not the "Generate fractal" option is available in the menu
	*/
	static bool _generateEnabled;


	/*!
	* @brief pointer the the Generate function
	*/
	static GEN_FUNC_PTR _generate;

	/*!
	* @brief defined colors used for drawing and transform points
	*/
	static double _colors[7][3];


	/*!
	* @brief the reference points for the fractal
	*/
	static PointSet _referencePoints;

	/*!
	* @brief the transform points for the fractal
	*/
	static vector<PointSet> _transformPoints;


	/*!
	* @brief the color of the drawn shape
	*/
	static State _state;

	//Functions
	static void GenerateFractal();
	static int CreateColorsMenu(int menuIndex);
	static int CreateMenu();
	static void Menu(int value);
};

#endif