//
//  ofxOpenBCI.cpp
//  OpenBCIReceiveExample
//
//  Created by Kento Morita on 2017/08/07.
//
//

#include "ofxOpenBCI.hpp"

using namespace std;

ofxOpenBCIReceiver::ofxOpenBCIReceiver() {
    scale = 0.2;
    pos = ofVec2f(0,0);
    size = ofVec2f(ofGetWidth(), ofGetHeight());
    begin = 0;
    end = 60;
}

void ofxOpenBCIReceiver::setReceivePort(int _port) {
    // listen on the given port
    cout << "listening for osc messages on port " << _port << "\n";
    receiver.setup(_port);
}

void ofxOpenBCIReceiver::setSendPort(string _host, int _port) {
    // send on the given port
    cout << "sending osc message on port " << _port << endl;
    sender.setup(_host, _port);
}

void ofxOpenBCIReceiver::update() {
    receivedData = false;
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
//        cout << "size: " << m.getNumArgs() << endl;
        
        if (m.getAddress() == "/openbci") {
            receivedData = true;
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

void ofxOpenBCIReceiver::drawRawGraph() {
    if (values.size() == 0) return;
    ofPushMatrix();
    ofTranslate(pos);
    
    float max = 1;
    for (int i=0; i<values.size(); i++) {
        ofPolyline p;
        float width = size.x / float(values.at(i).size()-1);
        for (int j=0; j<values.at(i).size(); j++) {
            p.addVertex(j*width, size.y - size.y * (values.at(i).at(j) / max) * scale);
        }
        p.draw();
    }
    
    ofPopMatrix();
}

void ofxOpenBCIReceiver::drawRawGraphInRange() {
    if (values.size() == 0) return;
    ofPushMatrix();
    ofTranslate(pos);
    
    float max = 1;
    for (int i=0; i<values.size(); i++) {
        ofPolyline p;
        float width = size.x / end;
        for (int j=begin; j<end; j++) {
            p.addVertex(j*width, size.y - size.y * (values.at(i).at(j) / max) * scale);
        }
        p.draw();
    }
    
    ofPopMatrix();
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

void ofxOpenBCIReceiver::drawSmoothGraph() {
    if (svalues.size() == 0) return;
    ofPushMatrix();
    ofTranslate(pos);
    
    for (int i=0; i<values.size(); i++) {
        ofPolyline p;
        float width = size.x / float(values.at(i).size()-1);
        for (int j=0; j<values.at(i).size(); j++) {
            p.addVertex(j*width, size.y - size.y * log(svalues.at(i).at(j)+1) * scale);
        }
        p.draw();
    }
    
    ofPopMatrix();
}

void ofxOpenBCIReceiver::drawGraphInRange() {
    ofPushMatrix();
    ofTranslate(pos);
    
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

void ofxOpenBCIReceiver::printAllReceivedValues() {
    if (!receivedData) return;
    if (values.size() == 0) {
        cout << "values has no values" << endl;
        return;
    }
    
    for (int i=0; i<values.size(); i++) {
        cout << i << ": ";
        for (int j=0; j<values.at(i).size(); j++) {
            cout << values.at(i).at(j) << ", ";
        }
        cout << "__END__" << endl;
    }
}

void ofxOpenBCIReceiver::sendValues() {
    for (int ch = 0; ch < values.size(); ch++) {
        ofxOscMessage m;
        m.setAddress("/output");
        for (int val = 0; val < values.at(ch).size(); val++) {
            m.addFloatArg(values.at(ch).at(val));
        }
        sender.sendMessage(m);
    }
}

// DATA FILTERING

void ofxOpenBCIReceiver::addToOneChannel() {
    if (values.size() == 0) return;
    vector<float> sum;
    sum = getSum(values, true);
    values.clear();
    values.push_back(sum);
}

void ofxOpenBCIReceiver::logValues() {
    for (int i=0; i<values.size(); i++) {
        for (int j=0; j<values.at(i).size(); j++) {
            values.at(i).at(j) = log(values.at(i).at(j)+1);
        }
    }
}

void ofxOpenBCIReceiver::trimValues() {
    vector<vector<float>> trimmed;
    for (int i=0; i<values.size(); i++) {
        vector<float> _v;
        for (int j=begin; j<end; j++) {
            _v.push_back(values.at(i).at(j));
        }
        trimmed.push_back(_v);
    }
    values.clear();
    values = trimmed;
}

// wip: do not use
void ofxOpenBCIReceiver::smoothOut() {
//    pvalues.resize(_num);
    if (values.size() == 0) return;
    while (pvalues.size() > pastValues) {
        pvalues.erase(pvalues.begin());
    }
    pvalues.push_back(values);
    if (pvalues.size() < 2) return;
    vector<vector<float>> sum;
    sum = values;
    for (int frame = 0; frame < pvalues.size()-1; frame++) {
        for (int ch = 0; ch < pvalues.at(frame).size(); ch++) {
            for (int val = 0; val < pvalues.at(frame).at(ch).size(); val++) {
                sum.at(ch).at(val) += pvalues.at(frame).at(ch).at(val);
            }
        }
    }
    
    for (int frame = 0; frame < pvalues.size(); frame++) {
        for (int ch = 0; ch < pvalues.at(frame).size(); ch++) {
            for (int val = 0; val < pvalues.at(frame).at(ch).size(); val++) {
                sum.at(ch).at(val) /= pastValues;
            }
        }
    }
    
    svalues = sum;
}

float ofxOpenBCIReceiver::getMaxInValues() const {
    float max = 0;
    for (int i=0; i<values.size(); i++) {
        float _max = *max_element(values.at(i).begin(), values.at(i).end());
        if (max < _max) max = _max;
    }
    return max;
}

vector<float> ofxOpenBCIReceiver::getSum(const vector<vector<float>> &_in, bool _divide) const {
    if (_in.size() == 0) return {};
    float divideby = _in.size();
    vector<float> sum;
    sum.resize(_in.at(0).size());
    for (int i=0; i<sum.size(); i++) {
        for (int j=0; j<_in.size(); j++) {
            sum.at(i) += _in.at(j).at(i);
        }
    }
    if (!_divide) return sum;
    for (int i=0; i<sum.size(); i++) {
        sum.at(i) /= divideby;
    }
    return sum;
}
