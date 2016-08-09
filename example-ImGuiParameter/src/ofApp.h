#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
//#include "ThemeTest.h"
//#include "BaseTheme.h"

#include "ofxOscParameterSync.h"

#include "SharedSettings.h"
#include "GuiShellTheme.h"
#include "Camera.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
	void addListeners();
	void removeListeners();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(float x, float y);
    
    ofxImGui gui;
	SharedSettings sharedSettings;
	ofxOscParameterSync sync;

	Camera camera;

	bool 	show_test_window = false;
	bool	show_another_window = false;

};


/*
sharedSettings.float_t.drawSliderFloat();
sharedSettings.int_t.drawSliderInt();
sharedSettings.float_t1.drawSliderFloat();
sharedSettings.int_t1.drawSliderInt();
sharedSettings.bool_t.drawCheckbox();
sharedSettings.button_t.drawButton();
sharedSettings.OSD_string_t.drawTextWrapped();
sharedSettings.Input_string_t.drawInputText();
//	sharedSettings.Input_string_t.drawInputTextMultiline();

if (sharedSettings.collapsingHeader_t.drawCollapsingHeader()) {
sharedSettings.combo_options_t.drawInputText();
sharedSettings.combo_value_t.drawCombo();
}
*/

//////////////////////////////
// Image framerate
//////////////////////////////
/*
{
// check changes in shared settings
if (sharedSettings.imageFrameRate != camera.getImageFramerate()) {
ofLogNotice() << "Client changed imageFrameRate";
// apply changes to registered method
bool result = camera.check_setImageFramerate(sharedSettings.imageFrameRate);
// if registered method succeds to apply, update local var
if (result) camera.getImageFramerate() = sharedSettings.imageFrameRate;
}
// label
ImGui::Text(sharedSettings.imageFrameRate.getName().c_str());
// slider
ImGui::PushItemWidth(sliderWidth);
ImGui::SliderInt("##v2", &camera.getImageFramerate(), sharedSettings.imageFrameRate.getMin(), sharedSettings.imageFrameRate.getMax(), "");
ImGui::PopItemWidth();
ImGui::SameLine();
// input field
ImGui::PushItemWidth(inputIntWidth);
ImGui::InputInt("##i2", &camera.getImageFramerate());
ImGui::PopItemWidth();

// check user interaction
if (sharedSettings.imageFrameRate != camera.getImageFramerate()) {
// clamp user input to param limits
camera.getImageFramerate() = MAX(camera.getImageFramerate(), sharedSettings.imageFrameRate.getMin());
camera.getImageFramerate() = MIN(camera.getImageFramerate(), sharedSettings.imageFrameRate.getMax());
// apply changes to registered method
bool result = camera.check_setImageFramerate(camera.getImageFramerate());
// if registered method succeds to apply, update local var
if (result) sharedSettings.imageFrameRate = camera.getImageFramerate();
}
}

// label
ImGui::Text(sharedSettings.imageFrameRate.getName().c_str());
// slider
ImGui::PushItemWidth(sliderWidth);
ImGui::SliderInt(sharedSettings.imageFrameRate.getName().c_str(),
&sharedSettings.imageFrameRate.value,
sharedSettings.imageFrameRate.getMin(),
sharedSettings.imageFrameRate.getMax());
//	ImGui::SliderInt("##v2", &camera.getImageFramerate(), sharedSettings.imageFrameRate.getMin(), sharedSettings.imageFrameRate.getMax(), "");
ImGui::PopItemWidth();
ImGui::SameLine();
// input field
ImGui::PushItemWidth(inputIntWidth);
//	ImGui::InputInt("##i2", sharedSettings.imageFrameRate);
ImGui::PopItemWidth();


// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
if (show_test_window)
{
ImGui::SetNextWindowPos(ofVec2f(650, 20), ImGuiSetCond_FirstUseEver);
ImGui::ShowTestWindow(&show_test_window);
}
*/