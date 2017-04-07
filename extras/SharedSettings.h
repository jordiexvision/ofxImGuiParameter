#pragma once
#include "ofMain.h"
#include "ofxOscParameterSync.h"
#include "ImGuiTheme.h"

#include "ofxImGuiParameter.h"
#include "ofxImGuiWidgets.h"

class SharedSettings {

public:

	// ParameterSync Params	
	ofParameter<string>		paramSyncIP;
	ofParameter<int>		paramSyncServerPort;
	ofParameter<int>		paramSyncClientPort;

	// Basic types
	SliderFloat					float_t;
	SliderInt					int_t;
	SliderFloat					float_t1;
	SliderInt					int_t1;

	CheckBox					bool_t;
	TextWrapped					OSD_string_t;
	TextWrapped					OSD_string_t2;
	TextWrapped					OSD_string_t3;
	TextWrapped					Input_string_t;
	Button						button_t;

	// Headers
	ofxImGuiParameter<string>	collapsingHeaderString;
	CollapsingHeader			collapsingHeader_t;
	CollapsingHeader			bResend;

	// Combos
	ofxImGuiParameter<string>	combo_options_t;
	Combo						combo_value_t = Combo(combo_options_t);

	//ListBox
	ofxImGuiParameter<string>	listbox_options_t;
	ListBox	listbox_value_t = ListBox(listbox_options_t);

	// PopUps
	Popup						popUp_1;
	Popup						popUp_2;

	// Resend
	SliderInt					testResend;
	ofxImGuiParameter<string>	comboResend_options_t;
	Combo						comboResend_value_t = Combo(comboResend_options_t);
	ofxImGuiParameter<string>	listboxResend_options_t;
	ListBox	listboxResend_value_t = ListBox(listboxResend_options_t);

	ofParameterGroup			syncParams_b;
	ofParameterGroup			syncParams;
	ofParameterGroup			initParams;


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