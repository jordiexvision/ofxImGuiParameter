#pragma once
#include "ofMain.h"
#include "ofxOscParameterSync.h"
#include "ImGuiTheme.h"

#include "ofxImGuiParameter.h"
#include "ofxImGuiParameterCombo.h"
#include "ofxImGuiParameterListbox.h"

class SharedSettings {

public:

	// ParameterSync Params	
	ofParameter<string>		paramSyncIP;
	ofParameter<int>		paramSyncServerPort;
	ofParameter<int>		paramSyncClientPort;

	// Basic types
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

	// Headers
	ofxImGuiParameter<string>	collapsingHeaderString;
	ofxImGuiParameter<bool>		collapsingHeader_t;
	ofxImGuiParameter<bool>		bResend;

	// Combos
	ofxImGuiParameter<string>	combo_options_t;
	ofxImGuiParameterCombo		combo_value_t = ofxImGuiParameterCombo(combo_options_t);
	//ListBox
	ofxImGuiParameter<string>	listbox_options_t;
	ofxImGuiParameterListbox	listbox_value_t = ofxImGuiParameterListbox(listbox_options_t);

	// PopUps
	ofxImGuiParameter<bool>		popUp_1;
	ofxImGuiParameter<bool>		popUp_2;

	// Resend
	ofxImGuiParameter<int>		testResend;
	ofxImGuiParameter<string>	comboResend_options_t;
	ofxImGuiParameterCombo		comboResend_value_t = ofxImGuiParameterCombo(comboResend_options_t);
	ofxImGuiParameter<string>	listboxResend_options_t;
	ofxImGuiParameterListbox	listboxResend_value_t = ofxImGuiParameterListbox(listboxResend_options_t);



	ofParameterGroup	syncParams_b;
	ofParameterGroup	syncParams;
	ofParameterGroup	initParams;


	SharedSettings();

	void setupServer();
	void setupClient();
	void update();
	void draw();
	void load();
	void save();


	//text files
	ofBuffer credits;
	ofBuffer shortcuts;
	void loadTextFile(string loadPath, ofBuffer& buff);

private:
	ofJson json;
	ofxImGui gui;
	ofxOscParameterSync sync;

	bool 	show_test_window = false;
	bool	show_another_window = false;

//	bool addListeners(*camera);

};