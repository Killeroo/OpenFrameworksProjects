#include "ofApp.h"

// TODO: Re-write csv parsing to parse inputs as we are looping through the line...
// TODO: Move csv parsing functionality to it's own file and convert to .dat file for BusMapper to use

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();

	std::wstring BusCsvPath = L"C:\\Users\\Kelpie\\Desktop\\bus-sequences.csv";
	ofFile CsvFile(ofToDataPath(BusCsvPath), ofFile::ReadOnly, false);
	ofBuffer CsvFileBuffer(CsvFile);

	if (CsvFileBuffer.size() == 0)
	{
		ofLog(ofLogLevel::OF_LOG_ERROR, "Could not read file %s", BusCsvPath.c_str());
		return;
	}

	constexpr char kSeparatorChar = ',';
	constexpr CsvIndex kCsvIndexesToExtract[] = {
		CsvIndex::Route,
		CsvIndex::StopCode,
		CsvIndex::StopName,
		CsvIndex::LocationEasting,
		CsvIndex::LocationNorthing,
		CsvIndex::Heading
	};

	auto ExtractSectionFromLine = [](const std::string& Line, const std::vector<int>& SeparatorLocations, const int32& SeparatorIndex) -> std::string
	{
		const int32 DelimiterCount = SeparatorLocations.size() - 1;
		if (DelimiterCount >= SeparatorIndex)
		{
			const int32 SegmentStart = SeparatorIndex == 0 ? 0 : SeparatorLocations[SeparatorIndex] + 1; // Add an extra character so we skip the initial delimiter
			const int32 SegmentLength = (DelimiterCount == SeparatorIndex ? Line.length() : SeparatorLocations[SeparatorIndex + 1]) - SegmentStart;
			return Line.substr(SegmentStart, SegmentLength);
		}
		return "";
	};

	int32 CurrentLineIndex = 0;
	int32 EntryCount = 0;
	std::vector<int> SeparatorLocations;
	std::map<CsvIndex, std::string> Values;
	int32 MaxX = 0; int32 MinX = 0;
	int32 MaxY = 0; int32 MinY = 0;
	for (const std::string& Line : CsvFileBuffer.getLines())
	{
		SeparatorLocations.clear();
		Values.clear();

		EntryCount++;

		CurrentLineIndex = 0;
		for (const char& Char : Line)
		{
			if (Char == kSeparatorChar)
			{
				SeparatorLocations.push_back(CurrentLineIndex);
			}
			CurrentLineIndex++;
		}

		const int32 LineLen = Line.length();
		const int32 DelimeterCount = SeparatorLocations.size();

		// Ugh TFL, why must you have fucked up the formatting for Sidcup road..
		if (DelimeterCount <= kCsvIndexesToExtract[0] + 1)
		{
			ofLog(ofLogLevel::OF_LOG_WARNING, "Encountered badly formatted line @ %d", EntryCount);
			continue;
		}

		// There are multiple runs for any given bus stop but they duplicate a lot of data and don't seem to vary that much so
		// we only want to extract the first run
		if (ExtractSectionFromLine(Line, SeparatorLocations, CsvIndex::Run) != "1")
		{
			continue;
		}

		// Extract each of the values we want from the current line in csv
		bool bLineCurrupted = false;
		for (int32 Index = 0; Index < sizeof(kCsvIndexesToExtract); Index++)
		{
			const CsvIndex CurrentIndex = kCsvIndexesToExtract[Index];
			const string CurrentValue = ExtractSectionFromLine(Line, SeparatorLocations, CurrentIndex);

			if (CurrentValue == "")
			{
				// TODO: Don't worry if heading is blank
				bLineCurrupted = true;
				break;
			}
			else
			{
				Values.emplace(CurrentIndex, CurrentValue);
			}
		}

		// There are missing values in this line, move onto next one
		if (bLineCurrupted)
		{
			ofLog(ofLogLevel::OF_LOG_WARNING, "Encountered corrupted values at line %d", EntryCount);
			//ofLog(ofLogLevel::OF_LOG_WARNING, "%s", Line.c_str());
			continue;
		}
		ofLog(ofLogLevel::OF_LOG_WARNING, "%s", Line.c_str());

		const string StopId = Values[CsvIndex::StopCode];
		if (map.Stops.find(StopId) == map.Stops.end())
		{
			// We got a new stop so lets add it
			Stop newStop;
			newStop.Id = StopId;
			newStop.Name = Values[CsvIndex::StopName];
			newStop.Heading = static_cast<int32>(std::stoul(Values[CsvIndex::Heading]));

			Coordinate stopCoordinates;
			stopCoordinates.X = static_cast<int32>(std::stoul(Values[CsvIndex::LocationEasting]));
			stopCoordinates.Y = static_cast<int32>(std::stoul(Values[CsvIndex::LocationNorthing]));
			newStop.Pos = stopCoordinates;

			if (MinY == 0 || MinY > stopCoordinates.Y)
			{
				MinY = stopCoordinates.Y;
			}
			if (MaxY < stopCoordinates.Y)
			{
				MaxY = stopCoordinates.Y;
			}
			if (MinX == 0 || MinX > stopCoordinates.X)
			{
				MinX = stopCoordinates.X;
			}
			if (MaxX < stopCoordinates.X)
			{
				MaxX = stopCoordinates.X;
			}

			map.Stops.emplace(Values[CsvIndex::StopCode], newStop);
		}

		const string Route = Values[CsvIndex::Route];
		ofLog(ofLogLevel::OF_LOG_NOTICE, "-> %s", Route.c_str());
		if (map.Routes.find(Route) == map.Routes.end())
		{
			std::vector<Coordinate> stopLocations;
			map.Routes.emplace(Route, stopLocations); // TODO: Convert to ofVec2f
		}

		// Add the new stop to the route
		map.Routes[Route].push_back(map.Stops[StopId].Pos);
	}
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Counted %d", EntryCount);
}

//--------------------------------------------------------------
void ofApp::update(){

}

template<typename tVal>
tVal map_value(std::pair<tVal, tVal> a, std::pair<tVal, tVal> b, tVal inVal)
{
	tVal inValNorm = inVal - a.first;
	tVal aUpperNorm = a.second - a.first;
	tVal normPosition = inValNorm / aUpperNorm;

	tVal bUpperNorm = b.second - b.first;
	tVal bValNorm = normPosition * bUpperNorm;
	tVal outVal = b.first + bValNorm;

	return outVal;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofMesh mesh;
	std::pair<float, float> InRangeX(497000.f, 562000.f);
	std::pair<float, float> OutRangeX(1.f, 1000.f);

	std::pair<float, float> InRangeY(148000.f, 202000.f);
	std::pair<float, float> OutRangeY(1.f, 1000.f);

	/*for (const std::pair<const string, Stop>& stop : map.Stops)
	{
		const ofPoint Location = ofPoint(map_value(InRangeX, OutRangeX, (float)stop.second.Pos.X), map_value(InRangeY, OutRangeY, (float)stop.second.Pos.Y), 1.f);
		mesh.addVertex(Location);
	}*/

	const std::vector<Coordinate>& Coords = map.Routes["190"];

	for (const Coordinate& Pos : Coords)
	{
		const ofPoint Location = ofPoint(map_value(InRangeX, OutRangeX, (float)Pos.X), map_value(InRangeY, OutRangeY, (float)Pos.Y), 1.f);
		mesh.addVertex(Location);
	}
	ofSetColor(ofColor::black);
	mesh.drawWireframe();
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
