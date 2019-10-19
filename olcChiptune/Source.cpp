#include "olcConsoleGameEngine.h"
#include <string>
#include "Page.h"
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

	Page* myPage;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{
		myPage = new Page();
		myPage->getBeat(0).addNote(40);
		
		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {

		//Draw a test box or two :)

		BoxDrawing::DrawBox(*this, 10, 10, 30, 40, BoxDrawing::BoxType::Line, 0x000F);
		BoxDrawing::DrawBox(*this, 50, 10, 70, 40, BoxDrawing::BoxType::Pipe, 0x000F);

		return true;
	}
};


int main() {

	Chiptune game;

	game.ConstructConsole(128, 64, 8, 8);
	game.Start();

	return 0;
}