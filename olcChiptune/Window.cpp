#include "Window.h"
#include "olcConsoleGameEngine.h"

Window::Window(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

void Window::Draw(olcConsoleGameEngine* enginePtr) {
	enginePtr->Fill(x, y, x + w, y + h);
}

void Window::setStyle(const Style* const style) {
	// TODO Update the style of how this window is drawn
}

void Window::addCallback(Event evt) {
	m_Events.push_back(evt);
}
