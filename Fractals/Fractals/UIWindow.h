#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include <vector>

#include "Structs.h"

using namespace std;

class UIWindow
{
public:
	UIWindow();
	~UIWindow();

	//Members
	vector<vector<double> > CoordTable;
	vector<Point> DrawnShape;

	//Functions
	void Init();
};

#endif

