#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("HighVolume");
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);

	positions.assign(1500, ofVec2f());
	velocities.assign(1500, ofVec2f());

	for (unsigned int i = 0; i < 1500; i++) {
		positions[i].x = ofRandomWidth();
		positions[i].y = ofRandomHeight();

		velocities[i].x = ofRandom(-1, 1);
		velocities[i].y = ofRandom(-1, 1);
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	for (unsigned int i = 0; i < positions.size(); i++) {
		positions[i].x += velocities[i].x * 0.5;
		positions[i].y += velocities[i].y * 0.5;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(103, 160, 237);
	ofNoFill();

	for (unsigned int i = 0; i < positions.size(); i++) {
		ofDrawCircle(positions[i].x, positions[i].y, 2);
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
