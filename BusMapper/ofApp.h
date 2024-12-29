#pragma once

#include "ofMain.h"

typedef int32_t int32;
typedef uint32_t uint32;
typedef uint16_t ushort;
typedef uint8_t byte;
typedef std::string string;

struct Coordinate
{
	uint32 X;
	uint32 Y;

	Coordinate() { }
	Coordinate(uint32 x, uint32 y) : X(x), Y(y) { }
};

struct Stop
{
	string Id;
	string Name;
	Coordinate Pos;
	ushort Heading;

	Stop() { }
	Stop(string id, string name, Coordinate pos, ushort heading) 
		: Id(id), Name(name), Pos(pos), Heading(heading) { }
};

struct Map
{
	std::map<string, Stop> Stops;
	std::map<string, std::vector<Coordinate>> Routes;
	Coordinate Bounds;
};


// These related to a 0 indexed column in the bus data csv
enum CsvIndex : byte
{
	Route = 0,
	Run = 1,
	StopCode = 3,
	StopName = 5,
	LocationEasting = 6,
	LocationNorthing = 7,
	Heading = 8
};

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

private:
	Map map;
		
};
