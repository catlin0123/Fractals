#ifndef __GENWINDOW_H__
#define __GENWINDOW_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>

#include "Structs.h"

using namespace std;

class GenWindow
{
public:
	//Members
	static vector<TransformMatrix> Transforms;

	//Functions
	static void Init(int x, int y, int width, int height);
	static void Display();
	static void Reshape(int width, int height);
	static void Mouse(int button, int state, int x, int y);

private:
	GenWindow();
	~GenWindow();

	//Members
	static int _windowID;

	//Functions
};

#endif

