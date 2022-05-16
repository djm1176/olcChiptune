#pragma once
#include "Window.h"
#include "Chiptune.h"

class PianoWindow :
    public Window {

public:
	PianoWindow(int x, int y, int w, int h);

	void Draw(Chiptune* chiptunePtr) override;

private:

	/// <summary>
	/// Position of the cursor, i.e. which note space is highlighted
	/// </summary>
	int m_CursorX, m_CursorY;

	/// <summary>
	/// The lowest pitch shown on in the piano window.
	/// </summary>
	int m_verticalOffset;

};

