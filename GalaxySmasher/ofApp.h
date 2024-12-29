#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);

private:
	vector<ofVec2f> ParticlePositions;
	vector<ofVec2f> ParticleVelocities;
	vector<ofVec2f> AttractorPositions;
	vector<ofVec2f> AttractorRotationAxes;

	ofVec2f Rotate(const ofVec2f& p, const ofVec2f& c, const double& a);
};
