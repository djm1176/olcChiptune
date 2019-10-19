#include "olcConsoleGameEngine.h"
#include <string>
#include "Tune.h"
#include "Characters.h"

class Chiptune : public olcConsoleGameEngine {

	//std::wstring PadInt(int num, int placesCount);
	//bool OffsetPlayhead(int amount);

	static const int TASKBAR_COUNT = 4;
	std::wstring TASKBAR_NAMES[TASKBAR_COUNT]{L"File", L"Edit", L"Project", L"Help"};
	
	static const int COLOR_BLACK =		0;
	static const int COLOR_BLUE =		1;
	static const int COLOR_GREEN =		2;
	static const int COLOR_AQUA =		3;
	static const int COLOR_RED =		4;
	static const int COLOR_PURPLE =		5;
	static const int COLOR_YELLOW =		6;
	static const int COLOR_WHITE =		7;
	static const int COLOR_GRAY =		8;
	static const int COLOR_LTBLUE =		9;
	static const int COLOR_LTGREEN =	10;
	static const int COLOR_LTAQUA =		11;
	static const int COLOR_LTRED =		12;
	static const int COLOR_LTPURPLE =	13;
	static const int COLOR_LTYELLOW =	14;
	static const int COLOR_BTWHITE =	15;

	int cursor_x = 0;
	int cursor_y = 0;
	int playhead = 0;

	//TDOO: Create a data structure for multiple of these
	float wait_target = 1.0f / 30.0f; //30 fps target
	float wait_counter = 0.0f; //Don't do anything when less than wait_target

	Tune* tune;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{
		tune = new Tune();
		tune->getPages().at(0).getBeats().at(0).addNote(10);
		
		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {

		//Draw all the notes that can be drawn on screen
		for (Page page : tune->getPages()) {
			for (int beat = 0; beat < page.getBeats().size(); beat++) {
				for (Note note : page.getBeats().at(beat).getNotes()) {
					Draw(beat, note.getPitch(), PIXEL_SOLID, 0x000E);
				}
			}
		}

		return true;
	}
};


int main() {

	Chiptune game;

	game.ConstructConsole(64, 32, 16, 16);
	game.Start();

	return 0;
}