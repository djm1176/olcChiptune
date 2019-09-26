#include "olcConsoleGameEngine.h"
#include <string>
#include "Note.h"

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

	std::vector<Note *> notes;


	int cursor_x = 0;
	int cursor_y = 0;
	int playhead = 0;

	//TDOO: Create a data structure for multiple of these
	float wait_target = 1.0f / 30.0f; //30 fps target
	float wait_counter = 0.0f; //Don't do anything when less than wait_target


	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{

		for (int i = 0; i < 64; i++) {
			notes.push_back(new Note{});
		}

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override
	{
		
		if (m_keys[VK_NEXT].bHeld && wait_counter >= wait_target) {
			OffsetPlayhead(1);
			wait_counter = 0.0f;
		}
		else if (m_keys[VK_PRIOR].bHeld && wait_counter >= wait_target) {
			OffsetPlayhead(-1);
			wait_counter = 0.0f;
		}

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
				DrawLine(15, m_mousePosY, 16, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
			}
			else if (m_mousePosX > 19 && m_mousePosX < 22) {
				//One of the note's octaves
				DrawLine(20, m_mousePosY, 21, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
			}
			else if (m_mousePosX > 24 && m_mousePosX < 28) {
				//One of the note's volumes
				DrawLine(25, m_mousePosY, 27, m_mousePosY, PIXEL_SOLID, COLOR_BLUE);
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

		DrawString(9, 3, L"Pos  Pit  Oct  Vol");
		//Draw notes
		for (int i = playhead; i < playhead + min(notes.size() - playhead, ScreenHeight() - 9); i++) {
			DrawString(9, i - playhead + 4, PadInt(i, 3));
			DrawString(14, i - playhead + 4, L"[" + notes[i]->GetPitchStr(Flats) + L"]", (m_mousePosY == i + 4 && m_mousePosX > 14 && m_mousePosX < 17 ? 0x0017 : 0x0007));
			DrawString(19, i - playhead + 4, L"[" + notes[i]->GetOctaveStr() + L"]", (m_mousePosY == i + 4 && m_mousePosX > 19 && m_mousePosX < 22 ? 0x0017 : 0x0007));
			DrawString(24, i - playhead + 4, L"[" + notes[i]->GetVolumeStr() + L"]", (m_mousePosY == i + 4 && m_mousePosX > 24 && m_mousePosX < 28 ? 0x0017 : 0x0007));
		}

		wait_counter += fElapsedTime;

		return true;
	}

	//This is the ONLY way that playhead should be modified
	bool OffsetPlayhead(int amount) {
		if (playhead + amount < 0) return false;
		if (playhead + amount > notes.size() - 1) return false;
		playhead += amount;
	}

	static std::wstring PadInt(int num, int placesCount) {
		switch (placesCount) {
		case 1:
			if (num < 10) return std::to_wstring(num);
			else return L"9";
			break;
		case 2:
			if (num < 10) return L"0" + std::to_wstring(num);
			else if (num < 100) return std::to_wstring(num);
			else return L"99";
			break;
		case 3:
			if (num < 10) return L"00" + std::to_wstring(num);
			else if (num < 100) return L"0" + std::to_wstring(num);
			else if (num < 1000) return std::to_wstring(num);
			else return L"999";
			break;
		default:
			return std::to_wstring(num);
		}
	}
};


int main() {

	Chiptune game;

	game.ConstructConsole(64, 32, 16, 16);
	game.Start();

	return 0;
}