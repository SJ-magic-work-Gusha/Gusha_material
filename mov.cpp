/************************************************************
************************************************************/
#include "mov.h"

/************************************************************
************************************************************/

/******************************
******************************/
MOV::MOV()
: State(STATE__OFF)
, t_Off(0)
{
}

/******************************
******************************/
MOV::~MOV()
{
}

/******************************
******************************/
void MOV::Clear_fbo()
{
	fbo.begin();
	
	// Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ofClear(0, 0, 0, 0);
	
	fbo.end();
}

/******************************
******************************/
void MOV::setup()
{
	/********************
	********************/
	fbo.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_RGBA, 0);
	Clear_fbo();
	
	fbo_SyphonServer.setName("Gusha_material_mov");
	
	/********************
	********************/
	if(video.load("mov/mov.mov")){
		setup_video(video);
	}else{
		printf("> No mov file.\n");
		fflush(stdout);
	}
}

/******************************
******************************/
void MOV::setup_video(ofxHapPlayer& video)
{	
	if(video.isLoaded()){
		video.setLoopState(OF_LOOP_NORMAL);
		// video.setLoopState(OF_LOOP_PALINDROME);
		
		video.setSpeed(1);
		video.setVolume(0.0);
		video.play();
	}
}

/******************************
******************************/
void MOV::update(float _now)
{
	if(Gui_Global->b_mov && video.isLoaded()){
		video.update();
		if(video.isFrameNew()){
			draw_to_fbo();
		}
	}else{
		Clear_fbo();
	}
	
	switch(State){
		case STATE__OFF:
			if(Gui_Global->b_mov){
				State = STATE__ON;
			}
			break;
			
		case STATE__ON:
			if(!Gui_Global->b_mov){
				State = STATE__ONtoOFF;
				t_Off = _now;
			}
			break;
			
		case STATE__ONtoOFF:
			if(Gui_Global->b_mov){
				State = STATE__ON;
			}else if(1.0 < _now - t_Off){
				State = STATE__OFF;
			}
			break;
	}
}

/******************************
******************************/
void MOV::publish_syphon()
{
	/*
	c_syphon++;
	if(c_syphon % 2 == 0){
		c_syphon = 0;
		return;
	}
	*/
	
	if( (State == STATE__ON) || (State == STATE__ONtoOFF) ){
		ofTexture tex = fbo.getTextureReference();
		fbo_SyphonServer.publishTexture(&tex);
	}
}

/******************************
******************************/
void MOV::draw_to_fbo()
{
	if(!video.isLoaded()) return;
	
	fbo.begin();
		/********************
		********************/
		// Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ofClear(0, 0, 0, 0);
		
		/********************
		********************/
		ofColor BaseColor = Gui_Global->gui_MovColor;
		ofSetColor(BaseColor);
		// ofSetColor(255, 255, 255, 255);
		
		video.draw(0, 0, fbo.getWidth(), fbo.getHeight());
	fbo.end();
}

/******************************
******************************/
void MOV::draw()
{
	ofSetColor(255, 255, 255, 255);
	fbo.draw(0, 0, fbo.getWidth(), fbo.getHeight());
}

