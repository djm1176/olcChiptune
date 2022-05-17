#pragma once

#include <vector>

class Event {
	struct Trigger {
		enum State {OnKeyDown, OnKeyUp, OnMouseDown, OnMouseUp, OnMouseMove, OnFocus};
		enum Context {Global, Focused};

		Trigger(State state, Context context, int mouseIndex = 0, int key = 0);

		//Member variables
		State state;
		Context context;
		int mouseIndex;
		int key;
	};

public:

	/// <summary>
	/// Defines a FUNCTION to be called as a result of an event occurring
	/// </summary>
	typedef bool(*CallbackFunction)(int);

	/// <summary>
	/// Instantiate an Event that binds a function callback to one or more matching triggers
	/// </summary>
	/// <param name="func"></param>
	/// <param name="..."></param>
	Event(CallbackFunction func);

	void AddTrigger(Trigger trigger);

private:
	std::vector<Event::Trigger> m_Triggers;
	CallbackFunction m_Function;
};

