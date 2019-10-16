#pragma once

#include "ofMain.h"
#include "ofxWarp.h"

class VProjClass{
    public:
        void setup();
        void draw();
        ofxWarpController wc;
        ofTexture tex;
        std::vector<ofRectangle> srcarea;
        ofVideoPlayer vid;
        /* WarpBase warp; */
        std::shared_ptr<ofxWarp::WarpBase> warp;
        ofRectangle bounds;
};

