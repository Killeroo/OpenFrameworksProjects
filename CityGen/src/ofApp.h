#pragma once

#include "ofMain.h"
#include "Building.h"

class ofApp : public ofBaseApp {

public:

	const static int CITY_GRID_X = 20;
	const static int CITY_GRID_Y = 20;

	ofEasyCam camera;

	vector<Building> buildings;
	Building b [CITY_GRID_X][CITY_GRID_Y];

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
