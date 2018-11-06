/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/
/********************
********************/
int GPIO_0 = 0;
int GPIO_1 = 0;

/********************
********************/
GUI_GLOBAL* Gui_Global = NULL;

FILE* fp_Log = NULL;


/************************************************************
class
************************************************************/

/******************************
******************************/
void GUI_GLOBAL::setup(string GuiName, string FileName, float x, float y)
{
	/********************
	********************/
	gui.setup(GuiName.c_str(), FileName.c_str(), x, y);
	
	/********************
	********************/
	/* */
	gui.add(b_VideoCam.setup("0)b_VideoCam", true));
	gui.add(b_SourceCode.setup("1)b_SourceCode", true));
	gui.add(b_mov.setup("2)b_mov", false));
	
	/* */
	{
		ofColor initColor = ofColor(255, 255, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		
		gui.add(gui_VideoColor.setup("VideoColor", initColor, minColor, maxColor));
		gui.add(gui_MovColor.setup("MovColor", initColor, minColor, maxColor));
	}
	
	/********************
	********************/
	gui.minimizeAll();
}

