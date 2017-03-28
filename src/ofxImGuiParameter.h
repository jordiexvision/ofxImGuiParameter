#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"

template<typename ParameterType>
class ofxImGuiParameter: public ofParameter<ParameterType>
{
private:
	ParameterType	value;//= NULL;
	ParameterType	oldValue;//= NULL;
	bool	didChange			= false;
	bool	needsUpdateOnNextFrame = false;
	bool	isNextFrame			= false;
	int		sliderWidth			= 180;
	int		inputIntWidth		= 100;
	char	str[OFXIMGUIPARAM_STRING_MAX_LENGTH];

public:

	const int& getSliderWidth() {
		return sliderWidth;
	}

	void setSliderWidth(int value) {
		sliderWidth = value;
	}

	// templates can-t be defined in cpp
	// http://stackoverflow.com/questions/1353973/c-template-linking-error

	// use constructors of parent class
	// http://stackoverflow.com/questions/347358/inheriting-constructors
	// https://en.wikipedia.org/wiki/C%2B%2B11#Object_construction_improvement

	//	using ofParameter::ofParameter; //not sure if its ok in all compilers.
	/*
	ofxImGuiParameter() {
		ofParameter();
		cout << "getName   [" << this->getName() << "]" << endl;
		cout << "old value [" << value << "]" << endl;
		cout << "new value [" << this->get() << "]" << endl;
		value = this->get();
	};
	ofxImGuiParameter(const ofParameter<ParameterType> & v) {
		ofParameter(const ofParameter<ParameterType> & v);
		cout << "getName   [" << this->getName() << "]" << endl;
		cout << "old value [" << value << "]" << endl;
		cout << "new value [" << this->get() << "]" << endl;
		value = this->get();
		oldValue = value = v;
	};
	ofxImGuiParameter(const ParameterType & v) {
		ofParameter(v);
		cout << "getName   [" << this->getName() << "]" << endl;
		cout << "old value [" << value << "]" << endl;
		cout << "new value [" << this->get() << "]" << endl;
		value = this->get();
		oldValue = value = v;
	};
	ofxImGuiParameter(const string& name, const ParameterType & v) {
		ofParameter(name, v);
		cout << "getName   [" << this->getName() << "]" << endl;
		cout << "old value [" << value << "]" << endl;
		cout << "new value [" << this->get() << "]" << endl;
		value = this->get();
		oldValue = value = v;
	};
	ofxImGuiParameter(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max) {
		ofParameter(name, v, min, max);
		cout << "getName   [" << this->getName() << "]" << endl;
		cout << "old value [" << value << "]" << endl;
		cout << "new value [" << this->get() << "]" << endl;
		value = this->get();
		oldValue = value = v;
	};
	*/

//	template<typename ParameterType>
//	ofParameter<ParameterType> & set(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max) {
////		ofParameter::set(name, v, min, max);
////		getOfParameter();
////		this->oldValue = this->value = v;
//		return *this;
//	}
//	template<typename ParameterType>
//	ofParameter<ParameterType> & set(const string& name, const ParameterType & v) {
////		ofParameter::set(name, v);
////		getOfParameter();
//		return *this;
//	}
//	template<typename ParameterType>
//	inline ofParameter<ParameterType> & set(const ParameterType & v) {
////		ofParameter::set(v);
//		//		getOfParameter();
//		return *this;
//	}

	string type() const {
		return typeid(ofParameter<ParameterType>).name();
	}
	const ParameterType& getOldValueRef() {
		return oldValue;
	}


	// forward operator definitions to base class
	ofParameter<ParameterType> & operator=(const ofParameter<ParameterType> & v);
	const ParameterType & operator=(const ParameterType & v);

	//-----------
	void drawSliderFloat()
	{
		setOfParameterOnNextFrame();

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
		ImGui::PopID();

		ImGui::SameLine();
		ImGui::PushID(this->getName().c_str());
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
		ImGui::PopID();

		ImGui::SameLine();
		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(inputIntWidth);
		ImGui::InputInt("##i1", &this->value);
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	//-----------
	void drawCheckbox()
	{
		setOfParameterOnNextFrame();

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
	bool drawCollapsingHeader(bool returnChangesOnly = false)
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
			ImColor(0, 255, 255, 25)
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
		)) {
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
//			this->set(true);
			value = true;
		}
		else {
//			this->set(false);
			value = false;
		}

		ImGui::PopItemWidth();
		ImGui::PopID();

		// don-t need coz imgui will not change it?
		setOfParameter();
	}

	//-----------
	void drawToggleButton(string stringOnTrue, string stringOnFalse)
	{
		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		bool isPressed;
		if (value){
			if (ImGui::Button(stringOnTrue.c_str())) {
				value = !value;
			}
		}
		else {
			if (ImGui::Button(stringOnFalse.c_str())) {
				value = !value;
			}
		}

		ImGui::PopItemWidth();
		ImGui::PopID();

		// don-t need coz imgui will not change it?
		setOfParameter();
	}

	//-----------
	void drawPopUpfromMenu(ofBuffer & text, int width= ofGetWidth() / 2, int height= ofGetHeight() / 2)
	{

		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);

//		if (ImGui::Button(this->getName().c_str())) {
		if (ImGui::MenuItem(this->getName().c_str(), "", false, !(bool*)this->get())) {

			value = !value;
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "result    [" << value << "]";
		}

		drawPopUp(text, width, height);

		ImGui::PopItemWidth();
		ImGui::PopID();

	}

	//-----------
	void drawPopUp(ofBuffer & text, int width = ofGetWidth() / 2, int height = ofGetHeight() / 2)
	{
		if (this->get() == true) {
			ImGui::Begin(this->getName().c_str(), (bool*)this->get(), ImVec2(100, 100), 1.0,
				ImGuiWindowFlags_Modal |
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoSavedSettings
			);
			ImGui::SetWindowPos(ofVec2f(ofGetWidth() / 2 - (width / 2), ofGetHeight() / 2 - (height / 2)));
			ImGui::SetWindowSize(ofVec2f(width, height));
			ImGui::TextWrapped(text.getText().c_str());
			if (ImGui::Button("Close"))
				this->set(false);
			if (!ImGui::IsWindowFocused())
				this->set(false);
			ImGui::End();
		}
	}

	//--------------------------------------------------------------
	bool beginPanel(ofParameter<ofVec2f>& position, ofParameter<ofVec2f>& size)
	{
		getOfParameter();

		//		ImGui::PushID(this->getName().c_str());;

		if (value == true) {
			//set window properties
			static bool no_titlebar = false;
			static bool no_border = true;
			static bool no_resize = false;
			static bool no_move = false;
			static bool no_scrollbar = false;
			static bool no_collapse = false;
			static bool no_menu = true;
			static bool no_settings = true;
			static float bg_alpha = -0.01f; // <0: default

											// Typically you would just use the default.
			ImGuiWindowFlags window_flags = 0;
			if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
			if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
			if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
			if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
			if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
			if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
			if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
			if (no_settings) window_flags |= ImGuiWindowFlags_NoSavedSettings;

			bool open;
			open = ImGui::Begin(this->getName().c_str(), &value, ImVec2(size), bg_alpha, window_flags);
			setOfParameter();

			// set from imgui to of
			if (ImGui::IsWindowFocused() &&
				ImGui::IsWindowHovered() &&
				ImGui::IsMouseDragging()) {
				position.set(ImGui::GetWindowPos());
				size.set(ImGui::GetWindowSize());
			}
			else {
				ImGui::SetWindowPos(position.get());
				ImGui::SetWindowSize(size.get());
			}

			return open;
		}
		else {
			return false;
		}

	}

	//--------------------------------------------------------------
	bool beginWindow(string& windowName, ofParameter<ofVec2f>& position, ofParameter<ofVec2f>& size)
	{
		getOfParameter();

//		ImGui::PushID(this->getName().c_str());;
		
		if (value == true) {
			//set window properties
			static bool no_titlebar = false;
			static bool no_border = false;
			static bool no_resize = false;
			static bool no_move = false;
			static bool no_scrollbar = false;
			static bool no_collapse = false;
			static bool no_menu = true;
			static bool no_settings = true;
			static float bg_alpha = -0.01f; // <0: default

			// Typically you would just use the default.
			ImGuiWindowFlags window_flags = 0;
			if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
			if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
			if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
			if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
			if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
			if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
			if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
			if (no_settings) window_flags |= ImGuiWindowFlags_NoSavedSettings;

			void  SetNextWindowFocus();
			bool open;
			open = ImGui::Begin(windowName.c_str(), &value, ImVec2(size), bg_alpha, window_flags);
			setOfParameter();

			// set from imgui to of
			if (ImGui::IsWindowFocused() &&
				ImGui::IsWindowHovered() &&
				ImGui::IsMouseDragging()) {

				ofVec2f pos = ImGui::GetWindowPos();
				ofVec2f minpos;
				minpos.set(
					MAX(pos.x, 0),
					MAX(pos.y, 18));

				position.set(minpos);
				size.set(ImGui::GetWindowSize());
			}

			// set from of to imgui
			else {
				ImGui::SetWindowPos(position.get());
				ImGui::SetWindowSize(size.get());
			}

			return open;
		}
		else {
			return false;
		}

	}

	//--------------------------------------------------------------
	void endPanel()
	{
		ImGui::End();
		//		ImGui::PopID();
	}

	//--------------------------------------------------------------
	void endWindow()
	{
		ImGui::End();
//		ImGui::PopID();
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
	void setOnNextFrame(const ParameterType & v)
	{
		OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "ofParameter  [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "value        [" << value << "]";
		OFXIMGUIPARAM_VERBOSE << "new value	   [" << v << "]";

		value = v;
		needsUpdateOnNextFrame = true;
	}
	//-----------
	void setFromExisting(ofParameter<ParameterType>& existingParameter, bool doUpdate = false)
	{
		value = existingParameter;
		this->makeReferenceTo(existingParameter);
		if (doUpdate)
		{
			startUpdating();
		}
	}
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
	bool update()
	{
		didChange = false;
		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "result    [" << value << "]";

			this->set(value);
			didChange = true;
		}
		return didChange;
	}

private:
	//-----------
	inline bool getOfString()
	{
		didChange = false;
		int oldlength = strlen(str);
		int newlength = strlen(this->get().c_str());

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
			strncpy_s(str, this->get().c_str(), newlength);
			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline 	bool setOfString()
	{
		didChange = false;
		int oldlength = strlen(this->get().c_str());
		int newlength = strlen(str);

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
		if (needsUpdateOnNextFrame) return didChange;

		if (this->get() != this->value)
		{
			OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
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
		if (needsUpdateOnNextFrame) return didChange;

		// has to be here
		oldValue = this->get();

		if (this->get() != this->value)
		{

			value = MAX(this->value, this->getMin());
			value = MIN(this->value, this->getMax());

			OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "old value [" << oldValue << "]";
			OFXIMGUIPARAM_VERBOSE << "new value [" << value << "]";

			this->set(value);

			didChange = true;
		}
		return didChange;
	}

	//-----------
	inline bool setOfParameterOnNextFrame()
	{
		didChange = false;

		// if we need to update the value out of ofListener
		if (needsUpdateOnNextFrame) {
			if (isNextFrame) {
				if (this->get() != this->value)
				{
					OFXIMGUIPARAM_VERBOSE << "getName   [" << this->getName() << "]";
					OFXIMGUIPARAM_VERBOSE << "old value [" << this->get() << "]";
					OFXIMGUIPARAM_VERBOSE << "new value [" << value << "]";

					this->set(value);
					this->value = MAX(this->value, this->getMin());
					this->value = MIN(this->value, this->getMax());
					didChange = true;
				}
				needsUpdateOnNextFrame = false;
				isNextFrame = false;
			}
			else {
				isNextFrame = true;
			}
		}

		return didChange;
	}
};


//typedef ofxImGuiParameter<float> ofxImGuiParameter_;

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
