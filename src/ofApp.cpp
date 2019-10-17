#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    /* ofToggleFullscreen(); */
    
    camWidth = 480;  // try to grab at this size.
    camHeight = 360;

    //get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    ofBuffer buffer = ofBufferFromFile("CLIPS/allmp4.txt");
    for (auto line : buffer.getLines()){
        linesOfTheFile.push_back(line);
    }


    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    vidGrabber.setDeviceID(1);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.setup(camWidth,camHeight);
    ofSetVerticalSync(true);
    color.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    gray.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    finder.setup("haarcascade_frontalface_default.xml");

	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableArbTex();
	ofBackground(ofColor::black);
        str = "settings";

        for(count=0; count < 9; count++) {
            vp.push_back( VProjClass()  );
            /* vp.back().vid.load("output.mp4"); */
            /* vp.back().vid.setLoopState(OF_LOOP_NORMAL); */
            /* vp.back().vid.play(); */
            /* string lala = "output"; */
            /* lala.append(to_string(count)); */
            /* lala.append(".mp4"); */
            string lala = "CLIPS/";
            lala.append(linesOfTheFile[count]);
            cout << "it is me " << lala << endl;
            vp[count].vid.load(lala);
            vp[count].vid.setLoopState(OF_LOOP_NORMAL);
            vp[count].vid.play();
            vp[count].change = (int)ofRandom(5,10);

            string temp = str;
            temp.append(to_string(count));
            temp.append(".json");
	    /* this->vp.back().tex.enableMipmap(); */
            /* this->vp.back().tex.loadData(vp[count].vid.getPixels()); */
	    /* // Load warp settings from file if one exists. */
	    /* this->vp.back().wc.loadSettings(temp); */

            vp[count].s= temp; 
	    this->vp[count].tex.enableMipmap();
            this->vp[count].tex.loadData(vp[count].vid.getPixels());
	    // Load warp settings from file if one exists.
	    this->vp[count].wc.loadSettings(vp[count].s);
        }
	/* if (this->vp[i].wc.getWarps().empty()) */
	/* { */
		// Otherwise create warps from scratch.
		/* std::shared_ptr<ofxWarpBase> warp; */ 
		
		/* warp = this->vp[i].wc.buildWarp<ofxWarpPerspective>(); */
		/* warp->setSize(this->vp[i].tex.getWidth(), this->vp[i].tex.getHeight()); */
		/* warp->setEdges(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); */
		
		/* warp = this->vp[i].wc.buildWarp<ofxWarpBilinear>(); */
		/* warp->setSize(this->vp[i].tex.getWidth(), this->vp[i].tex.getHeight()); */
		/* warp->setEdges(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); */
		
		/* warp = this->vp[i].wc.buildWarp<ofxWarpPerspectiveBilinear>(); */
		/* warp->setSize(this->vp[i].tex.getWidth(), this->vp[i].tex.getHeight()); */
		/* warp->setEdges(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f)); */
		
		/* warp = this->vp[i].wc.buildWarp<ofxWarpPerspectiveBilinear>(); */
		/* warp->setSize(this->vp[i].tex.getWidth(), this->vp[i].tex.getHeight()); */
		/* warp->setEdges(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f)); */
	/* } */

        for(count=0; count < vp.size(); count++) {
            this->vp[count].srcarea.resize(this->vp[count].wc.getNumWarps());
        }

	// Start with full area mode.
    this->areaMode = -1;
    this->keyPressed('a');
	
    this->useBeginEnd = false;
}

//--------------------------------------------------------------
void ofApp::exit()
{
        for(count = 0; count < vp.size(); count++) {
            /* this->vp[count].wc.saveSettings("settings.json"); */
        }
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2) + " FPS :: " + areaName + " :: " + (this->useBeginEnd ? "begin()/end()" : "draw()"));
        for(count=0; count < vp.size(); count++) {
            vp[count].vid.update();
            this->vp[count].tex.loadData(vp[count].vid.getPixels());
        }
    ofBackground(100, 100, 100);    
    vidGrabber.update();

    /* cout<< "timer "<< (int)ofGetElapsedTimef() << endl; */

    for(count = 0; count < vp.size(); count++) {
        if(vp[count].change < (int)ofGetElapsedTimef()){
            vp[count].vid.close();
            string clip = "CLIPS/";
            vp[count].vid.load(clip.append(linesOfTheFile[(int)ofRandom(0,10000)]));
            vp[count].vid.play();
            vp[count].change += vp[count].change;
        }
    }
    if(vidGrabber.isFrameNew()){
        color.setFromPixels(vidGrabber.getPixels());
        gray = color ;
        finder.findHaarObjects(gray);
    } 
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(ofColor::black);
        for(count=0; count < vp.size(); count++) {
            if (this->vp[count].tex.isAllocated())
            {
                    for (auto i = 0; i < this->vp[count].wc.getNumWarps(); ++i)
                    {
                            vp[count].warp = this->vp[count].wc.getWarp(i);
                            /* std::cout << to_string(&vp[count].warp) << endl; */
                            if (this->useBeginEnd)
                            {
                                    std::cout << "lala" << endl;
                                    vp[count].warp->begin();
                                    {
                                            vp[count].bounds = vp[count].warp->getBounds();
                                            this->vp[count].tex.drawSubsection(vp[count].bounds.x, vp[count].bounds.y, vp[count].bounds.width, vp[count].bounds.height, this->vp[count].srcarea[i].x, this->vp[count].srcarea[i].y, this->vp[count].srcarea[i].width, this->vp[count].srcarea[i].height);
                                    }
                                    vp[count].warp->end();
                            }
                            else
                            {
                                    /* vp[count].warp->draw(this->vp[count].tex, this->vp[count].srcarea[i]); */
                                    ofRectangle myRect(0, 0, 640, 360);
                                    vp[count].warp->draw(vp[count].tex, myRect);
                            }
                    }
            }
        }

	/* std::ostringstream oss; */
	/* oss << ofToString(ofGetFrameRate(), 2) << " fps" << endl; */
	/* oss << "[a]rea mode: " << areaName << endl; */
	/* oss << "[a]rea mode: " << vp[0].s << endl; */
	/* oss << "[a]rea mode: " << vp[1].s << endl; */
	/* oss << "[a]rea mode: " << vp[2].s << endl; */
	/* oss << "[d]raw mode: " << (this->useBeginEnd ? "begin()/end()" : "draw()") << endl; */
        /* for(count=0; count < vp.size(); count++) { */
            /* oss << "[w]arp edit: " << (this->vp[count].wc.getWarp(0)->isEditing() ? "on" : "off"); */
        /* } */
	/* ofSetColor(ofColor::white); */
	/* ofDrawBitmapStringHighlight(oss.str(), 10, 20); */
    ofSetHexColor(0xffffff);
        /* cout<< "shalalalalalalalalalalalala" << to_string(finder.blobs.size()) << endl; */
    for(int x =0 ; x < finder.blobs.size(); x++){
        ofSetColor(255);
        ofNoFill();
        color.draw(0,0);
        ofDrawRectangle(finder.blobs[x].boundingRect);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
	else if (key == 'a')
	{
		this->areaMode = (this->areaMode + 1) % 3;
		if (this->areaMode == 0)
		{
			// Draw the full image for each warp.
			auto area = ofRectangle(0, 0, this->vp[0].tex.getWidth(), this->vp[0].tex.getHeight());
			for (auto i = 0; i < this->vp[0].wc.getNumWarps(); ++i)
			{
				this->vp[0].srcarea[i] = area;
			}

			this->areaName = "full";
		}
		else if (this->areaMode == 1)
		{			
			// Draw a corner region of the image so that all warps make up the entire image.
			for (auto i = 0; i < this->vp[0].wc.getNumWarps(); ++i)
			{
				static const auto overlap = 10.0f;
				if (i == 0)
				{
					// Top-left.
					this->vp[0].srcarea[i] = ofRectangle(0, 0, this->vp[0].tex.getWidth() * 0.5f + overlap, this->vp[0].tex.getHeight() * 0.5f + overlap);
				}
				else if (i == 1)
				{
					// Top-right.
					this->vp[0].srcarea[i] = ofRectangle(this->vp[0].tex.getWidth() * 0.5f - overlap, 0, this->vp[0].tex.getWidth() * 0.5f + overlap, this->vp[0].tex.getHeight() * 0.5f + overlap);
				}
				else if (i == 2)
				{
					// Bottom-right.
					this->vp[0].srcarea[i] = ofRectangle(this->vp[0].tex.getWidth() * 0.5f - overlap, this->vp[0].tex.getHeight() * 0.5f - overlap, this->vp[0].tex.getWidth() * 0.5f + overlap, this->vp[0].tex.getHeight() * 0.5f + overlap);
				}
				else
				{
					// Bottom-left.
					this->vp[0].srcarea[i] = ofRectangle(0, this->vp[0].tex.getHeight() * 0.5f - overlap, this->vp[0].tex.getWidth() * 0.5f + overlap, this->vp[0].tex.getHeight() * 0.5f + overlap);
				}
			}

			this->areaName = "corners";
		}
		else
		{			
			// Draw a random region of the image for each warp.
			auto x1 = ofRandom(0, this->vp[0].tex.getWidth() - 150);
			auto y1 = ofRandom(0, this->vp[0].tex.getHeight() - 150);
			auto x2 = ofRandom(x1 + 150, this->vp[0].tex.getWidth());
			auto y2 = ofRandom(y1 + 150, this->vp[0].tex.getHeight());
			auto area = ofRectangle(x1, y1, x2 - x1, y2 - y1);
			for (auto i = 0; i < this->vp[0].wc.getNumWarps(); ++i)
			{
				this->vp[0].srcarea[i] = area;
			}

			this->areaName = "random";
		}
	}
	else if (key == 'd')
	{
		this->useBeginEnd ^= 1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
