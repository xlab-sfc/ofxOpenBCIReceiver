#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    receiver.setReceivePort(PORT);
    receiver.setSendPort("localhost", S_PORT);
    
    gui.setup();
    gui.add(log.setup("log values", false));
    gui.add(add.setup("sum all ch", false));
    gui.add(range.setup("in range", false));
    gui.add(send.setup("send osc", false));
//    gui.add(smooth.setup("smooth", false));
    gui.add(printV.setup("print values", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!receiver.hasWaitingMessages()) return;
    receiver.update();
    if (log) receiver.logValues();
    if (add) receiver.addToOneChannel();
    if (range) receiver.trimValues();
    if (send) receiver.sendValues();
//    if (smooth) receiver.smoothOut();
    if (printV) receiver.printAllReceivedValues();
}

//--------------------------------------------------------------
void ofApp::draw(){
    receiver.drawRawGraph();
    
    string wtitle = "";
    if (receiver.isReceiving()) wtitle += "d -- ";
    wtitle += "receive: " + ofToString(PORT);
    wtitle += " send: " + ofToString(S_PORT);
    ofSetWindowTitle(wtitle);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
