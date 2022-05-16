#include <queue>
#include <string>
#include "Chiptune.h"
#include "Frequency.h"
#include "PianoWindow.h"


// Inherited via olcConsoleGameEngine
bool Chiptune::OnUserCreate() {

	//Initialize windows
	Window* pianoWindow = new PianoWindow(0, 0, 10, 16);

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
		window->Draw(this);
	}

	return true;
}

void Chiptune::OnMouseMove(int x, int y) {

}

void Chiptune::OnMouseDown(int index) {

}

void Chiptune::OnMouseUp(int index) {

}

void Chiptune::OnKeyDown(int key) {

}

void Chiptune::OnKeyUp(int key) {

}

float Chiptune::OnUserSoundSample(int nChannel, double fGlobalTime, float fTimeStep) {
	return 0.0f;
}

int main() {

	Chiptune game;

	game.ConstructConsole(Chiptune::SCREEN_WIDTH, Chiptune::SCREEN_HEIGHT, 10, 14);
	game.Start();

	return 0;
}
