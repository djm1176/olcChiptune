#pragma once

#include <vector>
#include "Style.h"
#include "Event.h"

class olcConsoleGameEngine;

class Window {
public:
	Window(int x, int y, int w, int h);

	virtual void Draw(olcConsoleGameEngine* enginePtr);

	virtual void onMouseDown(int) = 0;
	virtual void onMouseUp(int) = 0;
	virtual void onMouseMove(int, int) = 0;
	virtual void onKeyDown(int) = 0;
	virtual void onKeyUp(int) = 0;

	void setStyle(const Style* const style);
	void addCallback(Event evt);


private:
	int x, y, w, h;

	std::vector<Event> m_Events;
};

