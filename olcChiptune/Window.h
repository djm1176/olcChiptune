#pragma once

#include <vector>
#include "Style.h"
#include "Event.h"

class Chiptune;

class Window {
public:
	Window(int x, int y, int w, int h);

	virtual void Draw(Chiptune* enginePtr);
	
	void OnMouseDown(int index);
	void OnMouseUp(int index);
	void OnMouseMove(int x, int y);
	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void SetStyle(const Style* const style);
	void AddCallback(Event evt);
	const std::vector<Event> GetEvents();


protected:

	/// <summary>
	/// Returns the bounds, in (x, y, w, h) of this Window
	/// </summary>
	/// <returns></returns>
	std::tuple<int, int, int, int> GetRect();


private:
	int x, y, w, h;
	std::vector<Event> m_Events;
};
