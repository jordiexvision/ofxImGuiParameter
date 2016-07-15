#include "ofApp.h"

#define STRINGIFY(x) #x

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_NOTICE);
	ofSetBackgroundColor(50);	
	ofSetVerticalSync(true);

	gui.setup(new GuiShellTheme());
	show_test_window = true;

	string xmlString = STRINGIFY(
	<group>
	<imageFrameRate max="1000" min="1" type="int">0</ imageFrameRate>
	</group>
	);

//	controlPanel.setup(xmlString);
	sharedSettings.imageFrameRate.addListener(&camera, &Camera::setImageFramerate);

	sharedSettings.float_t.addListener(&camera, &Camera::setFloatValue);
	sharedSettings.int_t.addListener(&camera, &Camera::setIntValue);
	sharedSettings.bool_t.addListener(&camera, &Camera::setBoolValue);
//	sharedSettings.Input_string_t.addListener(&camera, &Camera::setStringValue);
	sharedSettings.button_t.addListener(&camera, &Camera::setButtonValue);

	// a synchronized combo box
	sharedSettings.combo_options_t.addListener(&camera, &Camera::setOptionsValue);
	sharedSettings.combo_value_t.addListener(&camera, &Camera::setComboValue);

	
	sync.setup((ofParameterGroup&)sharedSettings.syncParams,
		sharedSettings.paramSyncClientPort,
		sharedSettings.paramSyncIP,
		sharedSettings.paramSyncServerPort);
		
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
//	controlPanel.drawInt(sharedSettings.imageFrameRate);
//	controlPanel.drawBool(sharedSettings.imageFrameRate);

	sharedSettings.float_t.drawSliderFloat();
	sharedSettings.int_t.drawSliderInt();
	sharedSettings.bool_t.drawCheckbox();
	sharedSettings.OSD_string_t.drawTextWrapped();
//	sharedSettings.Input_string_t.drawInputText();
	sharedSettings.button_t.drawButton();

//	sharedSettings.Input_string_t.drawInputText();
//	sharedSettings.Input_string_t.drawTextWrapped();

	sharedSettings.combo_options_t.drawInputText();
	sharedSettings.combo_value_t.drawCombo();

	// Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::ShowTestWindow(&show_test_window);
	}


	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    ofLogVerbose(__FUNCTION__) << key;
    switch (key)
    {
        case 'r':
        {
			sharedSettings.imageFrameRate.removeListener(&camera, &Camera::setImageFramerate);
            break;
        }
		case 's':
		{
			
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