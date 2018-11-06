/************************************************************
************************************************************/
#include "VideoCam.h"

/************************************************************
************************************************************/

/******************************
******************************/
SJ_VIDEO_CAM::SJ_VIDEO_CAM()
: VideoCam(NULL)
, c_syphon(0)
{
}

/******************************
******************************/
SJ_VIDEO_CAM::~SJ_VIDEO_CAM()
{
	if(VideoCam) delete VideoCam;
}

/******************************
******************************/
void SJ_VIDEO_CAM::setup(int _Cam_id)
{
	/********************
	********************/
	VideoCam = new ofVideoGrabber;
	
	ofSetLogLevel(OF_LOG_VERBOSE);
    VideoCam->setVerbose(true);
	
	vector< ofVideoDevice > Devices = VideoCam->listDevices();// 上 2行がないと、List表示されない.
	
	if(_Cam_id == -1){
		std::exit(1);
	}else{
		if(Devices.size() <= _Cam_id) { ERROR_MSG(); std::exit(1); }
		
		VideoCam->setDeviceID(_Cam_id);
		VideoCam->initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT);
	}

	/********************
	********************/
	fbo.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_RGBA, 0);
	Clear_fbo();
	
	fbo_SyphonServer.setName("Gusha_material_VideoCam");
	
}

/******************************
******************************/
void SJ_VIDEO_CAM::Clear_fbo()
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
void SJ_VIDEO_CAM::update()
{
	if(Gui_Global->b_VideoCam){
		VideoCam->update();
		if(VideoCam->isFrameNew()){
			draw_to_fbo();
		}
	}else{
		Clear_fbo();
	}
}

/******************************
******************************/
void SJ_VIDEO_CAM::publish_syphon()
{
	/*
	c_syphon++;
	if(c_syphon % 2 == 0){
		c_syphon = 0;
		return;
	}
	*/
	
	ofTexture tex = fbo.getTextureReference();
	fbo_SyphonServer.publishTexture(&tex);
}

/******************************
******************************/
void SJ_VIDEO_CAM::draw_to_fbo()
{
	fbo.begin();
		/********************
		********************/
		// Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ofClear(0, 0, 0, 0);
		
		/********************
		********************/
		ofColor BaseColor = Gui_Global->gui_VideoColor;
		ofSetColor(BaseColor);
		// ofSetColor(255, 255, 255, 255);
		
		VideoCam->draw(0, 0, fbo.getWidth(), fbo.getHeight());
	fbo.end();
}

/******************************
******************************/
void SJ_VIDEO_CAM::draw()
{
	ofSetColor(255, 255, 255, 255);
	fbo.draw(0, 0, fbo.getWidth(), fbo.getHeight());
}
