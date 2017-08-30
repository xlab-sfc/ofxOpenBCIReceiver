#pragma once

#include "ofMain.h"
#include "ofxOpenBCI.hpp"
#include "ofxGui.h"

// listen on port 12345
#define PORT 12345
#define S_PORT 8887

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
		
    ofxOpenBCIReceiver receiver;
    
    ofxPanel gui;
    ofxToggle log, add, smooth, range, send, printV;
};
