#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("HighVolume2");
	ofSetWindowShape(1000, 1000);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);

	positions.assign(5000, ofVec2f());
	velocities.assign(5000, ofVec2f());
	accelerations.assign(5000, ofVec2f());

	for (unsigned int i = 0; i < 5000; i++) {
		positions[i].x = ofRandomWidth();
		positions[i].y = ofRandomHeight();
		
		velocities[i].x = ofRandom(-1, 1);
		velocities[i].y = ofRandom(-1, 1);

		accelerations[i] = ofVec2f(0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	ofVec2f target = ofVec2f(ofGetMouseX(), ofGetMouseY());
	
	float stepSize = ofGetLastFrameTime() * 10;

	for (unsigned int i = 0; i < positions.size(); i++) {
		velocities[i] += accelerations[i] * stepSize;
		positions[i] += velocities[i] * stepSize;

		ofVec2f distance = target - positions[i];
		distance.normalize();
		distance *= 0.5;
		accelerations[i] += distance;

		velocities[i].limit(25);

		if (positions[i].x > width) {
			positions[i].x = width;
			velocities[i].x *= -0.5;
		}
		else if (positions[i].x < 0) {
			positions[i].x = 0;
			velocities[i].x *= -0.5;
		}

		if (positions[i].y > height ) {
			positions[i].y = height;
			velocities[i].y *= -0.5;
		} else if (positions[i].y < 0) {
			positions[i].y = 0;
			velocities[i].y *= -0.5;
		}

	}


	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0, 40);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	ofFill();

	for (unsigned int i = 0; i < positions.size(); i++) {
		if (i % 2 == 0) {
			ofSetColor(217, 77, 153, 100);
		} else {
			ofSetColor(255, 255, 255, 100);
		}

		ofDrawCircle(positions[i], 1);
	}
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
