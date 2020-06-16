#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		ofEasyCam camera;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		
};
