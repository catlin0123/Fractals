#pragma once
#include "Structs.h"

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

