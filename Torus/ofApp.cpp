#include "ofApp.h"
// Source: https://github.com/a1kageyama/MovingTorus/blob/master/ofApp.cpp

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Torus");
	ofSetFrameRate(30);

	ofBackground(70, 70, 70);
	ofSetLineWidth(2);
	ofEnableDepthTest(); // What does this do
	ofEnableAlphaBlending(); // What does this do

	gui.setup();
	gui.add(radius.setup("radius", 300, 10, 500));
	gui.setTextColor(ofColor::crimson);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	// Start our camera
	this->cam.begin();

	ofColor color;

	for (int r = 200; r >= 25; r -= 25) {
		ofRotate(ofGetFrameNum() * 0.5);

		int start = ofGetFrameNum();

		for (int v = start; v < start + 40; v += 8) {
			for (int u = 0; u < 360; u += 10) {

				//ofSetColor(255, 150, 255, 180);
				//ofFill();

				//ofBeginShape();
				//ofVertex(this->makePoint(300, r, u - 9.9, v - 4.9));
				//ofVertex(this->makePoint(300, r, u + 9.9, v - 4.9));
				//ofVertex(this->makePoint(300, r, u + 9.9, v + 4.9));
				//ofVertex(this->makePoint(300, r, u - 9.9, v + 4.9));
				//ofEndShape(true);

				ofSetColor(255, 50, 50, 200);
				ofNoFill();


				ofBeginShape();
				ofVertex(this->makePoint(radius, r, u - 10, v - 5));
				ofVertex(this->makePoint(radius, r, u + 10, v - 5));
				ofVertex(this->makePoint(radius, r, u + 10, v + 5));
				ofVertex(this->makePoint(radius, r, u - 10, v + 5));
				ofEndShape(true);
			}
		}

	}
	
	cam.end();
}

glm::vec3 ofApp::makePoint(float R, float r, float u, float v)
{
	// Transform our points to radians
	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	float x = (R + r * cos(u)) * cos(v);
	float y = (R + r * cos(u)) * sin(v);
	float z = r * sin(u);

	return glm::vec3(x, y, z);
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