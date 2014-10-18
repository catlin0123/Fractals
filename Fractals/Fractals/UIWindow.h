#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>

#include "Structs.h"

using namespace std;


class UIWindow
{
	typedef void(*GEN_FUNC_PTR)(void);

public:
	//Members
	static vector<vector<double> > CoordTable;
	static vector<Point> DrawnShape;

	//Functions
	static void Init(int x, int y, int width, int height);
	static void GenerateFunction(void(*generate)(void));

	static void Display();
	static void Reshape(int width, int height);
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);

private:
	UIWindow();
	~UIWindow();

	//Members
	static int _windowID;
	static GEN_FUNC_PTR _generate;

	//Functions
	static void GenerateFractal();
};

#endif

