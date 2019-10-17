#pragma once

#include "ofMain.h"
#include "ofxWarp.h"
#include "VProjClass.h"
#include "ofxCvHaarFinder.h"

class ofApp
	: public ofBaseApp
{
public:
	void setup();
	void exit();

	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	bool useBeginEnd;
	ofxWarpController warpController;
	/* ofxWarpController warpController2; */
	ofTexture texture;
        /* ofTexture texture2; */
	std::vector<ofRectangle> srcAreas;
	int areaMode;
	std::string areaName;
        ofVideoPlayer test;
        /* VProjClass vp[2]; */
        int count;
        vector <VProjClass> vp;
        string str;
        /* VProjClass vp1; */
        /* ofVideoPlayer test2; */
        ofxCvColorImage color;
        ofxCvGrayscaleImage gray;
        ofxCvHaarFinder finder;
        ofVideoGrabber vidGrabber;
        vector < string > linesOfTheFile;
        int camWidth;
        int camHeight;
};

