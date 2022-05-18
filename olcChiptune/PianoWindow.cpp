#include "PianoWindow.h"
#include "Event.h"
#include "Frequency.h"
#include "Helpers.h"
#include "Chiptune.h"
#include "Characters.h"
#include "Style.h"
#include "DebugWindow.h"


PianoWindow::PianoWindow(int x, int y, int w, int h) : Window(x, y, w, h),
	m_CursorX{ 0 }, m_CursorY{ 0 }, m_HorizontalOffset{ 0 },
	m_VerticalOffset{ 0 }, m_PageOffset{ 0 }, m_HorizontalZoom{ 4 } {

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

	//Mouse Cursor
	Event evt_Cursor = Event([&](Event src) {MoveCursor(src); });
	evt_Cursor.AddTrigger(Event::Trigger(Event::State::OnKeyDown, Event::Context::Global, Event::KeyModifiers::None, -1, VK_UP));
	evt_Cursor.AddTrigger(Event::Trigger(Event::State::OnKeyDown, Event::Context::Global, Event::KeyModifiers::None, -1, VK_DOWN));
	evt_Cursor.AddTrigger(Event::Trigger(Event::State::OnKeyDown, Event::Context::Global, Event::KeyModifiers::None, -1, VK_LEFT));
	evt_Cursor.AddTrigger(Event::Trigger(Event::State::OnKeyDown, Event::Context::Global, Event::KeyModifiers::None, -1, VK_RIGHT));
	evt_Cursor.AddTrigger(Event::Trigger(Event::State::OnMouseMove, Event::Context::Global, Event::KeyModifiers::None, -1, -1));
	AddCallback(evt_Cursor);

}

void PianoWindow::Draw(Chiptune& chiptune) {
	//Clear the window
	int x, y, w, h;
	if(GetRect(x, y, w, h))
		chiptune.Fill(x, y, x + w, y + h, PIXEL_SOLID, FG_BLACK | BG_BLACK);

	// Draw cursor lines
	chiptune.DrawLine(x + m_CursorX, y + 2, x + m_CursorX, y + h, PIXEL_SOLID, BG_DARK_MAGENTA); //Vertical
	chiptune.DrawLine(x + 3, y + m_CursorY, x + 3, y + m_CursorY, PIXEL_SOLID, BG_DARK_MAGENTA); //Horizontal

	// Draw vertical features
	for (int i = 0; i < h - 2; i++) {
		//Scale on left side. Max length is 3 pixels
		chiptune.DrawString(x, y + h - i, Frequency::pitchToWstring(i + m_VerticalOffset, true), FG_GREY);
	}

	// Draw horizontal features
	for (int i = 0; i < w - 3; i++) {
		//Measure dividers
		if (i % m_HorizontalZoom == 0 && i != 0 /*Skip first measure divider*/ ) {
			chiptune.DrawLine(x + i, y + 2, x + i, y + h, BoxDrawing::LINE_VERTICAL, FG_DARK_CYAN);
		}
		else if (i > 2) {
			// Draw dots over empty beats
			chiptune.DrawLine(x + i, y + 2, x + i, y + h, L'.', FG_DARK_GREY);
		}
	}

	chiptune.Debugger().Log(std::to_wstring(m_CursorX));
	chiptune.Debugger().Log(std::to_wstring(m_CursorY));
	chiptune.Debugger().Log(std::to_wstring(m_HorizontalOffset));
	chiptune.Debugger().Log(std::to_wstring(m_VerticalOffset));
}

void PianoWindow::IncrementVerticalOffset(Event evt) {
	Event::Trigger t = evt.GetTriggers()[0];

	int x, y, w, h;
	GetRect(x, y, w, h);
	int amount = evt.GetTriggers()[0].mouseWheel;
	m_VerticalOffset = Math::clamp(m_VerticalOffset + amount, 0, PianoWindow::MAX_PITCH - h + 2);
}

void PianoWindow::IncrementHorizontalZoom(Event evt) {
	Event::Trigger t = evt.GetTriggers()[0];

	int direction = t.mouseWheel;
	m_HorizontalZoom = Math::clamp(m_HorizontalZoom + direction, ZOOM_MIN, ZOOM_MAX);
}

void PianoWindow::MoveCursor(Event evt) {
	Event::Trigger t = evt.GetTriggers()[0];

	int x, y, w, h;
	GetRect(x, y, w, h);
	if (t.state == Event::OnMouseMove) {
		m_CursorX = Math::clamp(t.mouseX - x + 3, 0, w);
		m_CursorY = Math::clamp(y + h - t.mouseY, 0, h - 2);
	}
	else if (t.state == Event::OnKeyDown) {
		if (t.key == VK_UP)
			m_CursorY = Math::clamp(m_CursorY + 1, 0, MAX_PITCH);
		else if (t.key == VK_DOWN)
			m_CursorY = Math::clamp(m_CursorY - 1, 0, MAX_PITCH);
		else if (t.key == VK_LEFT)
			m_CursorX = Math::clamp(m_CursorX - 1, -1, w);
		else if (t.key == VK_RIGHT)
			m_CursorX = Math::clamp(m_CursorX + 1, 0, w);

		//Adjust window if necessary
		if (m_CursorY > m_VerticalOffset) {
			//Cursor went above highest displayed pitch
			m_VerticalOffset = m_CursorY - h + pitchRows();
		}
		else if (m_CursorY < m_VerticalOffset) {
			//Cursor went below lowest displayed pitch
			m_VerticalOffset = m_CursorY;
		}


		if (m_CursorX > w - 2) {
			int _movePages = m_CursorX / w;
			m_CursorX %= w;

			m_PageOffset += _movePages;
		}
		else if (m_CursorX < 0) {
			if (m_PageOffset > 0) {
				m_PageOffset--;
				m_CursorX = w - 3;
			} else
				m_CursorX = 0;
		}
	}
}

int PianoWindow::pitchRows() {
	int x, y, w, h;
	GetRect(x, y, w, h);
	return h - 2;
}
