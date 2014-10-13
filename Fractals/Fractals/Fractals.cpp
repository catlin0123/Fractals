/*************************************************************************//**
* @file
*
* @mainpage Program 1 - Fractals
*
* @section course_section Course Information
*
* @author Paul Blasi, Caitlin Taggart
*
* @date <program date due>
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
c:\> make pong
@endverbatim
*
* @par Usage:
@verbatim
On Windows:
c:\> pong.exe

On Linux:
c:\> ./pong
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
       12:38  for Point and TransformMatrix. Declared Init functions for
			  GenWindow and UIWindow.
			  Files added:
               +  Fractals.cpp
			   +  Structs.h
			   +  GenWindow.h
			   +  GenWindow.cpp
			   +  UIWindow.h
			   +  UIWindow.cpp
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

//Windows
UIWindow DrawingWindow;
GenWindow FractalWindow;

//Global Data
int gScreenWidth = 400;
int gScreenHeight = 400;

int main()
{

}