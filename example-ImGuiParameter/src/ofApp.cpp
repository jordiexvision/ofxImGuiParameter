#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetBackgroundColor(50);
	ofSetVerticalSync(true);
	
	sharedSettings.setupServer();
	addListeners();

//	needsUpdate = false;
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

	// resend parameter after event
	//https://forum.openframeworks.cc/t/ofxoscparametersync-resend-after-listener-event-or-force-update-send/24226
	// listeners must be where settings are.
	sharedSettings.testResend.addListener(this, &ofApp::testResend_f);
	sharedSettings.bCameraInfo.addListener(this, &ofApp::updateCameraInfo_str);

}

//--------------------------------------------------------------
void ofApp::testResend_f(int & value) {
	sharedSettings.testResend.setOnNextFrame(value * 10);

	// this will not update the client
//	value = value * 10;
}

//--------------------------------------------------------------
void ofApp::updateCameraInfo_str(bool & value) {

	sharedSettings.cameraInfoString.setOnNextFrame(sharedSettings.cameraInfoString.get() + " a ");

	// or update it on next frame will work too.
//	needsUpdate = true;

	// this will not update the client
//	if (sharedSettings.bCameraInfo) sharedSettings.cameraInfoString = sharedSettings.cameraInfoString.get() + " a ";
//	cout << "#################### has changed on callback" << endl;
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
	
	sharedSettings.update();

	// or update it on next frame will work too.
	//if (needsUpdate) {
	//	if (sharedSettings.bCameraInfo) sharedSettings.cameraInfoString = sharedSettings.cameraInfoString.get() + " a ";
	//	cout << "#################### has changed on update" << endl;
	//	needsUpdate = false;
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	sharedSettings.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    ofLogVerbose(__FUNCTION__) << key;
    switch (key)
    {
		/*
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
		*/
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
		default:
		{
			sharedSettings.OSD_string_t = sharedSettings.OSD_string_t.get() + (char)key ;
			sharedSettings.OSD_string_t2 = sharedSettings.OSD_string_t2.get() + (char)key;
			sharedSettings.OSD_string_t3 = sharedSettings.OSD_string_t3.get() + (char)key;
			break;
		}
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y){

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