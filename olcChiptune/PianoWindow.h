#pragma once

#include "Window.h" // Required for inheritance

class Event;

class PianoWindow :
	public Window {

public:
	static constexpr int MAX_PITCH = 88;
	static constexpr int ZOOM_MIN = 4;
	static constexpr int ZOOM_MAX = 48;

	PianoWindow(int x, int y, int w, int h);

	void Draw(Chiptune& chiptune) override;

	//UI Events
	void IncrementVerticalOffset(Event evt);
	void IncrementHorizontalZoom(Event evt);
	void MoveCursor(Event e);

protected:
	int pitchRows();

private:

	/// <summary>
	/// Position of the cursor, i.e. which note space is highlighted in Piano Roll space.
	/// In other words, the bottom-left most position is (0, 0), NOT (x, y + h).
	/// </summary>
	int m_CursorX, m_CursorY;

	/// <summary>
	/// The lowest pitch shown on in the piano window.
	/// </summary>
	int m_VerticalOffset;

	/// <summary>
	/// The offset in time intervals to display, starting on the left-most side of the piano roll
	/// </summary>
	int m_HorizontalOffset;

	/// <summary>
	/// The offset in pages to start displaying.
	/// </summary>
	int m_PageOffset;

	/// <summary>
	/// The amount to zoom horizontally (time domain) by.
	/// Equal to how many rows of pixels are given to a quarter note. Default is 4.
	/// </summary>
	int m_HorizontalZoom;

};

