#include "ofApp.h"


// TODO: Implement in 3d
// Move attractors around so they crash into each other..
// TODO: Get working with timestep...
// TODO: Tweak values in imgui
// TODO: Port?


// TODO: Add variation to mass
// TODO: Rotation
#define PARTICLE_COUNT 15000

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("HighVolume");
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);

	ParticlePositions.assign(PARTICLE_COUNT, ofVec2f());
	ParticleVelocities.assign(PARTICLE_COUNT, ofVec2f());

	for (unsigned int i = 0; i < PARTICLE_COUNT; i++) {
		ParticlePositions[i].x = ofRandomWidth();
		ParticlePositions[i].y = ofRandomHeight();

		//ParticleVelocities[i].x = ofRandom(-1, 1);
		//ParticleVelocities[i].y = ofRandom(-1, 1);
	}


	AttractorPositions.push_back(ofVec2f(500.f, 500.f));
	//AttractorPositions.push_back(ofVec2f(300.f, 200.f));

	AttractorRotationAxes.push_back(ofVec2f(0.f, 1.f));
	AttractorRotationAxes.push_back(ofVec2f(0.f, 1.f));
}

ofVec2f ofApp::Rotate(const ofVec2f& p, const ofVec2f& c, const double& a) {
	return ofVec2f(c.x + (p.x - c.x) * glm::cos(a) - (p.y - c.y) * glm::sin(a),
		c.y + (p.x - c.x) * glm::sin(a) + (p.y - c.y) * glm::cos(a));
}

//--------------------------------------------------------------
void ofApp::update() {
	constexpr double kGravityConstant = 6.67e-11;
	constexpr double kSpinningStrength = 2.75f;
	constexpr float kTimeStep = 1.f;// 1.f / 60.f;

	for (unsigned int ParticleIndex = 0; ParticleIndex < ParticlePositions.size(); ParticleIndex++) 
	{
		constexpr float kParticleMass = 1000.f;

		ofVec2f& Pos = ParticlePositions[ParticleIndex];
		ofVec2f& Vel = ParticleVelocities[ParticleIndex];
		ofVec2f Force;

		for (unsigned int AttractorIndex = 0; AttractorIndex < AttractorPositions.size(); AttractorIndex++)
		{
			constexpr float kAttractorMass = 300000.f;

			const ofVec2f& AttractorPos = AttractorPositions[AttractorIndex];
			const ofVec2f& AttractorRotation = AttractorPositions[AttractorIndex];

			ofVec2f ParticleToAttractor = AttractorPos - Pos;
			const ofVec2f Direction = ParticleToAttractor.normalize();
			const float Distance = ParticleToAttractor.length();

			// Gravity
			const float GravityStrength = (kAttractorMass * kParticleMass * kGravityConstant) / glm::pow2(Distance);
			const ofVec2f GravityForce = Direction * GravityStrength;
			Force += GravityForce;

			// Spin
			//const float SpinningForce =  GravityStrength * kSpinningStrength;
			//const ofVec2f SpinningDirection = Rotate(Pos, AttractorPos, 90).normalize();
			//const ofVec2f SpinningVelocity = SpinningDirection * SpinningForce;
			//Force += SpinningVelocity;

		}
		Vel += Force * kTimeStep;
		//Vel.rotate(200, ofVec2f(0, 0));
		const float CurrentSpeed = Vel.length();
		if (CurrentSpeed > 8)
		{
			Vel = Vel.normalize() * 8;
		}
		//Vel *= 0.001f;

		//Vel.rotate(200.f);


		Pos += Vel * kTimeStep;
		
		// TODO: Bounds check
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(103, 160, 237);
	ofNoFill();

	ofMesh mesh;
	for (unsigned int i = 0; i < ParticlePositions.size(); i++) 
	{
		const ofPoint Location = ofPoint(ParticlePositions[i]);
		mesh.addVertex(Location);
	}
	ofSetColor(ofColor::white);
	//mesh.drawWireframe();
	mesh.drawVertices();

	ofSetColor(ofColor::red);
	for (const ofVec2f& AttractorPos : AttractorPositions)
	{
		ofDrawCircle(AttractorPos, 40.f);
	}
}

void ofApp::mousePressed(int x, int y, int button)
{
	AttractorPositions.push_back(ofVec2f(x, y));
}
