#ifndef __GENWINDOW_H__
#define __GENWINDOW_H__

#include <vector>

#include "Structs.h"

using namespace std;

class GenWindow
{
public:
	GenWindow();
	~GenWindow();

	//Members
	vector<TransformMatrix> Transforms;

	//Functions
	void Init();
};

#endif

