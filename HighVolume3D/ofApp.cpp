#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("HighVolume3D");
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);

	positions.assign(5000, ofVec3f());
	velocities.assign(5000, ofVec3f());

	for (unsigned int i = 0; i < 5000; i++) {
		positions[i].x = ofRandom(-500, 500);
		positions[i].y = ofRandom(-500, 500);
		positions[i].z = ofRandom(-500, 500);

		velocities[i].x = ofRandom(-1, 1);
		velocities[i].y = ofRandom(-1, 1);
		velocities[i].z = ofRandom(-1, 1);
	}

	camera.setDistance(500);
}

//--------------------------------------------------------------
void ofApp::update(){
	float stepSize = ofGetLastFrameTime() * 10;

	for (unsigned int i = 0; i < positions.size(); i++) {
		positions[i] += velocities[i] *stepSize;

		if (positions[i].x > 500) {
			positions[i].x = 500;
			velocities[i].x *= -0.5;
		}
		else if (positions[i].x < -500) {
			positions[i].x = -500;
			velocities[i].x *= -0.5;
		}

		if (positions[i].y > 500) {
			positions[i].y = 500;
			velocities[i].y *= -0.5;
		}
		else if (positions[i].y < -500) {
			positions[i].y = -500;
			velocities[i].y *= -0.5;
		}		
		
		if (positions[i].z > 500) {
			positions[i].z = 500;
			velocities[i].z *= -0.5;
		}
		else if (positions[i].z < -500) {
			positions[i].z = -500;
			velocities[i].z *= -0.5;
		}

	}
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();

	ofSetColor(255, 255, 255);
	ofNoFill();
	ofBox(ofVec3f(0, 0, 0), 1000);

	ofFill();
	for (unsigned int i = 0; i < positions.size(); i++) {
		if (i % 2 == 0) {
			ofSetColor(217, 77, 153, 100);
		}
		else {
			ofSetColor(255, 255, 255, 100);
		}

		ofVec3f pos = positions[i];
		ofDrawSphere(pos, 1);
	}
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
