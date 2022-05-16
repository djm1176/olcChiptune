#include "Event.h"

Event::Trigger::Trigger(bool triggerOnKeyDown, bool triggerOnKeyUp, bool triggerOnMouseDown, bool triggerOnMouseUp, bool triggerOnMouseMove, int mouseIndex, int key) :
	triggerOnKeyDown{ triggerOnKeyDown },
	triggerOnKeyUp{ triggerOnKeyUp },
	triggerOnMouseDown{ triggerOnMouseDown },
	triggerOnMouseUp{ triggerOnMouseUp },
	triggerOnMouseMove{ triggerOnMouseMove },
	mouseIndex{ mouseIndex },
	key{ key } {}
