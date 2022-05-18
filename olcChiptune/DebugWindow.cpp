#include "DebugWindow.h"
#include "Event.h"
#include "Chiptune.h"

DebugWindow::DebugWindow(int x, int y, int w, int h) : Window(x, y, w, h), stack{ new std::wstring[h] }, first{ 0 }, len{ h - 2 } {
}

void DebugWindow::Log(const std::string& message) {
	auto wstr = std::wstring(message.begin(), message.end());
	Log(wstr);
}

void DebugWindow::Log(const std::wstring& message) {
	//Replace the element at first
	stack[first] = message;

	//Increment first
	first = (first + 1) % len;

}

void DebugWindow::Draw(Chiptune& chiptune) {
	int x, y, w, h;
	GetRect(x, y, w, h);

	chiptune.Fill(x, y, x + w, y + h, PIXEL_SOLID, FG_BLACK | BG_BLACK);

	//Draw each message one at a time
	for (int i = 0; i < len; i++)
		chiptune.DrawString(x, y + i, stack[(i + first) % len].substr(0, w - 2));

}

DebugWindow::~DebugWindow() {
	delete[] stack;
}
