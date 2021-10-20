#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofEnableLighting();
    ofEnableDepthTest();
    
    glShadeModel(GL_FLAT);
    
    showWireFrame = false;

    gui.setup();
    gui.add(uiAmount.set("Height multiplier", 0, -100, 100));
    gui.add(uiToggle.setup("Wireframe", showWireFrame));
    
    uiToggle.addListener(this, &ofApp::toggleClicked);
    uiAmount.addListener(this, &ofApp::amountClicked);
    
    vector<std::string> lines = ofApp::readFileData("interpol.csv");//kensington3.csv");
    heightMap = ofApp::convertFileDataToHeightMap(lines);
    ofApp::setupMesh();
    ofApp::recalcMeshHeight();
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (flying)
    {
        int count = 0;
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                ofVec3f position = mesh.getVertex(count);
                position += positions[count];
                mesh.setVertex(count, position);
                count++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    cam.begin();
    //light.enable();
    //light.setParent(cam);
    ofPushMatrix();
    ofSetColor(255);
    
    if (showWireFrame) {
        mesh.drawWireframe();
    } else {
        mesh.drawFaces();
    }
    ofPopMatrix();
    //light.disable();
    cam.end();
    
    gui.draw();
}

void ofApp::toggleClicked(bool &toggleValue)
{
    showWireFrame = toggleValue;
}

void ofApp::amountClicked(float &amountValue)
{
    ofLog(OF_LOG_NOTICE, std::to_string(amountValue));
    float amt = amountValue;
    recalcMeshHeight();
}

vector<std::string> ofApp::readFileData(std::string path)
{
    vector<std::string> lines;
    
    // Read each line of file into a vector
    ofBuffer buffer = ofBufferFromFile(path);
    for (auto line : buffer.getLines())
    {
        lines.push_back(line);
    }
    
    return lines;
}

map<int, float> ofApp::convertFileDataToHeightMap(vector<std::string> data)
{
    map<int, float> cellHeights;
    
    // Seperate out values on each line, number them and add to height map
    int count = 1;
    for (auto cell : data)
    {
        size_t pos = 0;
        std::string token;
        std::string delimiter = ",";
        while ((pos = cell.find(delimiter)) != std::string::npos)
        {
            token = cell.substr(0, pos);
            cellHeights.insert(std::pair<int, float>(count, std::stof(token)));
            cell.erase(0, pos + delimiter.length());
            
            count++;
        }
        
    }
    
    return cellHeights;
}

void ofApp::recalcMeshHeight()
{
    int c1 = 0;
    int c2 = 1;
    
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
          float g = ofMap(heightMap[c2], 0, 2500, 0, 255);
          
          ofVec3f position = mesh.getVertex(c1);
          position.z = ofMap(heightMap[c1], 0, 2500, 0, 150); //uiAmount
          mesh.setVertex(c1, position);
          mesh.setColor(c1, ofColor(g, g, g, 255));
          
          c1++;
          c2++;
      }
    }
}

void ofApp::setupMesh()
{
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
  
    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){
            mesh.addVertex(ofPoint(x - size / 2, y - size / 2));
            mesh.addColor(ofColor(0, 255, 0, 255));
        }
    }
  
    for (int x = 0; x < size - 1; x++){
        for (int y = 0; y < size - 1; y++){
            mesh.addIndex(x + y * size);
            mesh.addIndex((x + 1) + y * size);
            mesh.addIndex(x + (y + 1) * size);
        
            mesh.addIndex((x + 1) + y * size);
            mesh.addIndex((x + 1) + (y + 1) * size);
            mesh.addIndex(x + (y + 1) * size);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    flying = true;
    
    int c = 0;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            positions.push_back(ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2), ofRandom(-2, 2)));
            c++;
        }
    }
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
