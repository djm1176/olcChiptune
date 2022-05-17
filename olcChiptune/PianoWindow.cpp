#include "PianoWindow.h"
#include "Frequency.h"
#include "Helpers.h"

PianoWindow::PianoWindow(int x, int y, int w, int h) : Window(x, y, w, h), m_CursorX{ 0 }, m_CursorY{ 0 } {
	//Create mouse/keyboard events, however this could also be moved in Chiptune scope if wanted

	//Scrolling up/down

	Event evt = Event([&](Event src) {IncrementVerticalOffset(src); });
	evt.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, -1, -1, -1));
	evt.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, -1, -1, 1));

	AddCallback(evt);
}

void PianoWindow::Draw(Chiptune* chiptunePtr) {
	// Draw the scale on the left

	for (int i = 0; i < NUM_ROWS; i++) {
		chiptunePtr->DrawString(1, 1 + std::get<3>(GetRect()) - i, Frequency::pitchToWstring(i + m_verticalOffset, true));
	}
}

void PianoWindow::IncrementVerticalOffset(Event evt) {
	int amount = evt.GetTriggers()[0].mouseWheel;
	m_verticalOffset = Math::clamp(m_verticalOffset + amount, 0, PianoWindow::MAX_PITCH - NUM_ROWS);
}
