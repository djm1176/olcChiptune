#include "Event.h"

Event::Trigger::Trigger(State state, Context context, int mouseIndex, int key, int mouseWheel) :
	state{ state },
	context{ context },
	mouseIndex{ mouseIndex },
	key{ key },
	mouseX{ -1 },
	mouseY{ -1 },
	mouseWheel{ mouseWheel } {}

Event::Event(Callback callback) {
	m_Callback = callback;
}

void Event::AddTrigger(Trigger t) {
	m_Triggers.push_back(t);
}

void Event::Invoke(Event& evt) {
	if (m_Callback != nullptr) {
		m_Callback(evt);
	}
}

const std::vector<Event::Trigger> Event::GetTriggers() {
	return m_Triggers;
}
