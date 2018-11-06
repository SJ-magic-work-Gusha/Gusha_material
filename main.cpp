#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	
	if(argc < 2){
		printf("exe [CamId]\n");
		
		int Cam_id = -1;
		ofRunApp(new ofApp(Cam_id));
		
	}else{
		int Cam_id = atoi(argv[1]);
		if(Cam_id < 0) Cam_id = 0;
		
		ofRunApp(new ofApp(Cam_id));
	}

}
