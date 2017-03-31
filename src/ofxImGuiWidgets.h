#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"
#include "ofxImGuiParameter.h"

//--------------------------------------------------------------
class SliderFloat : public ofxImGuiParameter<float>{
public:
	using  ofxImGuiParameter<float>::operator=;
	bool draw() override { drawSliderFloat(); return true; }

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
};

//--------------------------------------------------------------
class SliderInt : public ofxImGuiParameter<int> {
public:
	using  ofxImGuiParameter<int>::operator=;
	bool draw() override { drawSliderInt(); return true; }

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
};

//--------------------------------------------------------------
class IntPlot : public ofxImGuiParameter<float> {
public:
	using  ofxImGuiParameter<float>::operator=;
	bool draw() override { drawPlot(); return true; }

	static const int size = 100;
	float queue[size];
	int offset = 0;

	//-----------
	void drawPlot()
	{
//		setOfParameterOnNextFrame();

//		getOfParameter();

//		ImGui::PushID(this->getName().c_str());

//		if (ImGui::CollapsingHeader(this->getName().c_str())) {
//			queue[offset] = value;
			queue[offset] = this->get();

			offset++;
			if (offset == size) offset = 0;
//			ImGui::PushID("IntPlot");

			ImGui::PushItemWidth(sliderWidth);
			ImGui::PlotHistogram(
				"##IntPlot", 
				queue,
				IM_ARRAYSIZE(queue),
				offset, 
				string(this->getName()+" "+ofToString(this->get(), 0)).c_str(),
				this->getMin(), 
				this->getMax(), 
				ImVec2(0, 50)
			);
			ImGui::PopItemWidth();
//			ImGui::PopID();
//		}

//		ImGui::PopID();

//		setOfParameter();
	}
};

//--------------------------------------------------------------
class CheckBox : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { drawCheckbox(); return true; }

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
};

//--------------------------------------------------------------
class CollapsingHeader : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { return drawCollapsingHeader(); }

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
};

//--------------------------------------------------------------
class TextWrapped : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool draw() override { drawTextWrapped(); return true; }
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
};

//--------------------------------------------------------------
class InputText : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool draw() override { drawInputText(); return true; }
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
};

//--------------------------------------------------------------
class InputTextMultiline : public ofxImGuiParameter<string> {
public:
	using  ofxImGuiParameter<string>::operator=;
	bool draw() override { drawInputTextMultiline(); return true; }

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
};

//--------------------------------------------------------------
class Button : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { drawButton(); return true; }

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
};

//--------------------------------------------------------------
class Toggle : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { return true; }

	//-----------
	void drawToggleButton(string stringOnTrue, string stringOnFalse)
	{
		getOfParameter();

		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
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

		ImGui::PopItemWidth();
		ImGui::PopID();

		// don-t need coz imgui will not change it?
		setOfParameter();
	}
};

//--------------------------------------------------------------
class Popup : public ofxImGuiParameter<int> {
public:
	using  ofxImGuiParameter<int>::operator=;
	bool draw() override { return true; }

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
};

//--------------------------------------------------------------
class Panel : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { return true; }

	//-----------
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
	//-----------
	void endPanel()
	{
		ImGui::End();
		//		ImGui::PopID();
	}

};

//--------------------------------------------------------------
class Window : public ofxImGuiParameter<bool> {
public:
	using  ofxImGuiParameter<bool>::operator=;
	bool draw() override { return true; }

	//-----------
	bool beginWindow(string& windowName, ofParameter<ofVec2f>& position, ofParameter<ofVec2f>& size)
	{
		getOfParameter();

		//		ImGui::PushID(this->getName().c_str());

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
	//-----------
	void endWindow()
	{
		ImGui::End();
		//		ImGui::PopID();
	}
};
