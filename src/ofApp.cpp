#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	ofBackground(30, 30, 130);
}

//--------------------------------------------------------------
void ofApp::update(){
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
        
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        
        if (m.getAddress() == "/openbci") {
            
            if (m.getArgAsInt(0) == 1) bci.clear();
            vector<float> inf;
//            int chan = m.getArgAsInt(0);
            for (int i=1; i<m.getNumArgs(); i++) {
                inf.push_back(m.getArgAsFloat(i));
//                values.at(chan).at(i) = m.getArgAsFloat(i);
            }
            bci.push_back(inf);
        }
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
            cout << msg_string << endl;
		}

	}
}


//--------------------------------------------------------------
void ofApp::draw(){

	string buf;
	buf = "listening for osc messages on port " + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

    for (int i=0; i<bci.size(); i++) {
        ofPolyline p;
        float width = float(ofGetWidth() / bci.at(i).size());
        for (int j=0; j<bci.at(i).size(); j++) {
            p.addVertex(j*width, ofGetHeight() - ofGetHeight() * log(bci.at(i).at(j)+1)/5);
//            p.addVertex(j*width, ofGetHeight()/2 - ofGetHeight() * log(bci.at(i).at(j))/10);
//            cout << bci.at(i).at(j)<< ", ";
        }
        p.draw();
    }
//    for (int i=0; i<16; i++) {
//        ofPolyline p;
//        float width = float(ofGetWidth() / 125.f);
//        for (int j=0; j<126; j++) {
//            //            p.addVertex(j*width, ofGetHeight() - ofGetHeight() * log(bci.at(i).at(j) + 1)/10);
//            p.addVertex(j*width, ofGetHeight()/2 - ofGetHeight() * log(values.at(i).at(j))/10);
//            //            cout << bci.at(i).at(j)<< ", ";
//        }
//        p.draw();
//    }

//    cout << bci.size() << ": ";
//    if (bci.size() != 0) {
//        for (int i=0; i<bci.size(); i++) {
//            cout << bci.at(i).size() << ", ";
//        }
//    }
//    cout << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
