#pragma once
#include "ofMain.h"
#include "ofxImGui.h"

#define OFXIMGUIPARAM_DELIMITER "||"
#define OFXIMGUIPARAM_STRING_MAX_LENGTH 1256

#define OFXIMGUIPARAM_VERBOSE ofLogVerbose(string(__func__))
#define OFXIMGUIPARAM_NOTICE ofLogNotice(string(__func__))
#define OFXIMGUIPARAM_WARNING ofLogWarning(string(__func__))
#define OFXIMGUIPARAM_ERROR ofLogError(string(__func__))
#define OFXIMGUIPARAM_FATAL ofLogFatalError(string(__func__))

class ofxImGuiofParameterCombo : public ofParameter<int>
{

public:
	ofxImGuiofParameterCombo(ofxImGuiofParameterCombo& copy) 
		: stringRef(copy.getStringRef())
	{
	};
	
	ofxImGuiofParameterCombo(ofParameter<string> & opt) 
		: stringRef(opt) 
	{
	};


	ofParameter<int> & setCombo(const int & val) {
		return setCombo(this->getName(), val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setCombo(const string& name, const int & val) {
		return setCombo(name, val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setCombo(const string& name, const int & val, const int & min, const int & max)
	{
		options = stringRef.get();
		value = val;

		//		OFXIMGUIPARAM_VERBOSE << "2 " << ofToString(options) << "]";
		int maximum = parseOptions(options);
		setName(name);
		set(value);
		setMin(0);
		setMax(maximum);

		OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "getValue [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMin   [" << this->getMin() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMax   [" << this->getMax() << "]";
		OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";
		OFXIMGUIPARAM_VERBOSE << "options  ["		<< options << "]";

		return *this;
	};

	//-----------
	void drawCombo()
	{
		getOfParameter();


		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		// use vectors as const char *
		// https://github.com/ocornut/imgui/issues/673
		ImGui::Combo("##Combo", &value,
			[](void* vec, int idx, const char** out_text) {
			std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= vector->size())return false;
			*out_text = vector->at(idx).c_str();
			return true;
		}, reinterpret_cast<void*>(&comboItems), comboItems.size());
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	ofParameter<string>& getStringRef() {
		return stringRef;
	}

private:
	int	value;
	bool didChange = false;
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;
	int sliderWidth = 180;
	int inputIntWidth = 80;


	//-----------
	int parseOptions(string incoming_str) {
		if (incoming_str == "") {
			OFXIMGUIPARAM_VERBOSE << "string is empty!" ;
			return 0;
		}

		size_t pos = 0;
		size_t index = -1;
		std::string token;
//		OFXIMGUIPARAM_VERBOSE << "3 " << ofToString(options) << "]";
		comboItems.clear();
		while (incoming_str.length() > 0) {
			if ((pos = incoming_str.find(OFXIMGUIPARAM_DELIMITER)) != std::string::npos) {
				token = incoming_str.substr(0, pos);
				OFXIMGUIPARAM_VERBOSE << "token " << token ;
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
		if (stringRef.get() != this->options)
		{
			options = stringRef;
			OFXIMGUIPARAM_VERBOSE << "get String [" << options << "]";
			// update
			setMax(parseOptions(options));

			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "getValue [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMin   [" << this->getMin() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMax   [" << this->getMax() << "]";
			OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";

			didChange = true;
		}
		return didChange;
	}

	//-----------
	bool setOfParameter()
	{
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


template<typename ParameterType>
class ofxImGuiParameter: public ofParameter<ParameterType>
{
public:
    
	ParameterType value;
//	ParameterType valueOnNextFrame;
	char str[OFXIMGUIPARAM_STRING_MAX_LENGTH];
	bool didChange = false;
	bool needsUpdate = false;
	bool isNextFrame = false;
	int sliderWidth = 180;
	int inputIntWidth = 80;

	// forward operator definitions to base class
	ofParameter<ParameterType> & operator=(const ofParameter<ParameterType> & v);
	const ParameterType & operator=(const ParameterType & v);

	// use constructors of parent class
	// http://stackoverflow.com/questions/347358/inheriting-constructors
	// https://en.wikipedia.org/wiki/C%2B%2B11#Object_construction_improvement
//	using ofParameter::ofParameter; //not sure if its ok in all compilers.

	/*
	ofxImGuiParameter() {
		ofParameter();};
	ofxImGuiParameter(const ofParameter<T> & v) {
		ofParameter(const ofParameter<T> & v);
		value = v;
	};
	ofxImGuiParameter(const T & v) {
		ofParameter(v);
		value = v;
	};
	ofxImGuiParameter(const string& name, const T & v) {
		ofParameter(name, v);
		value = v;
	};
	ofxImGuiParameter(const string& name, const T & v, const T & min, const T & max) {
		ofParameter(name, v, min, max);
		value = v;
	};
	*/

	string type() const
    {
        return typeid(ofParameter<ParameterType>).name();
    }
    void setFromExisting(ofParameter<ParameterType>& existingParameter, bool doUpdate = false )
    {
        value = existingParameter;
        this->makeReferenceTo(existingParameter);
        if(doUpdate)
        {
            startUpdating();
        }
        
    }
    
	//-----------
	void drawSliderFloat()
	{
		getOfParameter();
		
		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		ImGui::SliderFloat(
			"##SliderFloat",	//this->getName().c_str(),
			&this->value,
			this->getMin(),
			this->getMax());
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PushItemWidth(inputIntWidth);
		ImGui::InputFloat("##f1",
			&this->value,
			this->getMin(),
			this->getMax()
		);
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	void drawSliderInt()
	{

		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		ImGui::SliderInt(
			"##SliderInt",	//this->getName().c_str(),
			&this->value,
			this->getMin(),
			this->getMax());
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PushItemWidth(inputIntWidth);
		ImGui::InputInt("##i1", &this->value);
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();

	}

	//-----------
	void drawCheckbox()
	{
		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
//		ImGui::Text(this->getName().c_str());
		ImGui::Checkbox(
			this->getName().c_str(),//"##Checkbox",
			&this->value);
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	bool drawCollapsingHeader(bool returnChangesOnly=false)
	{

		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		// apply from Client
		ImGui::SetNextTreeNodeOpen(value);
		// draw and catch input
		value = ImGui::CollapsingHeader(this->getName().c_str());
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();

		if (returnChangesOnly) return didChange;

		return value;
	}

	//-----------
	void drawTextWrapped()
	{
		setOfParameterOnNextFrame();

		getOfString();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		static float wrap_width = sliderWidth;
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);

		ImGui::TextWrapped(str);

		// draw custom frame
		ImGui::GetWindowDrawList()->AddRectFilled(
			ImGui::GetItemBoxMin(),
			ImVec2(ImGui::GetItemBoxMax().x + ImGuiStyleVar_FramePadding, ImGui::GetItemBoxMax().y + ImGuiStyleVar_FramePadding),
			ImColor(0,255,255,25)
		);

		ImGui::PopTextWrapPos();
		ImGui::PopItemWidth();
		ImGui::PopID();

		// don-t need coz imgui will not change it
//		setOfString();
	}

	//-----------
	void drawInputText()
	{
		getOfString();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		if (ImGui::InputText(
			"##InputText",
			str,
			OFXIMGUIPARAM_STRING_MAX_LENGTH
		)){
			setOfString();
		}
		ImGui::PopItemWidth();
		ImGui::PopID();
	}

	//-----------
	void drawInputTextMultiline()
	{
		getOfString();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		if (ImGui::InputTextMultiline(
			"##InputText",
			str,
			OFXIMGUIPARAM_STRING_MAX_LENGTH
		))
		{
			setOfString();
		}
		ImGui::PopItemWidth();
		ImGui::PopID();
	}

	//-----------
	void drawButton()
	{
		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		if (ImGui::Button(this->getName().c_str())) {
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "[" << value << "]";
		}
		ImGui::PopItemWidth();
		ImGui::PopID();

		// don-t need coz imgui will not change it
		//????setOfParameter();
	}

	/*
	void draw()
	{
//		cout << typeid(ofParameter<T>).name();
		ofAbstractParameter* param = this;
		ProbeResult probeResult = ParameterTypeUtils::probeType(this);
		switch (probeResult.type)
		{
		case FLOAT_:
		{
			cout << "FLOAT_";
			drawFloat();
			break;
		}
		case INT16_T:
		case INT32_T:
		case INT64_T:
		case INT8_T:
		{
			cout << "INT_";
			drawInt();
			break;
		}
		case BOOL_:
		{
			cout << "BOOL_";
			drawBool();
			break;
		}
		case STRING:
		{
			cout << "STRING";
			drawInputText();
			break;
		}
		}
	}
	*/

	//-----------
    void startUpdating()
	{
        ofAddListener(ofEvents().update, this, &ofxImGuiParameter::onUpdate);
    }

	//-----------
    void onUpdate(ofEventArgs& event)
	{
        update();
    }
    
	//-----------
	bool hasChanged() {
		return didChange;
	}

	//-----------
	inline bool getOfString()
	{
		didChange = false;
		int oldlength   = strlen(str);
		int newlength	= strlen(this->get().c_str());

		if (newlength > OFXIMGUIPARAM_STRING_MAX_LENGTH) {
			OFXIMGUIPARAM_ERROR << "String is too long.";
			OFXIMGUIPARAM_NOTICE << "Change OFXIMGUIPARAM_STRING_MAX_LENGTH or use shorter string.";
			return false;
		}

		if (oldlength != newlength)
		{
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old str  [" << str << "]";
			OFXIMGUIPARAM_VERBOSE << "old size [" << oldlength << "]";
			OFXIMGUIPARAM_VERBOSE << "new str  [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "new size [" << newlength << "]";

			// clear the char array
			memset(&str[0], 0, sizeof(str));
			//copy the string to the char array
			strncpy(str, this->get().c_str(), newlength);
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline 	bool setOfString()
	{
		didChange = false;
		int oldlength	= strlen(this->get().c_str());
		int newlength	= strlen(str);

		if (oldlength != newlength)
		{
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old str  [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "old size [" << oldlength << "]";
			OFXIMGUIPARAM_VERBOSE << "new str  [" << str << "]";
			OFXIMGUIPARAM_VERBOSE << "new size [" << newlength << "]";

			this->set(str);
			didChange = true;
		}
		return didChange;

	}

	//-----------
	inline bool getOfParameter()
	{
		didChange = false;
		if (needsUpdate) return didChange;

		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old value [" << value << "]";
			OFXIMGUIPARAM_VERBOSE << "new value [" << this->get() << "]";

			value = this->get();
			value = MAX(value, this->getMin());
			value = MIN(value, this->getMax());
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline bool setOfParameter()
	{
		didChange = false;
		if (needsUpdate) return didChange;

		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old value [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "new value [" << value << "]";

			this->set(value);
//			this->setWithoutEventNotifications(value);
			this->value = MAX(this->value, this->getMin());
			this->value = MIN(this->value, this->getMax());
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline bool setOfParameterOnNextFrame()
	{
		didChange = false;

		// if we need to update the value out of ofListener
		if (needsUpdate) {
			if (isNextFrame) {
				if (this->get() != this->value)
				{
					OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
					OFXIMGUIPARAM_VERBOSE << "old value [" << this->get() << "]";
					OFXIMGUIPARAM_VERBOSE << "new value [" << value << "]";

					this->set(value);
//					this->set(valueOnNextFrame);
//					this->setWithoutEventNotifications(valueOnNextFrame);
					this->value = MAX(this->value, this->getMin());
					this->value = MIN(this->value, this->getMax());
					didChange = true;
				}
				needsUpdate = false;
				isNextFrame = false;
			}
			isNextFrame = true;
		}

		return didChange;
	}

	//-----------
    bool update()
    {
       didChange = false;
		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "[" << value <<"]";

			this->set(value);
			didChange = true;
		}
        return didChange;
    }

	//-----------
	void setOnNextFrame(const ParameterType & v)
	{
		OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "ofParameter [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "value [" << value << "]";
		OFXIMGUIPARAM_VERBOSE << "new value [" << v << "]";

		value = v;
//		valueOnNextFrame = v;
		needsUpdate = true;
	}

};


// similar to ofParameter but returning base class operator:
template<typename ParameterType>
inline ofParameter<ParameterType> & ofxImGuiParameter<ParameterType>::operator=(const ofParameter<ParameterType> & v) {
	set(v);
	return ofParameter<ParameterType>::operator=(v);
}
template<typename ParameterType>
inline const ParameterType & ofxImGuiParameter<ParameterType>::operator=(const ParameterType & v) {
	set(v);
	return ofParameter<ParameterType>::operator=(v);
}
