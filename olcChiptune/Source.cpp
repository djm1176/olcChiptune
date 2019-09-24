#include "olcConsoleGameEngine.h"
#include <string>
#include "Note.h"

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

	std::vector<Note *> notes;


	int cursor_x = 0;
	int cursor_y = 0;


	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{

		for (int i = 0; i < 4; i++) {
			notes.push_back(new Note{});
		}

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override
	{


		//Display
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//Draw cursor
		//If over taskbar...
		if (m_mousePosY == 0) {
			DrawLine((m_mousePosX / 9) * 9, 0, (m_mousePosX / 9) * 9 + TASKBAR_NAMES[m_mousePosX / 9].length() - 1, 0, PIXEL_SOLID, COLOR_LTBLUE);
		} else if (m_mousePosX > 8 && m_mousePosX < ScreenWidth() - 1 && m_mousePosY > 2 && m_mousePosY < ScreenHeight() - 1) {
			//Draw inside piano roll
			if (m_mousePosX > 14 && m_mousePosX < 17) {
				//One of the note's pitches
				DrawLine(m_mousePosX - (m_mousePosX + 1) % 2, m_mousePosY, m_mousePosX + m_mousePosX % 2, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
			}
			else if (m_mousePosX > 19 && m_mousePosX < 22) {
				//One of the note's octaves
				DrawLine(m_mousePosX - m_mousePosX % 2, m_mousePosY, m_mousePosX + (m_mousePosX + 1) % 2, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
			}
			else if (m_mousePosX > 24 && m_mousePosX < 28) {
				//One of the note's volumes
				DrawLine(m_mousePosX - (m_mousePosX + 1) % 2, m_mousePosY, 1 + m_mousePosX + m_mousePosX % 2, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
			}
			else if (true) {
				//Everything else as of right now
				Draw(m_mousePosX, m_mousePosY, PIXEL_SOLID, COLOR_GRAY);
			}
		}
		else if (true) {
			//Everything else as of right now
			Draw(m_mousePosX, m_mousePosY, PIXEL_SOLID, COLOR_WHITE);
		}

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

		//Draw notes
		for (int i = 0; i < notes.size(); i++) {
			DrawString(9, i + 6, std::to_wstring(i) + L" .. ");
			DrawString(13, i + 6, L"[" + std::to_wstring(i) + L"]", (m_mousePosX > 14 && m_mousePosX < 17 ? 0x0017 : 0x0007));
			DrawString(18, i + 6, L"[" + notes[i]->GetPitchStr(Flats) + L"]", (m_mousePosX > 19 && m_mousePosX < 22 ? 0x0017 : 0x0007));
			DrawString(23, i + 6, L"[" + notes[i]->GetOctaveStr() + L"]", (m_mousePosX > 24 && m_mousePosX < 28 ? 0x0017 : 0x0007));
		}
			DrawString(9, 11, std::to_wstring(0) + L" .. [" + notes[0]->GetPitchStr(Flats) + L"] [" + notes[0]->GetOctaveStr() + L"] [" + notes[0]->GetVolumeStr() + L"]");

		



		return true;
	}
};


int main() {

	Chiptune game;

	game.ConstructConsole(64, 32, 16, 16);
	game.Start();

	return 0;
}