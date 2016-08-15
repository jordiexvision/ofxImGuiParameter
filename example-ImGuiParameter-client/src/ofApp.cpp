#include "ofApp.h"

#define STRINGIFY(x) #x

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetBackgroundColor(50);	
	ofSetVerticalSync(true);

	gui.setup(new GuiShellTheme());
	show_test_window = true;

	/*
	string xmlString = STRINGIFY(
	<group>
	<imageFrameRate max="1000" min="1" type="int">0</ imageFrameRate>
	</group>
	);

//	controlPanel.setup(xmlString);
	*/

	addListeners();
	
	sync.setup((ofParameterGroup&)sharedSettings.syncParams,
		sharedSettings.paramSyncClientPort,
		sharedSettings.paramSyncIP,
		sharedSettings.paramSyncServerPort);
		
}

//--------------------------------------------------------------
void ofApp::addListeners() {
	sharedSettings.float_t.addListener(&camera, &Camera::setFloatValue);
	sharedSettings.int_t.addListener(&camera, &Camera::setIntValue);
	sharedSettings.float_t1.addListener(&camera, &Camera::setFloatValue);
	sharedSettings.int_t1.addListener(&camera, &Camera::setIntValue);
	sharedSettings.bool_t.addListener(&camera, &Camera::setBoolValue);
	sharedSettings.button_t.addListener(&camera, &Camera::setButtonValue);
	sharedSettings.collapsingHeader_t.addListener(&camera, &Camera::setBoolValue);

	// a synchronized combo box
	sharedSettings.combo_options_t.addListener(&camera, &Camera::setOptionsValue);
	sharedSettings.combo_value_t.addListener(&camera, &Camera::setComboValue);
}

//--------------------------------------------------------------
void ofApp::removeListeners() {
	sharedSettings.float_t.removeListener(&camera, &Camera::setFloatValue);
	sharedSettings.int_t.removeListener(&camera, &Camera::setIntValue);
	sharedSettings.float_t1.removeListener(&camera, &Camera::setFloatValue);
	sharedSettings.int_t1.removeListener(&camera, &Camera::setIntValue);
	sharedSettings.bool_t.removeListener(&camera, &Camera::setBoolValue);
	sharedSettings.button_t.removeListener(&camera, &Camera::setButtonValue);
	sharedSettings.collapsingHeader_t.removeListener(&camera, &Camera::setBoolValue);

	// a synchronized combo box
	sharedSettings.combo_options_t.removeListener(&camera, &Camera::setOptionsValue);
	sharedSettings.combo_value_t.removeListener(&camera, &Camera::setComboValue);
}

//--------------------------------------------------------------
void ofApp::update(){
//	sharedSettings.imageFrameRate ++;
//	cout << ".";
	sync.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.begin();

	if (ImGui::CollapsingHeader("tests", false)) {
		sharedSettings.draw();
	}

	if (sharedSettings.bCameraInfo.drawCollapsingHeader()) {
//		if (sharedSettings.bCameraInfo.hasChanged()) {
//			cout << "#################### has changed" << endl;
//			sharedSettings.cameraInfoString = sharedSettings.cameraInfoString.get() + " a ";
//		}
		sharedSettings.cameraInfoString.drawTextWrapped();
	}

	sharedSettings.testResend.drawSliderInt();

	// Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::ShowTestWindow(&show_test_window);
	}

	gui.end();

//	ofDrawBitmapStringHighlight(ofToString(sharedSettings.testResend), ofVec2f(100, 100));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	ofLogVerbose(__FUNCTION__) << key;
	switch (key)
	{
		case 'r':
		{
			removeListeners();
			break;
		}
		case 'a':
		{
			addListeners();
			break;
		}
		case 'l':
		{
			sharedSettings.load();
			break;
		}
		case 's':
		{
			sharedSettings.save();
			break;
		}
		case 't':
		{
			sharedSettings.testResend++;
			break;
		}
		case '1':
		{
			sharedSettings.testResend=1;
			break;
		}
	}
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}


void ofApp::mouseScrolled(float x, float y)
{
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}