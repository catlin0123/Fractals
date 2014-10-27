#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>
#include <sstream>
#include <cmath>

#include "Structs.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define C_SEGS 20


class UIWindow
{
public:
	typedef void(*GEN_FUNC_PTR)(void);

	struct PointSet
	{
		Point Points[3];
		double Color[3];
		int Index;

		PointSet() { Index = -1; }
	};

	enum State
	{
		NONE,
		DRAWING,
		ADDING_REFERENCE,
		ADDING_TRANSFORM
	};

	//Members
	static vector<vector<double> > CoordTable;
	static vector<Point> DrawnShape;
	static double ShapeColor[3];

	static int Height;
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
	UIWindow();
	~UIWindow();

	//Members
	static int _windowID;
	static int _menuID;

	static bool _menuState;
	static bool _generateEnabled;

	static GEN_FUNC_PTR _generate;
	static double _colors[7][3];

	static PointSet _referencePoints;
	static vector<PointSet> _transformPoints;

	static State _state;

	//Functions
	static void GenerateFractal();
	static int CreateColorsMenu(int menuIndex);
	static int CreateMenu();

	static void Menu(int value);
};

#endif