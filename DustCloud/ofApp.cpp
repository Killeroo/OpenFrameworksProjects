#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	for (_index = 0; _index < ParticleCount; _index++)
	{
		_particles[_index] = ofVec3f(
			ofRandom(ofRandomWidth()),
			ofRandom(ofRandomHeight()),
			ofRandom(ofRandom(1.f, MaxVelocity)));
	}

	ofBackground(0.f);
}

//--------------------------------------------------------------
void ofApp::update()
{
	const float DeltaTime = glm::max(1.0, ofGetLastFrameTime());
	const float WindowWidth = ofGetWindowWidth();
	const float WindowHeight = ofGetWindowHeight();

	for (_index = 0; _index < ParticleCount; _index++)
	{
		ofVec3f& particle = _particles[_index];
		
		particle.x += particle.z * DeltaTime;
		particle.y += particle.z * DeltaTime;

		if (particle.x < 0)
		{
			particle.x = WindowWidth;
		}
		if (particle.x > WindowWidth)
		{
			particle.x = 0;
		}
		if (particle.y < 0)
		{
			particle.y = WindowHeight;
		}
		if (particle.y > WindowHeight)
		{
			particle.y = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	for (_index = 0; _index < ParticleCount; _index++)
	{
		const ofVec3f& particle = _particles[_index];

		const ofColor Color = ofColor(
			ofMap(particle.z, 1.f, MaxVelocity, 0.f, 255.f), 
			ofMap(particle.z, 1.f, MaxVelocity, 50.f, 150.f), 
			25.f);

		ofSetColor(Color);
		ofDrawCircle(particle, 2.f);
	}
}