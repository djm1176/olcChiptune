#pragma once

#include <vector>
#include <functional>

class Event {
public:
	enum State { OnKeyDown, OnKeyUp, OnMouseDown, OnMouseUp, OnMouseMove, OnMouseWheel, OnFocus };
	enum Context { Global, Focused };

	struct Trigger {
		Trigger(State state, Context context, int mouseIndex = -1, int key = -1, int mouseWheel = 0);

		//Member variables
		State state;
		Context context;
		int mouseIndex;
		int mouseWheel;
		int mouseX, mouseY;
		int key;
	};

	typedef std::function<void(Event)> Callback;

	/// <summary>
	/// Instantiate an Event that binds a function callback to one or more matching triggers
	/// </summary>
	/// <param name="func"></param>
	/// <param name="..."></param>
	Event(Callback func);

	void AddTrigger(Trigger trigger);
	void Invoke(Event &evt);

	const std::vector<Event::Trigger> GetTriggers();

private:
	std::vector<Event::Trigger> m_Triggers;
	Callback m_Callback;
};

