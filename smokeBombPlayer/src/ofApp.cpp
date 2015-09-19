#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
    
    ofDirectory dir("./img");
    dir.allowExt("jpg");
    dir.listDir();
    dir.sort();
    
    currentFrame = 0;
    numFrames =  dir.numFiles();
    
    pixels.resize(numFrames);
    
    ofImage img;
    
    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++){
        ofLogNotice(dir.getPath(i));
        img.loadImage(dir.getPath(i));
        pixels[i].setFromPixels(img.getPixels(), img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);
    }
    
    
    udpConnection.Create();
    udpConnection.Bind(11999);
    udpConnection.SetNonBlocking(true);
}

bool hasChanged = true;

//--------------------------------------------------------------
void ofApp::update(){
    if(hasChanged)
        img.setFromPixels(pixels[currentFrame]);
    
    hasChanged = false;
    
    char udpMessage[255];
    udpConnection.Receive(udpMessage,255);
    string message=udpMessage;
    if(message!=""){
        ofLog() << "message: " + message;
        if(message.substr(0,6) == "turn: "){
            ofLog() << "TURNING: " << message.substr(6, 10);
            currentFrame = ofClamp(ofToInt(message.substr(6, 10)), 0, numFrames);
            hasChanged = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);
    img.draw(0,0, ofGetWidth(), ofGetHeight());
    
    ofSetHexColor(0x000000);
    ofDrawBitmapString("frame: " + ofToString(currentFrame),20,80);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch(key){
        case OF_KEY_LEFT:
            currentFrame++;
            break;
        case OF_KEY_RIGHT:
            currentFrame--;
            break;
    }
    
    ofLog() << "key: " + ofToString( currentFrame );
    hasChanged = true;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    int width = ofGetWidth();
    float pct = (float)x / (float)width;
    
    currentFrame = numFrames * pct;
    
    ofLog() << "mouse: " + ofToString( currentFrame );
    hasChanged = true;
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
