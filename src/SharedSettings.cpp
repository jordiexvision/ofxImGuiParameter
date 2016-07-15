#include "SharedSettings.h"

SharedSettings::SharedSettings() {

	// Asio and Squash Params
	initParams.setName("init shared settings");
	initParams.add(asioIP.set("asioIP", "127.0.0.1"));
	initParams.add(asioPort.set("asioPort", 4444));
	initParams.add(codecName.set("codecName", "copy"));
	// ParameterSync Params	
	initParams.add(paramSyncIP.set("paramSyncIP", "localhost"));
	initParams.add(paramSyncServerPort.set("paramSyncServerPort", 6667));
	initParams.add(paramSyncClientPort.set("paramSyncClientPort", 6666));

	//-----------
	// syncParams
	syncParams.setName("sync shared settings");
	syncParams.add(imageFrameRate.set("Image Transfer Rate", 1, 1, 1000));

	//-----------
	// tests
	syncParams.add(float_t.set("float test", 0.5f, 0.0f, 1.0f));
	syncParams.add(int_t.set("int test", 1, 1, 1000));
	syncParams.add(bool_t.set("bool test", true));
	syncParams.add(OSD_string_t.set("OSD text", "lorem ipsum", "a", "aaaa"));

	syncParams.add(button_t.set("button test", false));

	string items = "Aaaaaaa/|/bbbbbbbb/|/ccccccc/|/dddddddddd/|/eeeeeeee/|/fffffffff/|/gggggggggggg/|/hhhhhhhh";
//	syncParams.add(Input_string_t.set("Input text field", items));
//	cout << "on SETUP:::: " << Input_string_t.get() << endl;

	syncParams.add(combo_options_t.set("combo_options_t", items));
	syncParams.add(combo_value_t.setCombo("combo", 1));
}
/*
bool SharedSettings::addListeners(* camera) {
	bool success;

	sharedSettings.imageFrameRate.addListener(&camera, &Camera::setImageFramerate);

	return success;
}
*/