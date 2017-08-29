//
//  ofxOpenBCI.cpp
//  OpenBCIReceiveExample
//
//  Created by Kento Morita on 2017/08/07.
//
//

#include "ofxOpenBCI.hpp"

ofxOpenBCIReceiver::ofxOpenBCIReceiver() {
    scale = 0.2;
    pos = ofVec2f(0,0);
    size = ofVec2f(ofGetWidth(), ofGetHeight());
    begin = 0;
    end = 60;
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
            // receives 126 values starting from channel num and float continues
            if (m.getArgAsInt(0) == 1) values.clear();
            vector<float> inf;
            for (int i=1; i<m.getNumArgs(); i++) {
                inf.push_back(m.getArgAsFloat(i));
            }
            values.push_back(inf);
        }
        else{
            cout << "unknown: " << m.getNumArgs() << endl;
        }
        
    }
}

void ofxOpenBCIReceiver::drawGraph() {
    ofPushMatrix();
    ofTranslate(pos);
    
    for (int i=0; i<values.size(); i++) {
        ofPolyline p;
        float width = size.x / float(values.at(i).size()-1);
        for (int j=0; j<values.at(i).size(); j++) {
            p.addVertex(j*width, size.y - size.y * log(values.at(i).at(j)+1) * scale);
        }
        p.draw();
    }
    
    ofPopMatrix();
}

void ofxOpenBCIReceiver::drawGraphInRange() {
    ofPushMatrix();
    ofTranslate(pos);
    cout << "size: " << values.size() << endl;
    if (values.size() != 0) {
        cout << ".at(i).size(): " << values.at(0).size() << endl;
    }
    
    for (int i=0; i<values.size(); i++) {
        ofPolyline p;
        float width = float(size.x / end);
        for (int j=begin; j<end; j++) {
            p.addVertex(j*width, size.y - size.y * log(values.at(i).at(j)+1) * scale);
        }
        p.draw();
    }
    
    ofPopMatrix();
}
