#include "PianoWindow.h"
#include "Frequency.h"

PianoWindow::PianoWindow(int x, int y, int w, int h) : Window(x, y, w, h) {}

void PianoWindow::Draw(Chiptune* chiptunePtr) {
	// Draw the scale on the left

	for (int i = 0; i < h; i++) {
		chiptunePtr->DrawString(0, h - i, Frequency::pitchToWstring(i + m_verticalOffset, true);
	}
}