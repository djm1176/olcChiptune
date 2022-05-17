#include "PianoWindow.h"
#include "Frequency.h"
#include "Helpers.h"

PianoWindow::PianoWindow(int x, int y, int w, int h) : Window(x, y, w, h), m_CursorX{ 0 }, m_CursorY{ 0 } {
	//Create mouse/keyboard events, however this could also be moved in Chiptune scope if wanted

	//Scrolling up/down
	Event evt = Event(IncrementVerticalOffset);
	//addCallback(Event(
}

void PianoWindow::Draw(Chiptune* chiptunePtr) {
	// Draw the scale on the left

	for (int i = 0; i < NUM_ROWS; i++) {
		chiptunePtr->DrawString(1, 1 + std::get<1>(GetRect()) - i, Frequency::pitchToWstring(i + m_verticalOffset, true));
	}
}

bool PianoWindow::IncrementVerticalOffset(int amount) {
	m_verticalOffset = Math::clamp(m_verticalOffset + amount, 0, PianoWindow::MAX_PITCH - NUM_ROWS);
	return true;
}
