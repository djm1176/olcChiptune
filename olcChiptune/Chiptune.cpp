#include <queue>
#include <string>
#include "Chiptune.h"
#include "Frequency.h"
#include "PianoWindow.h"

// Inherited via olcConsoleGameEngine
bool Chiptune::OnUserCreate() {

	//Initialize windows
	Window* pianoWindow = new PianoWindow(0, 0, 64, 24);

	//Add windows to the vector
	m_Windows.push_back(pianoWindow);


	EnableSound();
	currentTune = new Tune();


	//Debugging/Testing
	for (int i = 0; i < 12; i++) currentTune->addPage();

	for (int i = 1; i <= 88; i++)
		currentTune->addNote(i / 16, i % 16, i);

	return true;
}

bool Chiptune::OnUserUpdate(float fElapsedTime) {
	// Update all states and values

	// Handle drawing of windows as necessary
	for (Window* window : m_Windows) {
		window->Render(*this);
	}

	return true;
}

void Chiptune::OnMouseMove(int x, int y) {
	//Reuse Event to carry the UI interaction to a generalized compare
	//TODO We shouldn't reuse: this should be its own class
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnMouseMove, Event::Context::Global, Event::KeyModifiers::None, -1, -1);
	t.mouseX = x;
	t.mouseY = y;
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::OnMouseDown(int index) {
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnMouseDown, Event::Context::Global, Event::KeyModifiers::None, index, -1);
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::OnMouseUp(int index) {
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnMouseUp, Event::Context::Global, Event::KeyModifiers::None, index, -1);
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::OnMouseWheel(int direction) {
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnMouseWheel, Event::Context::Global, Event::KeyModifiers::None, -1, -1);
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	t.mouseWheel = direction;
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::OnKeyDown(int key) {
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnKeyDown, Event::Context::Global, Event::KeyModifiers::None, -1, key);
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::OnKeyUp(int key) {
	Event e(nullptr);
	auto t = Event::Trigger(Event::State::OnKeyUp, Event::Context::Global, Event::KeyModifiers::None, -1, key);
	t.SetKeyModifiers(GetKey(VK_CONTROL).bHeld, GetKey(VK_SHIFT).bHeld, GetKey(VK_MENU).bHeld);
	e.AddTrigger(t);
	ProcessEvent(e);
}

void Chiptune::ProcessEvent(Event evt) {

	//Go over every window, each of its events, and see if its properties match to do a callback
	for (auto*w : m_Windows) {
		for (auto e : w->GetEvents()) {
			for (auto &t2 : evt.GetTriggers()) {
				for (auto &t1 : e.GetTriggers()) {
					//t2 is the users' input, t1 is the trigger we're comparing

					//This context one works as long as there's only these 2 values (Global and Focused)
					if (t2.context == Event::Context::Global && t1.context == Event::Context::Focused) continue;
					if (t2.state != t1.state) continue;
					if (t2.keyModifiers != t1.keyModifiers) continue;
					if (t2.key != t1.key && t1.key != -1) continue;
					if (t2.mouseIndex != t1.mouseIndex && t1.mouseIndex != -1) continue;
					if (t2.mouseWheel != t1.mouseWheel && t1.mouseWheel != 0) continue;

					// Trigger
					e.Invoke(evt);
				}
			}
		}
	}
}

float Chiptune::OnUserSoundSample(int nChannel, double fGlobalTime, float fTimeStep) {
	return 0.0f;
}

int main() {

	Chiptune game;

	game.ConstructConsole(Chiptune::SCREEN_WIDTH, Chiptune::SCREEN_HEIGHT, 7, 15);
	game.Start();

	return 0;
}
