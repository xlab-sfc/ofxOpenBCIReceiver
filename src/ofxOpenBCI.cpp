//
//  ofOpenBCI.cpp
//  OpenBCIReceiveExample
//
//  Created by Kento Morita on 2017/08/07.
//
//

#include "ofxOpenBCI.hpp"

ofxOpenBCIReceiver::ofxOpenBCIReceiver() {
    
}

void ofxOpenBCIReceiver::setPort(int _port) {
    // listen on the given port
    cout << "listening for osc messages on port " << _port << "\n";
    receiver.setup(_port);
}

void ofxOpenBCIReceiver::update() {
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if (m.getAddress() == "/openbci") {
            vector<float> inf;
            int chan = m.getArgAsInt(0);
            for (int i=1; i<m.getNumArgs(); i++) {
                values.at(chan-1).at(i) = m.getArgAsFloat(i);
            }
        }
        else{
            cout << "unknown: " << m.getNumArgs() << endl;
        }
        
    }
}

void ofxOpenBCIReceiver::drawGraph() {
    for (int i=0; i<16; i++) {
        ofPolyline p;
        float width = float(ofGetWidth() / 125.f);
        for (int j=0; j<126; j++) {
            p.addVertex(j*width, ofGetHeight() - ofGetHeight() * log(values.at(i).at(j)+1)/10);
        }
        p.draw();
    }
}
