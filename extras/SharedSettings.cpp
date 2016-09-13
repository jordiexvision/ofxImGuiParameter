#include "SharedSettings.h"

SharedSettings::SharedSettings(){

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
	syncParams_b.add(float_t1.set("float test 11111", 0.2f, 0.0f, 1.0f));
	syncParams_b.add(int_t1.set("syncParams_b", 1234, 1, 1000));

	syncParams.add(bool_t.set("bool test", true));
	syncParams.add(OSD_string_t.set("OSDtext1", "lorem ipsum1"));
	syncParams.add(OSD_string_t2.set("OSD text2", "lorem ipsum2"));
	syncParams.add(OSD_string_t3.set("OSD text3", "lorem ipsum3"));

	syncParams.add(button_t.set("button test", false));
	syncParams.add(Input_string_t.set("Input text field", "try to edit string"));
	syncParams.add(collapsingHeader_t.set("Collapsing Header Sample", true));

	string items = "Aaaaaaa||bbbbbbbb||ccccccc||dddddddddd||eeeeeeee||fffffffff||gggggggggggg||hhhhhhhh";
	syncParams.add(combo_options_t.set("combo options", items));
	syncParams.add(combo_value_t.setCombo("combo value", 1));

	syncParams.add(bCameraInfo.set("Camera Information", false));
	syncParams.add(cameraInfoString.set("Camera Information string", "Unknown"));

	syncParams.add(testResend.set("testResend", 1, 1, 1000));

	syncParams.add(popUp_1.set("popUp_1", false));
	syncParams.add(popUp_2.set("popUp_2", false));

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
	
	if (ImGui::CollapsingHeader("tests", false)) {
		float_t.drawSliderFloat();
		int_t.drawSliderInt();
		float_t1.drawSliderFloat();
		int_t1.drawSliderInt();
		bool_t.drawCheckbox();
		button_t.drawButton();

		OSD_string_t.drawTextWrapped();
		OSD_string_t2.drawTextWrapped();
		OSD_string_t3.drawTextWrapped();

		Input_string_t.drawInputText();
		//	sharedSettings.Input_string_t.drawInputTextMultiline();

		if (collapsingHeader_t.drawCollapsingHeader()) {
			combo_options_t.drawInputText();
			combo_value_t.drawCombo();
		}
	}

	if (bCameraInfo.drawCollapsingHeader()) {

		cameraInfoString.drawTextWrapped();

		popUp_1.drawPopUp(credits);
		popUp_2.drawPopUp(shortcuts, 400, 300);

		// this will not update the client
		//if (sharedSettings.bCameraInfo.hasChanged()) {
		//	cout << "#################### has changed on draw" << endl;
		//	sharedSettings.cameraInfoString = sharedSettings.cameraInfoString.get() + " a ";
		//}
	}

	testResend.drawSliderInt();

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