#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#include "ofxOscParameterSync.h"
#include "SharedSettings.h"
#include "GuiShellTheme.h"
#include "Camera.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
	void addListeners();
	void removeListeners();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(float x, float y);
    
    ofxImGui gui;
	SharedSettings sharedSettings;
	ofxOscParameterSync sync;

	Camera camera;

	bool 	show_test_window = false;
	bool	show_another_window = false;

};