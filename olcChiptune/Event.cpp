#include "Event.h"

Event::Trigger::Trigger(State state, Context context, int mouseIndex, int key) :
	state{ state },
	context{ context },
	mouseIndex{ mouseIndex },
	key{ key } {}

Event::Event(CallbackFunction function) {
	m_Function = function;
}

void Event::AddTrigger(Trigger t) {
	m_Triggers.push_back(t);
}