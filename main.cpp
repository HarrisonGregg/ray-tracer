#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
 
#include <vector>
#include <limits>
#include <float.h>
#include <map>

using namespace std;

#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "float4x4.h"
#include "LightSource.h"
#include "Camera.h" 
#include "Ray.h" 
#include "Hit.h" 
#include "perlin.h" 
#include "Material.h" 
#include "Intersectable.h" 
#include "Sphere.h" 
#include "Ellipsoid.h" 
#include "Egg.h" 
#include "Plane.h" 
#include "Cube.h" 
#include "Scene.h" 

// YOU DO NOT NEED TO CHANGE ANYTHING BELOW THIS LINE
////////////////////////////////////////////////////////////////////////////////////////////////////////

// global application data

// screen resolution
const int screenWidth = 600;
const int screenHeight = 600;

// image to be computed by ray tracing
float3 image[screenWidth*screenHeight];

//scene object
Scene scene;

// Computes every 64th scanline of the image calling scene.trace() for every pixel. Returns true if scanlines are left uncomputed.
bool computeImage()
{
	static unsigned int iPart = 0;

	if(iPart >= 64)
		return false;
    for(int j = iPart; j < screenHeight; j+=64)
	{
        for(int i = 0; i < screenWidth; i++)
		{
			float3 pixelColor = float3(0, 0, 0);
			float2 ndcPixelCentre( (2.0 * i - screenWidth) / screenWidth, (2.0 * j - screenHeight) / screenHeight );

			Camera& camera = scene.getCamera();
			Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
			
			image[j*screenWidth + i] = scene.trace(ray,0);
		}
	}
	iPart++;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL starts here. In the ray tracing example, OpenGL just outputs the image computed to the array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// Needed on MsWindows
#include <windows.h>
#endif // Win32 platform
 
#include <GL/gl.h>
#include <GL/glu.h>
// Download glut from: http://www.opengl.org/resources/libraries/glut/
#include <GL/glut.h>

// Displays the image. 
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen

	// Compute some of image. If true was returned, the image is not complete yet, so redraw the window, computing some more of it.
	if(computeImage())
		glutPostRedisplay();
	// Output the image.
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
 
    glutSwapBuffers(); // drawing finished
}


void onKeyboard(unsigned char c, int x, int y)
{
	switch(c){
	case 27: // Escape key
		exit (0);
		break;
	}
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);						// initialize GLUT
    glutInitWindowSize(600, 600);				// startup window size 
    glutInitWindowPosition(100, 100);           // where to put window on screen
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 8 bit R,G,B,A + double buffer + depth buffer

    glutCreateWindow("Ray caster");				// application window is created and displayed
 
    glViewport(0, 0, screenWidth, screenHeight);

    glutDisplayFunc(onDisplay);					// register callback
 	glutKeyboardFunc(onKeyboard);
 
    glutMainLoop();								// launch event handling loop
    
    return 0;
}

