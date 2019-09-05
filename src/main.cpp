#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    
    ofGLWindowSettings    set;
    set.setSize(1024, 768);
    set.setGLVersion(4, 1);
    set.windowMode = OF_WINDOW;
    
    ofCreateWindow(set);
    
    
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
