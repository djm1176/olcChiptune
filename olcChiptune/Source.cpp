#include "olcConsoleGameEngine.h"
#include <string>

class Chiptune : public olcConsoleGameEngine {

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

	int notes[64][13];
	int playhead = 0;

	int cursor_x = 0;
	int cursor_y = 0;


	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{
		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override
	{


		//Display
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//Draw Taskbar buttons
		for (int i = 0; i < TASKBAR_COUNT; i++) {
			DrawString(i * 9, 0, TASKBAR_NAMES[i]);
		}
		olcConsoleGameEngine::DrawLine(0, 2, ScreenWidth() - 1, 2, PIXEL_SOLID, 2);

		//Draw timeline
		DrawLine(8, 3, 8, ScreenHeight() - 2, PIXEL_SOLID, 2);
		DrawLine(0, 3, 0, ScreenHeight() - 2, PIXEL_SOLID, 2);
		DrawLine(0, ScreenHeight() - 1, ScreenWidth(), ScreenHeight() - 1, PIXEL_SOLID, 2);
		DrawLine(ScreenWidth() - 1, 3, ScreenWidth() - 1, ScreenHeight() - 2, PIXEL_SOLID, 2);

		//Draw cursor
		//If over taskbar...
		if (m_mousePosY == 0) {
			DrawLine((m_mousePosX / 9) * 9, 0, (m_mousePosX / 9) * 9 + TASKBAR_NAMES[m_mousePosX / 9].length() - 1, 0, PIXEL_SOLID, COLOR_LTBLUE);
		} else if (m_mousePosX > 8 && m_mousePosX < ScreenWidth() - 1 && m_mousePosY > 2 && m_mousePosY < ScreenHeight() - 1) {
			//Draw inside piano roll
			Draw(m_mousePosX, m_mousePosY, PIXEL_SOLID, COLOR_GRAY);
		}
		else if (true) {
			//Everything else as of right now
			//Draw(m_mousePosX, m_mousePosY, PIXEL_SOLID, COLOR_LTRED);
		}

		//Draw notes
		//for (int x = 0; x < 32; x++) {
			//for (int y = 0; y < 13; y++) {
				//Draw note at (x, y) of the array, looping if necessary
				
			//}
		//}

		return true;
	}
};


int main() {

	Chiptune game;

	game.ConstructConsole(64, 32, 16, 16);
	game.Start();

	return 0;
}