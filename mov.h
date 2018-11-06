/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxHapPlayer.h"

#include "sj_common.h"

/************************************************************
************************************************************/
class MOV : Noncopyable{
private:
	/****************************************
	****************************************/
	enum{
		VIDEO_WIDTH = 1280,
		VIDEO_HEIGHT = 720,
	};
	
	enum STATE{
		STATE__OFF,
		STATE__ON,
		STATE__ONtoOFF,
	};
	
	/****************************************
	****************************************/
	STATE State;
	float t_Off;
	
	ofFbo fbo;
	ofxSyphonServer fbo_SyphonServer;
	
	ofxHapPlayer video;
	
	/****************************************
	****************************************/
	void Clear_fbo();
	void draw_to_fbo();
	void setup_video(ofxHapPlayer& video);

	
public:
	/****************************************
	****************************************/
	MOV();
	~MOV();
	
	void setup();
	void update(float _now);
	void draw();
	void publish_syphon();
};

