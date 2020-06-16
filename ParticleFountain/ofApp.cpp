#include "ofApp.h"

class Particle : public ofVec3f
{
public:
	vector<ofVec3f> previousPositions;
	ofVec3f vel, acc;
	ofColor color;
	int mass;
	int life;

	Particle()
	{
		Particle(ofColor(255, 255, 255), 1, 300, ofVec3f(0, 0, 0));
	}
	Particle(ofColor c, int m, int l,  ofVec3f pos)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;

		color = c;
		mass = m;
		life = l;

		vel = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
	}

	void update(float timestep)
	{
		vel += acc;
		*this += vel * timestep;

		//vel.limit(40);

		acc.set(0, 0, 0);

		if (x < -2500 || x > 2500) {
			vel.x = -vel.x;
		}
		if (y < -2500 || y > 2500) {
			vel.y = -vel.y;
		}
		if (z < -2500 || z > 2500) {
			vel.z = -vel.z;
		}

		previousPositions.insert(previousPositions.begin(), *this);

		life--;
	}

	void display()
	{
		ofVec3f copy = vel;
		copy.normalize();
		ofSetColor(ofMap(copy.x, 0, 1, 20, 255), ofMap(copy.y, 0, 1, 20, 255), ofMap(copy.z, 0, 1, 20, 255));
		ofDrawSphere(*this, 1);

		ofVec3f previous = ofVec3f(-6000, -6000, -6000);
		for (unsigned int i = 0; i < previousPositions.size(); i++) {

			if (previous != ofVec3f(-6000, -6000, -6000)) {
				ofDrawLine(previous, previousPositions[i]);
			}

			previous = previousPositions[i];
		}

		if (previousPositions.size() > 20) {
			previousPositions.pop_back();
		}
	}

	void aimForTarget(ofVec3f location, float force)
	{
		ofVec3f d = location - *this;
		d.normalize();
		applyForce(d);
		/*d *= force;
		acc = d;*/
	}

	void applyForce(ofVec3f force)
	{
		acc += force / mass;
	}

	bool isDead()
	{
		if (life <= 0) {
			return true;
		} else {
			return false;
		}
	}
};

const int PARTICLE_COUNT = 100;

vector<Particle> particles;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("ConfigurableParticles ");
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	
	camera.setDistance(500);

	particles.assign(PARTICLE_COUNT, Particle());
	
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i] = Particle(
			ofColor(ofRandom(255), ofRandom(255), ofRandom(255)),
			ofRandom(0.5, 2),
			ofRandom(200, 500),
			ofVec3f(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500))
		);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float stepSize = ofGetLastFrameTime() * 10;

	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i].aimForTarget(ofVec3f(0, 0, 0), 2);
		particles[i].applyForce(ofVec3f(0, -0.3, 0));
		particles[i].update(stepSize);
	}

	std::stringstream strm;
	strm << "Configurable Particles fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();

	ofSetColor(255, 255, 255);
	ofNoFill();
	ofBox(ofVec3f(0, 0, 0), 2500);

	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i].display();
	}

	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
