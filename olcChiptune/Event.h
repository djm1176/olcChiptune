#pragma once

#include <vector>
#include <functional>

class Event {
public:
	enum State { OnKeyDown, OnKeyUp, OnMouseDown, OnMouseUp, OnMouseMove, OnMouseWheel, OnFocus };
	enum Context { Global, Focused };

	struct KeyModifiers {
		static constexpr int None = 0;
		static constexpr int Control = 1;
		static constexpr int Shift = 2;
		static constexpr int Alt = 4;
	};

	struct Trigger {
		Trigger(State state, Context context, int keyModifiers = KeyModifiers::None, int mouseIndex = -1, int key = -1, int mouseWheel = 0);

		void SetKeyModifiers(bool ctrl, bool shift, bool alt);

		//Member variables
		State state;
		Context context;
		int keyModifiers;
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
	void Invoke(Event& evt);

	const std::vector<Event::Trigger>& GetTriggers();

private:
	std::vector<Event::Trigger> m_Triggers;
	Callback m_Callback;
};

