#include "ofApp.h"
#include "ofxPowerMate.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void ofApp::setup(){
	// we don't want to be running to fast
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    //create the socket and set to send to 127.0.0.1:11999
	udpConnection.Create();
	udpConnection.Connect("255.255.255.255",11999);
    udpConnection.SetEnableBroadcast(true);
	udpConnection.SetNonBlocking(true);
    
    position = 0;
    
    pm.conecta();
    pm.setBrillo(255);
    ofAddListener(pm.tengoInfo, this, &ofApp::pow);

}

//--------------------------------------------------------------
void ofApp::pow(powerData& data){
    ofLog() << ofToString(data.direccion) + ", " + ofToString(data.presionado);
    
    position = ofClamp(position + data.direccion, 0, 255);
    pm.setBrillo(position);
    
    string message="turn: " + ofToString(position);
    
    udpConnection.Send(message.c_str(),message.length());
}

//--------------------------------------------------------------
void ofApp::update(){
//    pm.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(100,100,100);
    ofRect(0, 0, position, 100);
    
	ofSetColor(20, 20, 20);
	ofDrawBitmapString("openFrameworks UDP Send Example ", 15, 30);
    ofDrawBitmapString("drag to draw", 15, 50);
	for(unsigned int i=1;i<stroke.size();i++){
		ofLine(stroke[i-1].x,stroke[i-1].y,stroke[i].x,stroke[i].y);
	}


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
	stroke.push_back(ofPoint(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	stroke.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	string message="";
	for(unsigned int i=0; i<stroke.size(); i++){
		message+=ofToString(stroke[i].x)+"|"+ofToString(stroke[i].y)+"[/p]";
	}
	udpConnection.Send(message.c_str(),message.length());
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
