#pragma once

#include "ofMain.h"
#include "ofxWarp.h"

/*-- use this to toggle HAP player --*/

#define HAPAVAPLAYER // comment out for ofVideoPlayer

#ifdef HAPAVAPLAYER
#include "ofxHAPAVPlayer.h"
#endif


class VProjClass{
    public:
        void setup();
        void draw();
        ofxWarpController wc;
        ofTexture tex;
        std::vector<ofRectangle> srcarea;
#ifdef HAPAVAPLAYER
        ofxHAPAVPlayer vid;
#else
        ofVideoPlayer vid;
#endif
        
        /* auto warp; */
        std::shared_ptr<ofxWarp::WarpBase> warp;
        ofRectangle bounds;
        string s;
        int change;
    VProjClass() {
        
        ofLog() << "initiating VProjClass - set vid to use pixels";
#ifdef HAPAVAPLAYER
        vid.setUsePixels(true);
        ofLog() << "USING HAPAVPLAYER";
#endif
    }
    ~VProjClass() {
        ofLog() << "deleting one VProjClass";
        vid.close();
    }
};

