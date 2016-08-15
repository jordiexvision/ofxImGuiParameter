#pragma once
#include "ofMain.h"
#include "ofxImGuiParameter.h"
#include "ofxImGui.h"
#include "Utils.h"

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
		OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "[" << value << "]";

		this->set(value);
		didChange = true;
	}
	return didChange;
}

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
		strncpy(str, this->get().c_str(), newlength);
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
