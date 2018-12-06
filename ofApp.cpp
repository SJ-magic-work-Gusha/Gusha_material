/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _Cam_id)
: DrawContents(DRAW_CONTENTS__CAM)
, Cam_id(_Cam_id)
, b_DispGui(true)
, b_ShowFrameRate(false)
, VisualizedSourceCode(NULL)
{
	VisualizedSourceCode = new SOURCE_CODE;
}

/******************************
******************************/
ofApp::~ofApp()
{
	if(VisualizedSourceCode) delete VisualizedSourceCode;
}

/******************************
******************************/
void ofApp::exit()
{
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	font.load("font/RictyDiminishedDiscord-Bold.ttf", 15, true, true, true);
	
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("Gusha:material");
	ofSetVerticalSync(true);
	ofSetFrameRate(20);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	setup_Gui();
	
	/********************
	********************/
	VideoCam.setup(Cam_id);
	VisualizedSourceCode->setup();
	mov.setup();
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("Gusha:material", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::update(){
	float now = ofGetElapsedTimef();
	
	VideoCam.update();
	if(VisualizedSourceCode) VisualizedSourceCode->update(now);
	mov.update(now);
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofClear(0, 0, 0, 0);
	
	/********************
	********************/
	switch(DrawContents){
		case DRAW_CONTENTS__CAM:
			VideoCam.draw();
			break;
			
		case DRAW_CONTENTS__SOURCE:
			if(VisualizedSourceCode) VisualizedSourceCode->draw();
			break;
			
		case DRAW_CONTENTS__MOV:
			mov.draw();
			break;
	}
	
	/********************
	********************/
	VideoCam.publish_syphon();
	if(VisualizedSourceCode) VisualizedSourceCode->publish_syphon();
	mov.publish_syphon();
	
	/********************
	********************/
	if(b_DispGui) Gui_Global->gui.draw();
	
	/********************
	********************/
	if(b_ShowFrameRate){
		char buf[BUF_SIZE_S];
		sprintf(buf, "%7.2f", ofGetFrameRate());
		ofSetColor(255, 0, 0, 100);
		font.drawString(buf, ofGetWidth() - font.stringWidth("xxxxxxxxxx"), ofGetHeight() - font.stringHeight("xxxxxxxxxx"));
	}
	
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
			DrawContents = DRAW_CONTENTS__CAM;
			break;
			
		case '1':
			DrawContents = DRAW_CONTENTS__SOURCE;
			break;

		case '2':
			DrawContents = DRAW_CONTENTS__MOV;
			break;

		case 'd':
			b_DispGui = !b_DispGui;
			break;
			
		/********************
		timing次第で、VisualizedSourceCode で、fbo描画が上手くいかない現象が発生。
		temporary対応として、Reset(deleteして新たにnew)を入れた。
		
		SOURCE_CODE::t_LastIntを初期化していないことに起因することが判明.
		Resetは不要なので、コメントアウトしておく。
		********************/
		/*
		case 'r':
			if(VisualizedSourceCode){
				delete VisualizedSourceCode;
				VisualizedSourceCode = new SOURCE_CODE;
				VisualizedSourceCode->setup();
			}
			break;
		*/
			
		case 'f':
			b_ShowFrameRate = !b_ShowFrameRate;
			break;
			
		case 'p':
			mov.SeekToTop();
			break;
			
		case ' ':
			if(GPIO_0 == 0){
				GPIO_0 = 1;
				printf("GPIO on\n");
				fflush(stdout);
			}else{
				GPIO_0 = 0;
				printf("GPIO off\n");
				fflush(stdout);
			}
			break;
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
