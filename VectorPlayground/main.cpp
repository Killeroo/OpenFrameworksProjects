#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel(OF_LOG_WARNING);

    int windowWidth = 800;
    int windowHeight = 600;

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(windowWidth, windowHeight);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
