#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"

class ofxImGuiParameterListbox : public ofParameter<ofVec4f>
{

public:
	ofxImGuiParameterListbox(ofxImGuiParameterListbox& copy)
		: stringRef(copy.getStringRef())
	{
	};

	ofxImGuiParameterListbox(ofParameter<string> & opt)
		: stringRef(opt)
	{
	};


	ofParameter<ofVec4f> & setCombo(const ofVec4f & val) {
		return setCombo(this->getName(), val, this->getMin(), this->getMax());
	};
	ofParameter<ofVec4f> & setCombo(const string& name, const ofVec4f & val) {
		return setCombo(name, val, this->getMin(), this->getMax());
	};
	ofParameter<ofVec4f> & setCombo(const string& name, const ofVec4f & val, const ofVec4f & min, const ofVec4f & max)
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

		OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
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

	ofParameter<string>& getStringRef() {
		return stringRef;
	}

private:
	ofVec4f	value;
	bool didChange = false;
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;
	int sliderWidth = 180;
	int inputIntWidth = 80;



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
		if (this->get() != this->value)
		{
			value = this->get();
			OFXIMGUIPARAM_VERBOSE << "get Value [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

	//-----------
	bool setOfParameter()
	{
		// special case. we need at least one selected
		if (this->value == ofVec4f(0))
		{
			value = this->get();
			OFXIMGUIPARAM_VERBOSE << "tired to set all to 0. Skipping..";
			OFXIMGUIPARAM_VERBOSE << "get Value [" << value << "]";
			didChange = true;
			return didChange;
		}

		didChange = false;
		if (this->get() != this->value)
		{
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "[" << value << "]";
			didChange = true;
		}
		return didChange;
	}
};

