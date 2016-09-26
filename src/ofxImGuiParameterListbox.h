#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"

class ofxImGuiParameterListbox : public ofParameter<ofVec4f>
{

public:
	ofxImGuiParameterListbox(ofxImGuiParameterListbox& copy)
		: stringRef(copy.stringRef)
	{
	};

	ofxImGuiParameterListbox(ofParameter<string> & opt)
		: stringRef(opt)
	{
	};


	ofParameter<ofVec4f> & setOptions(const ofVec4f & val) {
		return setOptions(this->getName(), val, this->getMin(), this->getMax());
	};
	ofParameter<ofVec4f> & setOptions(const string& name, const ofVec4f & val) {
		return setOptions(name, val, this->getMin(), this->getMax());
	};
	ofParameter<ofVec4f> & setOptions(const string& name, const ofVec4f & val, const ofVec4f & min, const ofVec4f & max)
	{
		options = stringRef.get();
		value = val;

		//		OFXIMGUIPARAM_VERBOSE << "2 " << ofToString(options) << "]";
		OFXIMGUIPARAM_VERBOSE << "number of items " << parseOptions(options);
		ofVec4f maximum = ofVec4f(1);
		ofVec4f minimum = ofVec4f(0);

		setName(name);
		set(value);
		setMin(minimum);
		setMax(maximum);

		OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "getValue [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMin   [" << this->getMin() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMax   [" << this->getMax() << "]";
		OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";
		OFXIMGUIPARAM_VERBOSE << "options  [" << options << "]";

		return *this;
	};

	//-----------
	void drawListbox()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());

		ImGui::ListBoxHeader("##listbox", 4);

		bool x = (bool)value.x;
		bool y = (bool)value.y;
		bool z = (bool)value.z;
		bool w = (bool)value.w;

		ImGui::Selectable(comboItems[0].c_str(), &x);
		ImGui::Selectable(comboItems[1].c_str(), &y);
		ImGui::Selectable(comboItems[2].c_str(), &z);
		ImGui::Selectable(comboItems[3].c_str(), &w);

		value.x = x;
		value.y = y;
		value.z = z;
		value.w = w;

		ImGui::ListBoxFooter();

		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	const ofParameter<string>& getStringRef() {
		return stringRef;
	}
	const ofVec4f& getOldValueRef() {
		return oldValue;
	}

	//-----------
	void setOnNextFrame(const ofVec4f & v)
	{
		OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "ofParameter  [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "value        [" << value << "]";
		OFXIMGUIPARAM_VERBOSE << "new value	   [" << v << "]";

		value = v;
		needsUpdateOnNextFrame = true;
	}

private:
	ofVec4f	value;
	ofVec4f	oldValue;

	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;
	
	int sliderWidth = 180;
	int inputIntWidth = 80;

	bool didChange = false;
	bool needsUpdateOnNextFrame = false;
	bool isNextFrame = false;


	//-----------
	int parseOptions(string incoming_str) {
		if (incoming_str == "") {
			OFXIMGUIPARAM_VERBOSE << "string is empty!";
			OFXIMGUIPARAM_VERBOSE << "setting default";
			incoming_str = "a||b||c||d";
		}

		size_t pos = 0;
		size_t index = -1;
		std::string token;
		//		OFXIMGUIPARAM_VERBOSE << "3 " << ofToString(options) << "]";
		comboItems.clear();
		//while (incoming_str.length() > 0) {
		for (int i=0; i<5; i++ ){
			if ((pos = incoming_str.find(OFXIMGUIPARAM_DELIMITER)) != std::string::npos) {
				token = incoming_str.substr(0, pos);
				OFXIMGUIPARAM_VERBOSE << "token " << token;
				comboItems.push_back(token);
				incoming_str.erase(0, pos + ((string)OFXIMGUIPARAM_DELIMITER).length());
				index++;
			}
			//get the last element if there is no delimiter at the end
			else {
				OFXIMGUIPARAM_VERBOSE << "token " << incoming_str;
				comboItems.push_back(incoming_str);
				incoming_str.clear();
				index++;
			}
		}
		return index;
	}

	//-----------
	bool getOfParameter()
	{
		didChange = false;
		if (needsUpdateOnNextFrame) return didChange;
		if (this->get() != this->value)
		{
			value = this->get();
			OFXIMGUIPARAM_VERBOSE << "get Value [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline bool setOfParameter()
	{
		didChange = false;
		if (needsUpdateOnNextFrame) return didChange;

		// has to be here
		oldValue = this->get();

		if (this->get() != this->value)
		{
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old value [" << oldValue << "]";
			OFXIMGUIPARAM_VERBOSE << "result    [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline bool setOfParameterOnNextFrame(){
		didChange = false;
		// if we need to update the value out of ofListener
		if (needsUpdateOnNextFrame) {
			if (isNextFrame) {
				OFXIMGUIPARAM_VERBOSE << "applying after frame";
				needsUpdateOnNextFrame = false;
				isNextFrame = false;

				if (this->get() != this->value)
				{
					OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
					OFXIMGUIPARAM_VERBOSE << "old value [" << this->get() << "]";
					OFXIMGUIPARAM_VERBOSE << "new value [" << value << "]";
					this->set(value);
					didChange = true;
				}
				// no idea why i can not use it like this
				// some weird recursion appears between server and client
				//				setOfParameter();

			}
			else {
				isNextFrame = true;
			}
		}
		return didChange;
	}

};

