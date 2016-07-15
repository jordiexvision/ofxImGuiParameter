#pragma once
#include "ofMain.h"
#include "ofxOscParameterSync.h"
#include "ofxImGuiParameter.h"

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
	ofxImGuiParameter<string>	Input_string_t;
	ofxImGuiParameter<bool>		button_t;

//	ofxImGuiParameter<int>		combo_value_t;
//	ofxImGuiParameter<string>	combo_options_t;

	ofxImGuiParameter<string>	combo_options_t;
	ofxImGuiofParameterCombo combo_value_t = ofxImGuiofParameterCombo(combo_options_t);

	ofParameterGroup	syncParams;
	ofParameterGroup	initParams;

	SharedSettings();

//	bool addListeners(*camera);

};