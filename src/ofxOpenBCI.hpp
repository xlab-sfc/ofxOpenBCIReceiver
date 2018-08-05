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

class ofxOpenBCIReceiver {
public:
    ofxOpenBCIReceiver();
    void setReceivePort(int _port);
    void setSendPort(std::string _host, int _port);
    void update();
    void drawRawGraph();
    void drawRawGraphInRange();
    void drawGraph();
    void drawGraphInRange();
    void drawSmoothGraph();
    void printAllReceivedValues();
    void sendValues();
    
    // DATA FILTERING
    void addToOneChannel();
    void logValues();
    void trimValues();
    void smoothOut();
    float getMaxInValues() const;
    std::vector<float> getSum(const std::vector<std::vector<float>> &_in, bool _divide) const;
    
    // SETTERS
    void setScale(float _scale) {scale = _scale;};
    void setPos(ofVec2f _pos) {pos = _pos;};
    void setSize(ofVec2f _size) {size = _size;};
    void setRange(int _begin, int _end) {begin = _begin; end = _end;};
    
    // GETTERS
    bool isReceiving() const {return receivedData;};
    bool hasWaitingMessages() {return receiver.hasWaitingMessages();};
    const std::vector<std::vector<float>> &getValues() const {return values;};
    const std::vector<float> &getChannel(int _c) const {return values.at(_c);};
    
    void debug();
    
private:
    ofxOscReceiver receiver;
    ofxOscSender sender;
    std::vector<std::vector<float>> values;
    std::vector<std::vector<float>> svalues;
    std::vector<std::vector<std::vector<float>>> pvalues;
    int pastValues = 5;
    
    float scale;
    ofVec2f pos, size;
    int begin, end;
    bool receivedData;
};
