#pragma once

#include <vector>

class Event {
	struct Trigger {
		Trigger(bool triggerOnKeyDown = false, bool triggerOnKeyUp = false, bool triggerOnMouseDown = false, bool triggerOnMouseUp = false, bool triggerOnMouseMove = false, int mouseIndex = 0, int key = 0);

		bool triggerOnKeyDown, triggerOnKeyUp, triggerOnMouseDown, triggerOnMouseUp, triggerOnMouseMove;
		int mouseIndex;
		int key;
	};

public:

	/// <summary>
	/// Defines a FUNCTION to be called as a result of an event occurring
	/// </summary>
	typedef bool CallbackFunction(int);

	/// <summary>
	/// Instantiate an Event that binds a function callback to one or more matching triggers
	/// </summary>
	/// <param name="func"></param>
	/// <param name="..."></param>
	Event(CallbackFunction func, Trigger triggers...);

private:
	std::vector<Event::Trigger> m_Triggers;

};

