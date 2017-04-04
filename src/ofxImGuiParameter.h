#pragma once
#include "ofxImGui.h"
#include "ofxImGuiParameterUtils.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

template<typename ParameterType>
class ofxImGuiParameter: public ofParameter<ParameterType>
{
public:
	ofParameterGroup	paramGroup;

protected:
	ParameterType		value;
	ParameterType		oldValue;

	bool	didChange			= false;
	bool	needsUpdateOnNextFrame = false;
	bool	isNextFrame			= false;
	int		sliderWidth			= 180;
	int		inputIntWidth		= 100;
	char	str[OFXIMGUIPARAM_STRING_MAX_LENGTH];
	virtual bool drawWidget() { return true; };

public:
	const int& getSliderWidth() {
		return sliderWidth;
	}

	void setSliderWidth(int value) {
		sliderWidth = value;
	}

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
	void setOnNextFrame(const ParameterType & v)
	{
		OFXIMGUIPARAM_VERBOSE << "getName      [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "ofParameter  [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "value        [" << value << "]";
		OFXIMGUIPARAM_VERBOSE << "new value    [" << v << "]";

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
		updateWidget();
	}
	//-----------
	bool hasChanged() {
		return didChange;
	}
	//-----------
	bool updateWidget()
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

protected:
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