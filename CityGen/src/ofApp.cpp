#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableDepthTest();
	ofSetWindowTitle("HighVolume3D");
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);

	ofVec3f baseSize = ofVec3f(10, 20, 10);
	ofVec3f currentPos = ofVec3f(0, 0, 0);

	buildings.assign(400, Building());

	for (int x = 0; x < CITY_GRID_X; x++)
	{
		currentPos.x += baseSize.x + 10;

		for (int y = 0; y < CITY_GRID_Y; y++)
		{
			//float heightModifier = ofRandom(100);
			//glm::vec2(x, y);
			float heightModifier = ofNoise(ofVec2f((float)x, (float)y));
			heightModifier *= 40;

			b[x][y] = Building(
						currentPos.x,
						currentPos.y,
						currentPos.z,
						baseSize.x,
						baseSize.y + heightModifier,
						baseSize.z);

			currentPos.z += baseSize.z + 10;
		}
		currentPos.z = 0;
	}

	//for (unsigned int i = 0; i < 400; i++) {


	//	buildings[i].posX
	//}

	camera.setDistance(500);
}

//--------------------------------------------------------------
void ofApp::update() {
	//float stepSize = ofGetLastFrameTime() * 10;

	//std::stringstream strm;
	//strm << "fps: " << ofGetFrameRate();
	//ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw() {
	camera.begin();

	//ofVec3f size = ofVec3f(10, 20, 10);
	//ofVec3f pos = ofVec3f(0, 0, 0);
	//ofSetColor(255, 255, 255);
	//ofFill();

	//for (int x = 1; x <= 20; x++)
	//{
	//	pos.x += size.x + 10;
	//	for (int y = 1; y <= 20; y++)
	//	{
	//		float heightModifier = ofRandom(200);

	//		ofSetColor(255, 255, 255);
	//		ofFill();
	//		ofDrawBox(pos, size.x, size.y + heightModifier, size.z);

	//		ofSetColor(0, 0, 0);
	//		ofNoFill();
	//		ofDrawBox(pos, size.x, size.y + heightModifier, size.z);
	//		pos.z += size.z + 10;
	//	}
	//	pos.z = 0;
	//}

	for (int x = 0; x < CITY_GRID_X; x++)
	{
		for (int y = 0; y < CITY_GRID_Y; y++)
		{
			ofVec3f size = ofVec3f(b[x][y].sizeX, b[x][y].sizeY, b[x][y].sizeZ);
			ofVec3f pos = ofVec3f(b[x][y].posX, b[x][y].posY, b[x][y].posZ);

			ofSetColor(255, 255, 255);
			ofFill();
			ofDrawBox(pos, size.x, size.y, size.z);

			ofSetColor(0, 0, 0);
			ofNoFill();
			ofDrawBox(pos, size.x, size.y, size.z);
		}
	}
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
