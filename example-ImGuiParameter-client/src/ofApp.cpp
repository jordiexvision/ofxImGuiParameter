#include "ofApp.h"

#define STRINGIFY(x) #x

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogToConsole();
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetBackgroundColor(50);	
	ofSetVerticalSync(true);

	sharedSettings.setupClient();
	addListeners();
	
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
	sharedSettings.update();
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