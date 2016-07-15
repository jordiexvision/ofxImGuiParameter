#pragma once
#include "ofMain.h"
#include "ofxImGui.h"

#define OFXIMGUIPARAM_DELIMITER "||"
#define OFXIMGUIPARAM_COMBO_ITEM_MAX_LENGTH 256

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
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;
	int sliderWidth = 180;
	int inputIntWidth = 80;
//	std::string delimiter = "/|/";


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
		bool didChange = false;
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
		bool didChange = false;
		if (this->get() != this->value)
		{
			this->set(this->getName(), value);
			OFXIMGUIPARAM_VERBOSE << "setOfParameter to [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

};


template<typename T>
class ofxImGuiParameter: public ofParameter<T>
{
public:
    
	T value;
	char str[OFXIMGUIPARAM_COMBO_ITEM_MAX_LENGTH];

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

	int sliderWidth = 180;
	int inputIntWidth = 80;

	string type() const
    {
        return typeid(ofParameter<T>).name();
    }
    void setFromExisting(ofParameter<T>& existingParameter, bool doUpdate = false )
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
		this->value = MAX(this->value, this->getMin());
		this->value = MIN(this->value, this->getMax());
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	void drawSliderInt()
	{
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
		this->value = MAX(this->value, this->getMin());
		this->value = MIN(this->value, this->getMax());
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
		ImGui::Text(this->getName().c_str());
		ImGui::Checkbox(
			"##Checkbox",	//this->getName().c_str(),
			&this->value);
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	void drawTextWrapped()
	{
		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		ImGui::TextWrapped(
			this->get().c_str());
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	void drawInputText()
	{

		// here we have a problem, 
		// Imgui  does not handle strings.
		// only char *s (const char * is not accepted either..)
		// so we need to convert string to char per frame...
		// http://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
		// http://stackoverflow.com/questions/5844040/c-setting-a-static-char-array-with-a-string


		getOfParameter();

		//		char IDname[100];   // array to hold the result.
		//		strcpy(IDname, "##InputText"); // copy string one into the result.
		//		strcat(IDname, this->getName().c_str()); // append string two to the result.

				// convert our string to static char
		static char str[OFXIMGUIPARAM_COMBO_ITEM_MAX_LENGTH];
		int length = strlen(this->get().c_str());
		strncpy(str, this->value.c_str(), length);

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		if (ImGui::InputText(
			this->getName().c_str(),
			str,
			OFXIMGUIPARAM_COMBO_ITEM_MAX_LENGTH
		))
		{
			int newlength = strlen(str);
			if (length != newlength)
			{
				OFXIMGUIPARAM_VERBOSE << "str  in  [" << this->value << "]";
				OFXIMGUIPARAM_VERBOSE << "size in  [" << length << "]";
				OFXIMGUIPARAM_VERBOSE << "str  out [" << str << "]";
				OFXIMGUIPARAM_VERBOSE << "size out [" << newlength << "]";

				this->set(this->getName(), str);
			}
		}
		ImGui::PopItemWidth();
		ImGui::PopID();
	}

	//-----------
	void drawInputTextMultiline()
	{
		getOfParameter();

		// convert our string to static char

		int length = strlen(this->value.c_str());
		strncpy(str, this->value.c_str(), length);

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		if (ImGui::InputTextMultiline(
			"##InputText",
			str,
			OFXIMGUIPARAM_COMBO_ITEM_MAX_LENGTH
		))
		{
			int newlength = strlen(str);
			if (length != newlength)
			{
				OFXIMGUIPARAM_VERBOSE << "str  in  [" << this->value << "]";
				OFXIMGUIPARAM_VERBOSE << "size in  [" << length << "]";
				OFXIMGUIPARAM_VERBOSE << "str  out [" << str << "]";
				OFXIMGUIPARAM_VERBOSE << "size out [" << newlength << "]";

				this->set(this->getName(), str);
			}
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
			this->set(this->getName(), value);
			OFXIMGUIPARAM_VERBOSE << "setOfParameter to [" << value << "]";
		}
		ImGui::PopItemWidth();
		ImGui::PopID();
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
	bool getOfParameter()
	{
		bool didChange = false;
		if (this->get() != this->value)
		{
			value = this->get();
			OFXIMGUIPARAM_VERBOSE << "getOfParameter [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

	//-----------
	bool setOfParameter()
	{
		bool didChange = false;
		if (this->get() != this->value)
		{
			this->set(this->getName(), value);
			OFXIMGUIPARAM_VERBOSE << "setOfParameter [" << value << "]";
			didChange = true;
		}
		return didChange;
	}

	//-----------
    bool update()
    {
        bool didChange = false;
		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "setOfParameter to [" << value <<"]";
			this->set(this->getName(), value);
			didChange = true;
		}
        return didChange;
    }
};
