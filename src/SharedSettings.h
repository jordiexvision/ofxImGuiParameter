#pragma once
#include "ofMain.h"
#include "ofxImGuiParameter.h"
#include "ofxImGuiParameterCombo.h"
#include "ofxOscParameterSync.h"
#include "GuiShellTheme.h"

class SharedSettings {

public:

	// Asio and Squash Params
	ofParameter<string>		asioIP;
	ofParameter<int>		asioPort;
	ofParameter<string>		codecName;
	// ParameterSync Params	
	ofParameter<string>		paramSyncIP;
	ofParameter<int>		paramSyncServerPort;
	ofParameter<int>		paramSyncClientPort;

	ofxImGuiParameter<int>		imageFrameRate;

	//tests
	ofxImGuiParameter<float>	float_t;
	ofxImGuiParameter<int>		int_t;
	ofxImGuiParameter<float>	float_t1;
	ofxImGuiParameter<int>		int_t1;

	ofxImGuiParameter<bool>		bool_t;
	ofxImGuiParameter<string>	OSD_string_t;
	ofxImGuiParameter<string>	OSD_string_t2;
	ofxImGuiParameter<string>	OSD_string_t3;
	ofxImGuiParameter<string>	Input_string_t;
	ofxImGuiParameter<bool>		button_t;
	ofxImGuiParameter<bool>		collapsingHeader_t;

//	ofxImGuiParameter<int>		combo_value_t;
//	ofxImGuiParameter<string>	combo_options_t;

	ofxImGuiParameter<string>	combo_options_t;
	ofxImGuiParameterCombo	combo_value_t = ofxImGuiParameterCombo(combo_options_t);

	ofxImGuiParameter<bool>		bCameraInfo;
	ofxImGuiParameter<string>	cameraInfoString;

	ofxImGuiParameter<int>		testResend;

	ofParameterGroup	syncParams;
	ofParameterGroup	initParams;

	SharedSettings();

	void setupServer();
	void setupClient();
	void update();
	void draw();
	void load();
	void save();

private:
	ofJson json;
	ofxImGui gui;
	ofxOscParameterSync sync;

	bool 	show_test_window = false;
	bool	show_another_window = false;

//	bool addListeners(*camera);

};