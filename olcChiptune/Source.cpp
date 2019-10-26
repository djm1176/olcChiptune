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

	//TODO: This could probably be a struct
	int playhead = 0;
	int currentPage = 0;

	//TDOO: Create a data structure for multiple of these
	float tempo_target = 60.0f / 120.0f;
	float tempo_current = 0.0f;

	bool isPlaying = false;

	Tune* myTune;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{
		myTune = new Tune();
		for(int i = 0; i < 12; i++) myTune->addPage();

		for (int i = 1; i <= 88; i++)
			myTune->addNote(i / 16, i % 16, i);


		EnableSound();

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {
		if (m_keys[VK_SPACE].bPressed) togglePlayback();

		if (isPlaying) {
			if (tempo_current >= tempo_target) {
				(playhead++);
				if (playhead == 16) {
					playhead = 0;
					currentPage++;
				}
				tempo_current = 0;
			}
			tempo_current += fElapsedTime;
		}


		return true;
	}

	void togglePlayback() {
		isPlaying = !isPlaying;
		if (isPlaying) {
			playhead = 0;
			tempo_current = 0.0f;
		}
	}

	static float pitchToSin(int pitch, float fGlobalTime) {
		static const float freqs[]{27.500, 29.1353, 30.8677, 32.7032, 34.6479, 36.7081, 38.8909, 41.2035, 43.6536, 46.2493, 48.9995, 51.9130};
		//TODO: Which is faster: Calculate frequency per-frame or lookup table?
		float baseFreq = freqs[(pitch - 1) % 12];
		int octave = (pitch - 1) / 12;
		//Final frequency is the base frequency * 2^n, where n = octave
		//Bitwise shifting works like this:
		//1 << 1 = 00000001 = 1
		//1 << 2 = 00000010 = 2
		//1 << 3 = 00000100 = 4
		//1 << 4 = 00001000 = 8 etc...
		float freq = baseFreq * (1 << octave);

		return sinf(freq * 2.0 * 3.14159f * fGlobalTime) > 0 ? 1.0 : -1.0;
		//return sinf(freq * 2.0 * 3.14159f * fGlobalTime);

	}

	virtual float onUserSoundSample(int nChannel, float fGlobalTime, float fTimeStep) {
		if (!isPlaying) return 0.0f;
		float final = 0.0f;
		float amplitude = 0.1f;

		//Get notes from current Beat
		for (Note n : myTune->getPages().at(currentPage).getBeats().at(playhead).getNotes()) {
			final += pitchToSin(n.getPitch(), fGlobalTime) * amplitude;
		}

		return final;
	}
};

int main() {

	Chiptune game;

	game.ConstructConsole(64, 32, 16, 16);
	game.Start();

	return 0;
}
