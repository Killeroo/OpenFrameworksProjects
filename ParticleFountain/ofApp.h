#pragma once

#include "ofMain.h"

//class ParticleSystem
//{
//public:
//	ParticleSystem();
//
//	void init();
//	void update();
//	void display();
//
//	void applyForce(ofVec3f force);
//private:
//	Particle* particles;
//	unsigned int count = 1000;
//};
//
//class Particle : public ofVec3f
//{
//public:
//	ofVec3f vel, acc;
//	ofVec3f bounds;
//	ofColor color;
//	int mass;
//	int life;
//
//	Particle();
//	Particle(int m, int l, ofVec3f b, ofVec3f pos);
//
//	void update();
//	void display();
//	void applyForce(ofVec3f force);
//
//	bool isDead();
//	void setBounds(ofVec3f b);
//};

class ofApp : public ofBaseApp{

	public:

		ofEasyCam camera;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		
};


