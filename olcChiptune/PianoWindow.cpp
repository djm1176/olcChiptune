#include "PianoWindow.h"
#include "Event.h"
#include "Frequency.h"
#include "Helpers.h"
#include "Chiptune.h"
//#include "Characters.h"


PianoWindow::PianoWindow(int x, int y, int w, int h) : Window(x, y, w, h),
	m_CursorX{ 0 }, m_CursorY{ 0 }, m_HorizontalOffset{ 0 },
	m_VerticalOffset{ 0 }, m_HorizontalZoom{ 4 } {

	/*
	Create mouse/keyboard events, however this could also be moved in Chiptune (i.e. higher up) scope if wanted (or abstracted into a keyboard config structure?)
	*/

	//Scrolling up/down
	Event evt_Scroll = Event([&](Event src) {IncrementVerticalOffset(src); });
	evt_Scroll.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, Event::KeyModifiers::None, -1, -1, -1));
	evt_Scroll.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, Event::KeyModifiers::None, -1, -1, 1));
	AddCallback(evt_Scroll);

	//Zooming in/out
	Event evt_Zoom = Event([&](Event src) {IncrementHorizontalZoom(src); });
	evt_Zoom.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, Event::KeyModifiers::Alt, -1, -1));
	evt_Zoom.AddTrigger(Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, Event::KeyModifiers::Alt, -1, 1));
	AddCallback(evt_Zoom);

}

void PianoWindow::Draw(Chiptune& chiptune) {
	//Clear the window
	int x, y, w, h;
	if(GetRect(x, y, w, h))
		chiptune.Fill(x, y, x + w, y + h, PIXEL_SOLID, FG_BLACK | BG_BLACK);

	// Draw vertical features
	for (int i = 0; i < h - 2; i++) {
		//Scale on left side. Max length is 3 pixels
		chiptune.DrawString(x, y - i, Frequency::pitchToWstring(i + m_VerticalOffset, true), FG_GREY);
	}

	// Draw horizontal features
	for (int i = 0; i < w - 3; i++) {
		//Measure dividers
		if (i % m_HorizontalZoom == 0 && i != 0 /*Skip first measure divider*/ ) {
			//chiptune.DrawLine(x + i, y + 2, x + i, y + h, BoxDrawing::LINE_VERTICAL, FG_DARK_CYAN);
		}
	}
}

void PianoWindow::IncrementVerticalOffset(Event evt) {
	int x, y, w, h;
	GetRect(x, y, w, h);
	int amount = evt.GetTriggers()[0].mouseWheel;
	m_VerticalOffset = Math::clamp(m_VerticalOffset + amount, 0, PianoWindow::MAX_PITCH - h + 2);
}

void PianoWindow::IncrementHorizontalZoom(Event evt) {
	int direction = evt.GetTriggers()[0].mouseWheel;
	m_HorizontalZoom = Math::clamp(m_HorizontalZoom + direction, ZOOM_MIN, ZOOM_MAX);
}