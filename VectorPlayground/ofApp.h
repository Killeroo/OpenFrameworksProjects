#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#include <iostream>
#include <list>

enum vpOperation
{
	Addition,
	Subtraction,
	Multiplication,
	Division
};

struct vpExpression
{
	ofVec2f a;
	ofVec2f b;
	vpOperation operation;

	ofVec2f Solve();
};

struct vpVector
{
public:
	int id = 0;
	ofVec2f length = ofVec2f(0.f, 0.f);
	ofVec2f start = ofVec2f(0.f, 0.f);
	ofVec2f end = ofVec2f(0.f, 0.f); // TODO: Remove?
	ofColor color = ofColor::red;

public:
	void draw();
	void reset();
};

class vpCalculator
{
public:
	void addVector(vpVector* input);
	void addOperation(vpOperation op);
	ofVec2f calculate();

public:
	const std::vector<vpVector*>& GetInputs() const { return pendingInputs; };
	const std::vector<vpOperation>& GetOperations() const { return pendingOperations; };

private:
	// TODO: Replace with single expression!
	std::vector<vpVector*> pendingInputs;
	std::vector<vpOperation> pendingOperations;
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void drawGui();

	void drawVector(vpVector& vector);
	void drawVectorList();
	void drawCalculator();

	bool isClickingOnMenu(const ofVec2f& position);
	inline ImVec4 ofColorToImVec4(const ofColor& color);

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:
	ofxImGui::Gui gui;
	ofVec2f menuPosition = ofVec2f(0.f, 0.f);
	ofVec2f menuSize = ofVec2f(0.f, 0.f);

	int currentVectorId = 0;
	int currentIndex = -1;

	vpCalculator calculator;
	std::vector<vpVector> vectors;
};
