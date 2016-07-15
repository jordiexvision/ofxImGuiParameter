#pragma once
#include "ofMain.h"

#define OFXIMGUIPARAM_VERBOSE ofLogVerbose(string(__func__))
#define OFXIMGUIPARAM_NOTICE ofLogNotice(string(__func__))
#define OFXIMGUIPARAM_WARNING ofLogWarning(string(__func__))
#define OFXIMGUIPARAM_ERROR ofLogError(string(__func__))
#define OFXIMGUIPARAM_FATAL ofLogFatalError(string(__func__))

class Camera {
public:
	void setImageFramerate(int & value) {
		imageFrameRate = value;
		OFXIMGUIPARAM_NOTICE << value ;
	}
	int		imageFrameRate;

	void setFloatValue(float & value) {		OFXIMGUIPARAM_NOTICE << value ; }
	void setIntValue(int & value) {			OFXIMGUIPARAM_NOTICE << value ; }
	void setBoolValue(bool & value) {		OFXIMGUIPARAM_NOTICE << value ; }
	void setStringValue(string & value) {	OFXIMGUIPARAM_NOTICE << value ; }
	void setButtonValue(bool & value) {		OFXIMGUIPARAM_NOTICE << value ; }
	void setComboValue(int & value) {		OFXIMGUIPARAM_NOTICE << value ; }
	void setOptionsValue(string & value) {	OFXIMGUIPARAM_NOTICE << "//////" <<value ; }

	//	void setValue(float & value) { cout << value ; }
	//	void setValue(int & value) { cout << value ; }
	//	void setValue(bool & value) { cout << value ; }
	//	void setValue(string & value) { cout << value ; }

	//	template<typename T>
	//	void setValue(ofxSyncedParameter<ofParameter<T>> & value) { cout << value ; }
	//	void setValue(ofParameter<int> & value) { cout << value ; }
	//	void setValue(ofParameter<bool> & value) { cout << value ; }
	//	void setValue(ofParameter<string> & value) { cout << value ; }
};