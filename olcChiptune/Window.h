#pragma once

#include <vector>
#include "Style.h"
#include "Event.h"
#include "Chiptune.h"

class Window {
public:
	Window(int x, int y, int w, int h);

	virtual void Draw(Chiptune* enginePtr);

	void setStyle(const Style* const style);
	void addCallback(Event evt);


protected:
	int x, y, w, h;

	std::vector<Event> m_Events;
};

