#include "Window.h"
#include "Style.h"
#include "Event.h"
#include "Chiptune.h"
#include "Characters.h"

Window::Window(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h }, m_Style{ Style::Default() } {}

void Window::Draw(Chiptune& chiptune) {
	chiptune.Fill(x, y, x + w, y + h);
}

//void Window::OnMouseDown(int index) {
//	//Create a fake event trigger to pass it off to comparison
//
//}
//
//void Window::OnMouseUp(int index) {
//	//Create a fake event trigger to pass it off to comparison
//
//}
//
//void Window::OnMouseMove(int x, int y) {
//	//Create a fake event trigger to pass it off to comparison
//
//}
//
//void Window::OnKeyDown(int key) {
//	//Create a fake event trigger to pass it off to comparison
//
//}
//
//void Window::OnKeyUp(int key) {
//	//Create a fake event trigger to pass it off to comparison
//
//}

void Window::SetStyle(Style style) {
	// TODO Update the style of how this window is drawn
	m_Style = style;
}

void Window::AddCallback(Event evt) {
	m_Events.push_back(evt);
}

bool Window::GetRect(int& x, int& y, int& w, int& h) const {
	x = this->x + 1;
	y = this->y + 1;
	w = this->w - 2;
	h = this->h - 2;

	return true;
}

void Window::BaseDraw(Chiptune &chiptune) {
	//TODO Any shading/highlighting when the user hovers over? Disabling of the window? Title?
	//Render a box
	BoxDrawing::DrawBox(chiptune, x, y, x + w - 1, y + h - 1, BoxDrawing::BoxType::Pipe, m_Style.borderColor | m_Style.backgroundColor);
	chiptune.Fill(x + 1, y + 1, x + w, x + h, PIXEL_SOLID, FG_DARK_GREY | BG_DARK_GREY);

}

const std::vector<Event> Window::GetEvents() {
	return m_Events;
}

void Window::Render(Chiptune& chiptune) {
	BaseDraw(chiptune); //Enforce base class Window drawings happen first
	Draw(chiptune); //Perform user draws
}
