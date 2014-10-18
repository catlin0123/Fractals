/*************************************************************************//**
* @file
*
* @mainpage Program 2 - Fractals
*
* @section course_section Course Information
*
* @author Paul Blasi, Caitlin Taggart
*
* @date 24 October, 2014
*
* @par Professor:
*         Dr. Weiss
*
* @par Course:
*         Graphics  -  9 AM
*
* @par Location:
*         McLaury - 313
*
* @section program_section Program Information
*
* @details This program is a fractal generator using an iterated function system.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
@verbatim
c:\> make fractals
@endverbatim
*
* @par Usage:
@verbatim
On Windows:
c:\> fractals.exe

On Linux:
c:\> ./fractals
@endverbatim
* After starting the application, the user should draw a rough sketch of the initial
* fractal shape on the left hand screen. When the user finishes, they should enter 3
* reference points by right clicking and selecting "Set Reference Points". Once 3
* reference points are set, they can set transform points by right clicking and
* selecting "Set Transform Points". You can set any number of sets of transform points.
* Once all of the reference and transform points are set, right click and select
* "Generate" to display the fractal on the right hand screen.
*
* At any time, you can right click and select "Clear" to clear both screens. The
* "Generate" option will only be selectable when 3 reference points and at least 1 set
* of 3 transform points have been set.
*
* @section todo_bugs_modification_section Todo, Bugs, and Modificationss
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Oct 13, 2014  Initial setup of GitHub and project structure. Defined structs
    12:38 AM  for Point and TransformMatrix. Declared Init functions for
			  GenWindow and UIWindow.
			  Files added:
               +  Fractals.cpp
			   +  Structs.h
			   +  GenWindow.h
			   +  GenWindow.cpp
			   +  UIWindow.h
			   +  UIWindow.cpp

Oct 17, 2014  Finalized setup of project. Classes are going to be "static"
    08:36 PM  (at least as static as C++ allows) to allow for the member
			  functions to act as callbacks with glut.
			  Files modified:
			   ~  Fractals.cpp
			   ~  GenWindow.cpp
			   ~  UIWindow.cpp
			   ~  GenWindow.h
			   ~  UIWindow.h
@endverbatim
*
*****************************************************************************/
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>
#include <string>

#include "Structs.h"
#include "GenWindow.h"
#include "UIWindow.h"

using namespace std;

//Callbacks
void Keyboard(unsigned char key, int x, int y);
void GenerateFractal();

//Constants
const unsigned char ESCAPE_KEY = 27;

//Global Data
int gScreenWidth = 400;
int gScreenHeight = 400;

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Main execution point of the app. Initializes the windows.
*
* @returns Execution outcome.
*
*****************************************************************************/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	
	//Initialize both windows and share the keyboard function between them
	UIWindow::Init(100, 100, gScreenWidth, gScreenHeight);
	UIWindow::GenerateFunction(GenerateFractal);
	glutDisplayFunc(UIWindow::Display);
	glutReshapeFunc(UIWindow::Reshape);
	glutMouseFunc(UIWindow::Mouse);
	glutMotionFunc(UIWindow::Motion);
	glutKeyboardFunc(Keyboard);

	GenWindow::Init(100 + gScreenWidth + 50, 100, gScreenWidth, gScreenHeight);
	glutDisplayFunc(GenWindow::Display);
	glutReshapeFunc(GenWindow::Reshape);
	glutMouseFunc(GenWindow::Mouse);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* if escape is pressed, exits the application.
*
* @param[in] key - the key that was pressed
* @param[in] x - the x position of the mouse when the key was pressed
* @param[in] y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void Keyboard(unsigned char key, int x, int y)
{
	if (key == ESCAPE_KEY)
	{
		glutLeaveMainLoop();
	}
}

void GenerateFractal()
{

}