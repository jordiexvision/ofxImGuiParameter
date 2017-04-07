#include "SharedSettings.h"

SharedSettings::SharedSettings(){

	// ParameterSync Params	
	initParams.add(paramSyncIP.set("paramSyncIP", "localhost"));
	initParams.add(paramSyncServerPort.set("paramSyncServerPort", 6667));
	initParams.add(paramSyncClientPort.set("paramSyncClientPort", 6666));

	//-----------
	// syncParams
	syncParams.setName("sync shared settings");

	//-----------
	// tests
	syncParams.add(float_t.set("Float test1", 0.5f, 0.0f, 1.0f));
	syncParams.add(int_t.set("Int test1", 1, 1, 1000));
	syncParams_b.add(float_t1.set("Float test2", 0.2f, 0.0f, 1.0f));
	syncParams_b.add(int_t1.set("Int test2", 1234, 1, 1000));

	syncParams.add(bool_t.set("bool test", true));
	syncParams.add(OSD_string_t.set("OSD text1", "Check values on Server and resend to Client. Check values on Server and resend to Client. Check values on Server and resend to Client. "));
	syncParams.add(OSD_string_t2.set("OSD text2", "Lorem ipsum2"));
	syncParams.add(OSD_string_t3.set("OSD text3", "Lorem ipsum3"));

	syncParams.add(button_t.set("button test", false));
	syncParams.add(Input_string_t.set("Input text field", "try to edit string"));
	syncParams.add(collapsingHeader_t.set("Collapsing Header Sample", true));

	// Combos
	string items = "Aaaaaaa||bbbbbbbb||ccccccc||dddddddddd||eeeeeeee||fffffffff||gggggggggggg||hhhhhhhh";
	syncParams.add(combo_options_t.set("combo options 1", items));
	syncParams.add(combo_value_t.setOptions("combo value 1", 1));
	//ListBox
	// we are forced to use only 4 items. non modifiable!
	string items2 = "Aaaaaaa||bbbbbbbb||ccccccc||dddddddddd";
	syncParams.add(listbox_options_t.set("listBox options 1", items2));
	syncParams.add(listbox_value_t.setOptions("listBox value 1", ofVec4f(1, 0, 0, 0)));
	// Headers
	syncParams.add(bResend.set("Check values on Server and resend to Client", false));
	syncParams.add(collapsingHeaderString.set("Update String on header open", "Unknown"));
	// PopUps
	syncParams.add(popUp_1.set("popUp_1", false));
	syncParams.add(popUp_2.set("popUp_2", false));
	// Resend
	syncParams.add(testResend.set("add 5 on server", 1, 1, 1000));
	syncParams.add(comboResend_options_t.set("combo options 2", items));
	syncParams.add(comboResend_value_t.setOptions("combo value 2", 1));
	syncParams.add(listboxResend_options_t.set("listBoxResend options 2", items2));
	syncParams.add(listboxResend_value_t.setOptions("Force active: min 1, max 2", ofVec4f(1, 0, 0, 0)));

	syncParams.add(syncParams_b);

	loadTextFile(ofToDataPath("textFiles/credits.txt", true), credits);
	loadTextFile(ofToDataPath("textFiles/shortcuts.txt", true), shortcuts);

	//	needsUpdate = false;
}

//--------------------------------------------------------------
void SharedSettings::loadTextFile(string loadPath, ofBuffer& buff)
{
	ofFile file(ofToDataPath(loadPath));

	if (!file.exists()) {
		ofLogError("The file " + loadPath + " is missing");
		buff.set("file not found");
	}
	buff.set(file);
}

//--------------------------------------------------------------
void SharedSettings::setupServer(){
	sync.setup((ofParameterGroup&)syncParams,
		paramSyncServerPort,
		paramSyncIP,
		paramSyncClientPort);

	gui.setup(new ImGuiTheme());
	show_test_window = true;
}

//--------------------------------------------------------------
void SharedSettings::setupClient() {
	sync.setup((ofParameterGroup&)syncParams,
		paramSyncClientPort,
		paramSyncIP,
		paramSyncServerPort);

	gui.setup(new ImGuiTheme());
	show_test_window = true;
}

//--------------------------------------------------------------
void SharedSettings::update(){
	sync.update();
}
//--------------------------------------------------------------
void SharedSettings::draw(){

	gui.begin();
	
	if (ImGui::CollapsingHeader("Basic types", false)) {
		float_t.draw();
		int_t.draw();
		float_t1.draw();
		int_t1.draw();
		bool_t.draw();
		button_t.draw();
		button_t.draw();

		OSD_string_t.draw();
		OSD_string_t.draw();
		OSD_string_t2.draw();
		OSD_string_t3.draw();

		Input_string_t.draw();
		//	sharedSettings.Input_string_t.drawInputTextMultiline();

		combo_options_t.draw();
		combo_value_t.draw();
		listbox_value_t.drawListbox();
	}

	if (collapsingHeader_t.draw()) {

		collapsingHeaderString.draw();

		popUp_1.drawPopUp(credits);
		popUp_2.drawPopUp(shortcuts, 400, 300);

		// this will not update the client
		//if (sharedSettings.bCameraInfo.hasChanged()) {
		//	cout << "#################### has changed on draw" << endl;
		//	sharedSettings.cameraInfoString = sharedSettings.cameraInfoString.get() + " a ";
		//}
	}
	if (bResend.draw()) {
		testResend.draw();
		comboResend_value_t.draw();
		listboxResend_value_t.drawListbox();
	}

	// Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::ShowTestWindow(&show_test_window);
	}
	
	gui.end();
}

//--------------------------------------------------------------
void SharedSettings::load(){
	json = ofLoadJson("settings.json");
	ofDeserialize(json, syncParams);
}

//--------------------------------------------------------------
void SharedSettings::save() {
	ofSerialize(json, syncParams);
	ofSavePrettyJson("settings.json", json);
}

/*
bool SharedSettings::addListeners(* camera) {
	bool success;

	sharedSettings.imageFrameRate.addListener(&camera, &Camera::setImageFramerate);

	return success;
}
*/