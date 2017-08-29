//
//  ofxOpenBCI.hpp
//  OpenBCIReceiveExample
//
//  Created by Kento Morita on 2017/08/07.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define NUM_MSG_STRINGS 20

class ofxOpenBCIReceiver {
public:
    ofxOpenBCIReceiver();
    void setPort(int _port);
    void update();
    void drawGraph();
    void drawGraphInRange();
    
    // SETTERS
    void setScale(float _scale) {scale = _scale;};
    void setPos(ofVec2f _pos) {pos = _pos;};
    void setSize(ofVec2f _size) {size = _size;};
    void setRange(int _begin, int _end) {begin = _begin; end = _end;};
    
    // GETTERS
    vector<vector<float>> getValues() {return values;};
    vector<float> getChannel(int _c) {return values.at(_c);};
    
    void debug();
    
private:
    ofxOscReceiver receiver;
//    array<array<float, 126>, 16> values;
    vector<vector<float>> values;
    
    float scale;
    ofVec2f pos, size;
    int begin, end;
};
