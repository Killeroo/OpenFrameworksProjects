#pragma once

#include "ofMain.h"

constexpr int ParticleCount = 10000;
constexpr float MaxVelocity = 5.f;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
		
private:
	ofVec3f _particles[ParticleCount];
	size_t _index;
};
