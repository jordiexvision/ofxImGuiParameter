#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"
#include "ofxImGuiParameter.h"

//--------------------------------------------------------------
class SliderFloat : public ofxImGuiParameter<float>{
public:
	using  ofxImGuiParameter<float>::operator=;
	bool drawWidget() override { drawSliderFloat(); return true; }

	//-----------
	void drawSliderFloat()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::PushItemWidth(width * 0.6f);
		ImGui::SliderFloat(
			"##SliderFloat",	//this->getName().c_str(),
			&this->value,
			this->getMin(),
			this->getMax(),
			this->getName().c_str());
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushItemWidth(width * 0.3f);
		ImGui::InputFloat("##f1",
			&this->value,
			this->getMin(),
			this->getMax()
		);
		ImGui::PopItemWidth();

		setOfParameter();
	}
};

//--------------------------------------------------------------
class SliderInt : public ofxImGuiParameter<int> {
public:
	using  ofxImGuiParameter<int>::operator=;
	bool drawWidget() override { drawSliderInt(); return true; }

	//-----------
	void drawSliderInt()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::PushItemWidth(width * 0.6f);
		ImGui::SliderInt(
			"##SliderInt",	//this->getName().c_str(),
			&this->value,
			this->getMin(),
			this->getMax(),
			this->getName().c_str());
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushItemWidth(width * 0.3f);
		ImGui::InputInt("##i1", &this->value);
		ImGui::PopItemWidth();

		setOfParameter();
	}
};

//--------------------------------------------------------------
class FpsPlot : public ofxImGuiParameter<float> {
public:
	using  ofxImGuiParameter<float>::operator=;
	bool drawWidget() override { drawPlot(); return true; }

	static const int size = 100;
	float queue[size];
	int offset = 0;

	//-----------
	void drawPlot(int width = 10)
	{
		queue[offset] = this->get();
		offset++;
		if (offset == size) offset = 0;

		string label = this->getName() + " " + ofToString(this->get(), 1);

		ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
		ImGui::PlotHistogram(
			"##FpsPlot", 
			queue,
			IM_ARRAYSIZE(queue),
			offset, 
			label.c_str(),
			this->getMin(), 
			this->getMax(), 
			ImVec2(0, 50)
		);
		ImGui::PopItemWidth();
	}
};

//--------------------------------------------------------------
class CheckBox : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { drawCheckbox(); return true; }

	//-----------
	void drawCheckbox()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::Checkbox(
			this->getName().c_str(),//"##Checkbox",
			&this->value);

		setOfParameter();
	}
};

//--------------------------------------------------------------
class CollapsingHeader : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { return drawCollapsingHeader(); }

	//-----------
	bool drawCollapsingHeader(bool returnChangesOnly = false)
	{
		getOfParameter();

		// apply from Client
		ImGui::SetNextTreeNodeOpen(value);

		// draw and catch input
		value = ImGui::CollapsingHeader(this->getName().c_str());

		setOfParameter();

		if (returnChangesOnly) return didChange;

		return value;
	}
};

//--------------------------------------------------------------
class TextWrapped : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool drawWidget() override { drawTextWrapped(); return true; }
	//-----------
	void drawTextWrapped()
	{
		setOfParameterOnNextFrame();

		getOfString();

//		static float wrap_width = sliderWidth;
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + width);
		ImGui::TextWrapped(str);

		// draw custom frame
		ImGui::GetWindowDrawList()->AddRectFilled(
			ImGui::GetItemBoxMin(),
			ImVec2(ImGui::GetItemBoxMax().x + ImGuiStyleVar_FramePadding, ImGui::GetItemBoxMax().y + ImGuiStyleVar_FramePadding),
			ImColor(0, 255, 255, 25)
		);

		ImGui::PopTextWrapPos();

		// don-t need coz imgui will not change it
		//		setOfString();
	}
};

//--------------------------------------------------------------
class InputText : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool drawWidget() override { drawInputText(); return true; }
	//-----------
	void drawInputText()
	{
		getOfString();

		ImGui::Text(this->getName().c_str());
		if (ImGui::InputText(
			"##InputText",
			str,
			OFXIMGUIPARAM_STRING_MAX_LENGTH
		)) {
			setOfString();
		}
	}
};

//--------------------------------------------------------------
class InputTextMultiline : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool drawWidget() override { drawInputTextMultiline(); return true; }

	//-----------
	void drawInputTextMultiline()
	{
		getOfString();

		ImGui::Text(this->getName().c_str());
		if (ImGui::InputTextMultiline(
			"##InputText",
			str,
			OFXIMGUIPARAM_STRING_MAX_LENGTH
		))
		{
			setOfString();
		}
		ImGui::PopID();
	}
};

//--------------------------------------------------------------
class Button : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { drawButton(); return true; }

	//-----------
	void drawButton()
	{
		getOfParameter();

		if (ImGui::Button(this->getName().c_str())) {
			value = true;
		}
		else {
			value = false;
		}

		// don-t need coz imgui will not change it?
		setOfParameter();
	}
};

//--------------------------------------------------------------
class Toggle : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { return true; }

	//-----------
	void drawToggleButton(string stringOnTrue, string stringOnFalse)
	{
		getOfParameter();

		bool isPressed;
		if (value) {
			if (ImGui::Button(stringOnTrue.c_str())) {
				value = !value;
			}
		}
		else {
			if (ImGui::Button(stringOnFalse.c_str())) {
				value = !value;
			}
		}

		// don-t need coz imgui will not change it?
		setOfParameter();
	}
};

//--------------------------------------------------------------
class Popup : public ofxImGuiParameter<int> {
public:
	using  ofxImGuiParameter<int>::operator=;
	bool drawWidget() override { return true; }

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

	//-----------
	void drawPopUpfromMenu(ofBuffer & text, int width = ofGetWidth() / 2, int height = ofGetHeight() / 2)
	{

		getOfParameter();


		//		if (ImGui::Button(this->getName().c_str())) {
		if (ImGui::MenuItem(this->getName().c_str(), "", false, !(bool*)this->get())) {

			value = !value;
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "result    [" << value << "]";
		}

		drawPopUp(text, width, height);


	}
};

//--------------------------------------------------------------
class Panel : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { return true; }

	//-----------
	bool beginPanel(ofParameter<ofVec2f>& position, ofParameter<ofVec2f>& size)
	{
		getOfParameter();

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
	//-----------
	void endPanel()
	{
		ImGui::End();
	}

	//-----------
	void drawCheckbox()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

		ImGui::Checkbox(
			this->getName().c_str(),//"##Checkbox",
			&this->value);

		setOfParameter();
	}

};

//--------------------------------------------------------------
class Window : public ofxImGuiParameter<bool> {
public:
	Window() {
		//		sharedParams.add(bIsOpen.set("Open", true));
		settings.setName("Window Settings");
		settings.add(position.set("Position", ofVec2f(100, 100), ofVec2f(20, 20), ofVec2f(10000, 10000)));
		settings.add(size.set("Size", ofVec2f(320, 300), ofVec2f(320, 20), ofVec2f(10000, 10000)));
		settings.add(gridSize.set("Grid Size", ofVec2f(20, 20), ofVec2f(0, 0), ofVec2f(100, 100)));
		settings.add(name.set("Name", "Untitled"));

		//set window properties
		bool no_titlebar = false;
		bool no_border = false;
		bool no_resize = false;
		bool no_move = false;
		bool no_scrollbar = false;
		bool no_collapse = false;
		bool no_menu = true;
		bool no_settings = true;

		if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
		if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
		if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
		if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
		if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
		if (no_settings) window_flags |= ImGuiWindowFlags_NoSavedSettings;
	}

	//	ofxImGuiParameter<bool>	bIsOpen;
	ofxImGuiParameter<ofVec2f>	position;
	ofxImGuiParameter<ofVec2f>	size;
	ofxImGuiParameter<ofVec2f>	gridSize;
	ofxImGuiParameter<string>	name;

	// ImGui
	ImGuiWindowFlags window_flags = 0;
	float bg_alpha = -0.01f; // <0: default

	using  ofxImGuiParameter<bool>::operator=;
	bool drawWidget() override { return true; }

	//-----------
	bool begin()//const string& windowName, ofParameter<ofVec2f>& position, ofParameter<ofVec2f>& size)
	{
		getOfParameter();

		if (value == true) {

			void  SetNextWindowFocus();
			bool open;

			open = ImGui::Begin(name.get().c_str(), &value, ImVec2(size), bg_alpha, window_flags);
			setOfParameter();

			// set from imgui to of
			if (ImGui::IsWindowFocused() &&
				ImGui::IsWindowHovered() &&
				ImGui::IsMouseDragging()) {

				// aplly grid
				ofVec2f _position = nearest(ImGui::GetWindowPos(), gridSize);
				ofVec2f _size = nearest(ImGui::GetWindowSize(), gridSize);

				// set minimum position
				ofVec2f minpos(MAX(_position.x, 0), MAX(_position.y, 18));

				position.set(minpos);
				size.set(_size);
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
	//-----------
	void end()
	{
		ImGui::End();
	}

	//-----------
	void drawCheckbox()
	{
		setOfParameterOnNextFrame();

		//getOfParameter();
		value = this->get();

		ImGui::Checkbox(
			name.get().c_str(),//"##Checkbox",
			&value);

		//setOfParameter();
		this->set(value);
	}

	ofVec2f nearest(ofVec2f value, ofVec2f multiple) {
		ofVec2f result;
		result.x = ((int)value.x + ((int)multiple.x / 2)) / (int)multiple.x * (int)multiple.x;
		result.y = ((int)value.y + ((int)multiple.y / 2)) / (int)multiple.y * (int)multiple.y;
		return result;
	}
};

//--------------------------------------------------------------
class Combo : public ofxImGuiParameter<int>{
public:
	using  ofxImGuiParameter<int>::operator=;
	bool drawWidget() override { drawCombo(); return true; }

	Combo(Combo& copy)
		: stringRef(copy.stringRef)
	{
	};

	Combo(ofParameter<string> & opt)
		: stringRef(opt)
	{
	};

	const ofParameter<string>& getStringRef() {
		return stringRef;
	}
	const int& getOldValueRef() {
		return oldValue;
	}

	ofParameter<int> & setOptions(const int & val) {
		return setOptions(this->getName(), val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setOptions(const string& name, const int & val) {
		return setOptions(name, val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setOptions(const string& name, const int & val, const int & min, const int & max)
	{
		options = stringRef.get();
		value = val;

		//		OFXIMGUIPARAM_VERBOSE << "2 " << ofToString(options) << "]";
		int maximum = parseOptions(options);
		setName(name);
		set(value);
		setMin(0);
		setMax(maximum);

		OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "getValue     [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMin       [" << this->getMin() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMax       [" << this->getMax() << "]";
		OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";
		OFXIMGUIPARAM_VERBOSE << "options      [" << options << "]";

		return *this;
	};

private:
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;

	//-----------
	void drawCombo()
	{

		setOfParameterOnNextFrame();

		getOfParameter();

		// use vectors as const char *
		// https://github.com/ocornut/imgui/issues/673
		ImGui::Combo("##Combo", &value,
			[](void* vec, int idx, const char** out_text) {
			std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= vector->size())return false;
			*out_text = vector->at(idx).c_str();
			return true;
		}, reinterpret_cast<void*>(&comboItems), comboItems.size());

		setOfParameter();
	}

	//-----------
	int parseOptions(string incoming_str) {
		if (incoming_str == "") {
			OFXIMGUIPARAM_VERBOSE << "string is empty!";
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
			OFXIMGUIPARAM_VERBOSE << "get Value    [" << value << "]";
			didChange = true;
		}
		if (stringRef.get() != this->options)
		{
			options = stringRef;
			OFXIMGUIPARAM_VERBOSE << "get String   [" << options << "]";
			// update
			setMax(parseOptions(options));

			OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "getValue     [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMin       [" << this->getMin() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMax       [" << this->getMax() << "]";
			OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";

			didChange = true;
		}
		return didChange;
	}
};

class ListBox : public ofxImGuiParameter<ofVec4f>{
public:
	using  ofxImGuiParameter<ofVec4f>::operator=;
	bool drawWidget() override { drawListbox(); return true; }

	ListBox(ListBox& copy)
		: stringRef(copy.stringRef)
	{
	};

	ListBox(ofParameter<string> & opt)
		: stringRef(opt)
	{
	};

	const ofParameter<string>& getStringRef() {
		return stringRef;
	}
	const ofVec4f& getOldValueRef() {
		return oldValue;
	}

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

		OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "getValue     [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMin       [" << this->getMin() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMax       [" << this->getMax() << "]";
		OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";
		OFXIMGUIPARAM_VERBOSE << "options      [" << options << "]";

		return *this;
	};

private:
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;

	//-----------
	void drawListbox()
	{
		setOfParameterOnNextFrame();

		getOfParameter();

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

		setOfParameter();
	}

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
		for (int i = 0; i<5; i++) {
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
	inline bool setOfParameterOnNextFrame() {
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

