#include "ofApp.h"

//https://youtu.be/7axImc1sxa0

const float GRAVITATIONAL_CONSTANT = 0.0001f;
const float TIMESTEP = 10;//0.01f;

class Planet
{
public:
	ofVec3f pos, vel, acc;
	ofColor color;
	float mass;
	float radius;
	int index;

	Planet() {}

	Planet(ofVec3f p, ofVec3f v, ofColor c, float m, float r, int i)
	{
		pos = p;
		vel = v;
		acc = ofVec3f(0, 0, 0);

		color = c;
		mass = m;
		radius = r;

		index = i;
	}

	// TODO: Change planets array to pointer
	void UpdateVelocity(Planet planets[], float timestep)
	{
		// Newton's law of universal gravitation
		// force = gravitational_constant * (mass_1 * mass_2 / radius squared)

		for (int i = 0; i < 2; i++) {// sizeof(planets) / sizeof(planets[0]); i++) {
			/*if (&planets[i] != this)
			{*/
			if (i != index)
			{
				float squaredDistance = planets[i].pos.squareDistance(pos);
				ofVec3f forceDirection = (planets[i].pos - pos).normalized();
				ofVec3f force = forceDirection * GRAVITATIONAL_CONSTANT * mass * planets[i].mass / squaredDistance;
				ofVec3f acceleration = force / mass;
				vel += acceleration * timestep;
			}
			//}
		}
	}

	void UpdatePosition(float timestep)
	{
		pos += vel * timestep;
	}

	void Display()
	{
		ofSetColor(color);
		ofDrawSphere(pos, radius);
	}
};

Planet planets[2];

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Orbits");
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);

	camera.setDistance(500);

	planets[0] = Planet(
		ofVec3f(20, 20, 20),
		ofVec3f(0, 0, 0.1),
		ofColor(255, 0, 0, 255),
		10000,
		4,
		0
	);

	planets[1] = Planet(
		ofVec3f(20, 100, 20),
		ofVec3f(0.1, 0, 0.1),
		ofColor(0, 255, 0, 255),
		500,
		2,
		1
	);
}

//--------------------------------------------------------------
void ofApp::update(){

	for (int i = 0; i < 2; i++) {// sizeof(planets) / sizeof(planets[0]); i++) {
		planets[i].UpdateVelocity(planets, TIMESTEP);
	}

	for (int i = 0; i < 2; i++) {// sizeof(planets) / sizeof(planets[0]); i++) {
		planets[i].UpdatePosition(TIMESTEP);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();

	ofSetColor(255, 255, 255);
	ofNoFill();
	ofBox(ofVec3f(0, 0, 0), 2500);

	for (int i = 0; i < 2; i++) {// sizeof(planets) / sizeof(planets[0]); i++) {
		planets[i].Display();
	}

	camera.end();


	std::stringstream strm;
	strm << "Orbits fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
