#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0, 0, 0);
	ofSetWindowTitle("This is a test");
	ofSetFrameRate(60);

	m_Smooth = false;
	m_CirclePosX = 0;
	m_CirclePosY = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, ofRandom(255), 0);
	ofFill();
	//ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofRandom(30));
	m_CirclePosX = ofLerp(m_CirclePosX, ofGetMouseX(), 0.075);
	m_CirclePosY = ofLerp(m_CirclePosY, ofGetMouseY(), 0.075);
	ofDrawCircle(m_CirclePosX, m_CirclePosY, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {
		m_Smooth = !m_Smooth;
		if (m_Smooth) {
			ofEnableAntiAliasing();
		}
		else {
			ofDisableAntiAliasing();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
