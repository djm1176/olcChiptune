#pragma once
#include "Window.h"

class PianoWindow :
    public Window {

public:
	PianoWindow(int x, int y, int w, int h);

	void Draw(olcConsoleGameEngine* enginePtr) override;

	void onMouseDown(int) override;
	void onMouseUp(int) override;
	void onMouseMove(int, int) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;

private:
	/// <summary>
	/// Lowest pitch that is displayed on the piano roll
	/// </summary>
	int m_VerticalOffset;

	/// <summary>
	/// Number of measures to offset for displaying
	/// </summary>
	int m_HorizontalOffset;


	/// <summary>
	/// Position of the cursor, i.e. which note space is highlighted
	/// </summary>
	int m_CursorX, m_CursorY;


};

