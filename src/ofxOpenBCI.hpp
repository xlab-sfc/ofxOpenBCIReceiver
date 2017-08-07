//
//  ofOpenBCI.hpp
//  OpenBCIReceiveExample
//
//  Created by Kento Morita on 2017/08/07.
//
//

#ifndef ofOpenBCI_hpp
#define ofOpenBCI_hpp

#include "ofMain.h"
#include "ofxOsc.h"

#define NUM_MSG_STRINGS 20

class ofxOpenBCIReceiver {
public:
    ofxOpenBCIReceiver();
    void setPort(int _port);
    void update();
    void drawGraph();
    
    
    ofxOscReceiver receiver;
    
    vector<vector<float>> bci;
    array<array<float, 126>, 16> values;
};

#endif /* ofOpenBCI_hpp */
