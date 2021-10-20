#pragma once

#include "ofMain.h"

#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void toggleClicked(bool & toggleValue);
        void amountClicked(float & amountValue);
    
        vector<std::string> readFileData(std::string path);
        map<int, float> convertFileDataToHeightMap(vector<std::string> data);
        void recalcMeshHeight();
        void setupMesh();
    
        ofEasyCam cam;
        ofMesh mesh;
        ofLight light;

        ofxPanel gui;
        ofParameter <float> uiAmount;
        ofxToggle uiToggle;
    
        map<int, float> heightMap;
        vector<ofVec3f> positions;
    
    
    
        int size = 256;//128;//96;
        bool showWireFrame;
        bool flying = false;

		
};
