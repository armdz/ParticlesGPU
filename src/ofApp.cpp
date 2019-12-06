#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        
    
    gui.setup();
    fps.set("FPS","");
    gui.add(fps);
    
    particles.setup(100000,"Particles");
    gui.add(particles.getParams());
    
    showGui = true;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetFrameNum() == 1)
    {
        gui.loadFromFile("settings.xml");
    }
    
    fps = ofToString(ofGetFrameRate(),2.0);
    
    particles.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    particles.draw();
    if(showGui)
        gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'g'){
        showGui = !showGui;
    }else if(key == 'r')
    {
        particles.reloadShaders();
    }

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
