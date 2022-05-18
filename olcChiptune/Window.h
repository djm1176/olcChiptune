#pragma once

#include <vector>
#include "Style.h"
#include "Event.h"

class Chiptune;

class Window {
public:
	Window(int x, int y, int w, int h);
	
	void OnMouseDown(int index);
	void OnMouseUp(int index);
	void OnMouseMove(int x, int y);
	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void SetStyle(const Style* const style);
	void AddCallback(Event evt);
	const std::vector<Event> GetEvents();

	/// <summary>
	/// Called by the engine to perform draw operations on this window.
	/// </summary>
	void Render(Chiptune& chiptune);

protected:

	/// <summary>
	/// Perform any drawing operations on windows that subclass Window.
	/// </summary>
	/// <param name="chiptunePtr"></param>
	virtual void Draw(Chiptune& chiptune);

	/// <summary>
	/// Sets the bounds, in (x, y, w, h) of this Window
	/// </summary>
	/// <returns>True if the operation succeeded.</returns>
	bool GetRect(int& x, int& y, int& w, int& h) const;


private:
	int x, y, w, h;
	std::vector<Event> m_Events;

	void BaseDraw(Chiptune& chiptune);
};
