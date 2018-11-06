/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

#include "sj_common.h"
#include "VideoCam.h"
#include "SourceCode.h"
#include "mov.h"


/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum DRAW_CONTENTS{
		DRAW_CONTENTS__CAM,
		DRAW_CONTENTS__SOURCE,
		DRAW_CONTENTS__MOV,
	};
	
	DRAW_CONTENTS DrawContents;
	
	SJ_VIDEO_CAM VideoCam;
	int Cam_id;
	
	SOURCE_CODE* VisualizedSourceCode;
	
	MOV mov;
	
	bool b_DispGui;
	bool b_ShowFrameRate;
	
	ofTrueTypeFont font;
	
	/****************************************
	****************************************/
	void setup_Gui();
	
public:
	/****************************************
	****************************************/
	ofApp(int _Cam_id);
	~ofApp();
	
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
