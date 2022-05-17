#include "Window.h"
#include "olcConsoleGameEngine.h"
#include "Chiptune.h"

Window::Window(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

void Window::Draw(Chiptune* chiptunePtr) {
	chiptunePtr->Fill(x, y, x + w, y + h);
}

void Window::OnMouseDown(int index) {
	//Create a fake event trigger to pass it off to comparison

}

void Window::OnMouseUp(int index) {
	//Create a fake event trigger to pass it off to comparison

}

void Window::OnMouseMove(int x, int y) {
	//Create a fake event trigger to pass it off to comparison

}

void Window::OnKeyDown(int key) {
	//Create a fake event trigger to pass it off to comparison

}

void Window::OnKeyUp(int key) {
	//Create a fake event trigger to pass it off to comparison

}

void Window::setStyle(const Style* const style) {
	// TODO Update the style of how this window is drawn

}

void Window::addCallback(Event evt) {
	m_Events.push_back(evt);
}

std::tuple<int, int, int, int> Window::GetRect() {
	return std::tuple<int, int, int, int>(x, y, w, h);
}
