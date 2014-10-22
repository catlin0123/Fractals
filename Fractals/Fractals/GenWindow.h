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
	//Functions
	static void Init(int x, int y, int width, int height);
    static void Idle(); 
	static void Display();
	static void Reshape(int width, int height);
	static void Mouse(int button, int state, int x, int y);
    static void GenerateFractal(); 

private:
	GenWindow();
	~GenWindow();

	//Members
	static int _windowID;
    static Point idle;
    static bool generate;
    static vector<TransformMatrix> Transforms;
    static vector<Point> points; 
    static void SolveEquations(); 
    static Point TransformPoint(Point p, TransformMatrix m);

	//Functions
};

#endif

