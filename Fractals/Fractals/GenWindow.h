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
    static void GenerateFractal(vector<vector<double> > transforms, vector<Point>, double color[]);

private:
	GenWindow();
	~GenWindow();

	//Members
	static int _windowID;
    static ColorPoint idle;
    static bool generate;
    static double color[3];
    static vector<TransformMatrix> Transforms;
    static vector<Point> points; 
    static vector<ColorPoint> genPoints; 


    static void SolveEquations(vector<vector<double> > transforms);
    static ColorPoint TransformPoint(ColorPoint p, TransformMatrix m);

	//Functions
};

#endif

