/**
* \ingroup Examples
* \file Tentacle.cpp
* \brief This program is a simple introduction how to use simple inverse kinematics and Horde3D next gen rendering engine 
*  with Smr
*/

#include <iostream>
#include "Tentacle.h"


// Configuration
const char *caption = "tentacle - Horde3D Sample";
const int appWidth = 800;
const int appHeight = 600;
static bool fullScreen = false;


bool setupWindow( int, int, bool );
static bool running;
static double t0;
static int mx0, my0;
static TentacleApplication *app;


int GLFWCALL windowCloseListener()
{
	running = false;
	return 0;
}


void GLFWCALL keyPressListener( int key, int action )
{
	if( !running ) return;

	if( action == GLFW_PRESS )
	{
		int width = appWidth, height = appHeight;
		
		switch (key)
		{
		case GLFW_KEY_ESC:
			running = false;
			break;
		case GLFW_KEY_SPACE:
			app->keyPressEvent( key );
			break;
		case GLFW_KEY_F1:
			app->release();
			glfwCloseWindow();
			
			// Toggle fullscreen mode
			fullScreen = !fullScreen;

			if( fullScreen )
			{
				GLFWvidmode mode;
				glfwGetDesktopMode( &mode );
				
				float aspect = mode.Width / (float)mode.Height;
				if( (int)(aspect * 100) == 133 || (int)(aspect * 100) == 125 )	// Standard
				{
					width = 1280; height = 1024;
				}
				else if( (int)(aspect * 100) == 160 )							// Widescreen
				{
					width = 1280; height = 800;
				}
				else															// Unknown
				{
					// Use desktop resolution
					width = mode.Width; height = mode.Height;
				}
			}
			
			if( !setupWindow( width, height, fullScreen ) )
			{
				glfwTerminate();
				exit( -1 );
			}
			
			app->init();
			app->resize( width, height );
			t0 = glfwGetTime();
			break;
		default:
			app->keyPressEvent( key );
			break;
		}
	}

	if( key >= 0 ) app->keyStateChange( key, action == GLFW_PRESS );
}


void GLFWCALL mouseMoveListener( int x, int y )
{
	if( !running )
	{
		mx0 = x; my0 = y;
		return;
	}

	app->mouseMoveEvent( (float)(x - mx0), (float)(my0 - y) );
	mx0 = x; my0 = y;
}


bool setupWindow( int width, int height, bool fullscreen )
{
	// Create OpenGL window
	if( !glfwOpenWindow( width, height, 8, 8, 8, 8, 24, 8, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) )
	{
		glfwTerminate();
		return false;
	}

	if( !fullscreen ) glfwSetWindowTitle( caption );
	
	// Disable vertical synchronization
	glfwSwapInterval( 0 );

	// Set listeners
	glfwSetWindowCloseCallback( windowCloseListener );
	glfwSetKeyCallback( keyPressListener );
	glfwSetMousePosCallback( mouseMoveListener );
	
	return true;
}

std::string generatePath(char p[], const std::string& file) {
#ifdef __APPLE__
   string s(p);
   for (int i = 0; i < 4; i++)
      s = s.substr(0, s.rfind("/"));   
   return s + "/" + file;
#else
    const std::string s( p );
    if ( s.find("/") != std::string::npos) {
        return s.substr( 0, s.rfind( "/" ) ) + "/" + file;
    } else if ( s.find("\\") != std::string::npos ) {
        return s.substr( 0, s.rfind( "\\" ) ) + "\\" + file;
    } else {
        return file;
    }
#endif
}

int main( int argc, char** argv )
{
	// Initialize GLFW
	glfwInit();
	if( !setupWindow( appWidth, appHeight, fullScreen ) ) return -1;
	
	// Initalize application and engine
	app = new TentacleApplication( generatePath( argv[0], "../../../Data/HordeContent" ) );
	if ( !app->init() )
	{
		// Fake message box
		glfwCloseWindow();
		glfwOpenWindow( 800, 16, 8, 8, 8, 8, 24, 8, GLFW_WINDOW );
		glfwSetWindowTitle( "Unable to initalize engine - Make sure you have an OpenGL 2.0 compatible graphics card" );
		glfwSleep( 5 );
		
		std::cout << "Unable to initalize engine" << std::endl;
		std::cout << "Make sure you have an OpenGL 2.0 compatible graphics card";
		glfwTerminate();
		h3dSetOption(H3DOptions::MaxLogLevel, 0.0);
		return -1;

	}
	app->resize( appWidth, appHeight );

	glfwDisable( GLFW_MOUSE_CURSOR );

	

	int frames = 0;
	float fps = 30.0f;
	t0 = glfwGetTime();
	running = true;

	// Game loop
	while( running )
	{
		// Calc FPS
		++frames;
		if( frames >= 3 )
		{
			double t = glfwGetTime();
			fps = frames / (float)(t - t0);
			frames = 0;
			t0 = t;
		}

		// Render
		app->mainLoop( fps );
		glfwSwapBuffers();
	}

	glfwEnable( GLFW_MOUSE_CURSOR );

	// Quit
	app->release();
	delete app;
	glfwTerminate();

	return 0;
}
