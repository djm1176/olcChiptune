#include <queue>
#include <string>
#include "olcConsoleGameEngine.h"
#include "Tune.h"
#include "Characters.h"

class Chiptune : public olcConsoleGameEngine {
public:
	enum WaveType {Sine, Square, Triangle, SawAnalog, SawDigital, Noise};

	static const int SCREEN_WIDTH = 46;
	static const int SCREEN_HEIGHT = 32;

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

protected:
	int cursor_x = 0;
	int cursor_y = 0;

	//TODO: This could probably be a struct
	int playhead = 0; //The x-position of the current beat that is playing
	int currentPage = 0;
	int currentPitchOffset = 0; //TODO: Better name? This is the "bottom pitch" currently visible when scrolling up/down piano roll

	//TDOO: Create a data structure for multiple of these
	float tempo_target = 60.0f / 120.0f;
	float tempo_current = 0.0f;

	bool isPlaying = false;

	Tune* currentTune;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{

		EnableSound();
		currentTune = new Tune();


		//Debugging/Testing
		for(int i = 0; i < 12; i++) currentTune->addPage();

		for (int i = 1; i <= 88; i++)
			currentTune->addNote(i / 16, i % 16, i);


		

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {

		//Check user input
		if (m_keys[VK_SPACE].bPressed) togglePlayback();

		if (m_keys[VK_UP].bPressed) currentPitchOffset = clamp(currentPitchOffset + 1, 1, 7);
		else if (m_keys[VK_DOWN].bPressed) currentPitchOffset = clamp(currentPitchOffset - 1, 1, 7);

		//Behavior

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


		//Draw graphics
		//Clear screen
		
		Fill(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SOLID, 0x000E);
		
		//Draw Timeline box
		BoxDrawing::DrawBox(*this, SCREEN_WIDTH - (8 * 5 + 2), 2, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BoxDrawing::BoxType::Pipe, 0x00E0);
		Draw(4, 2, BoxDrawing::PIPE_TOPMID, 0x00E0);
		DrawLine(0, 2, 3, 2, BoxDrawing::PIPE_HORIZONTAL, 0x00E0);

		DrawString(5, SCREEN_HEIGHT - 2, std::to_wstring(screenSpaceToPitch(SCREEN_HEIGHT - 2, currentPitchOffset, SCREEN_HEIGHT)));

		//Draw debug cursor
		Draw(m_mousePosX, m_mousePosY, PIXEL_SOLID, 10);


		return true;
	}

	void togglePlayback() {
		isPlaying = !isPlaying;
		if (isPlaying) {
			playhead = 0;
			tempo_current = 0.0f;
		}
	}

	//Helper functions - TODO: Move to a header file?

	static int screenSpaceToPitch(int yCoord, int offset, int screenHeight) {
		return yCoord + offset;
	}

	static int clamp(int value, int min, int max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	static float pitchToSin(int pitch, float fGlobalTime, WaveType waveType) {
		if (waveType == Noise) return sinf(rand());
		static const float freqs[]{27.500, 29.1353, 30.8677, 32.7032, 34.6479, 36.7081, 38.8909, 41.2035, 43.6536, 46.2493, 48.9995, 51.9130};
		static const float PI = 3.14159f;
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

		switch (waveType) {
		case Sine:
			return sinf(freq * 2.0 * PI * fGlobalTime); //Sine wave
		case Square:
			return sinf(freq * 2.0 * PI * fGlobalTime) > 0 ? 1.0 : -1.0; //Square wave
		case SawDigital:
			return (2.0 / PI) * (freq * PI * fmod(fGlobalTime, 1.0 / freq) - (PI / 2.0)); //Sawtooth digital
		case SawAnalog:
			//TODO
		default:
			return 0.0f;
		}

	}

	virtual float onUserSoundSample(int nChannel, float fGlobalTime, float fTimeStep) {
		if (!isPlaying) return 0.0f;
		float final = 0.0f;
		float amplitude = 0.1f;

		//Get notes from current Beat
		for (Note n : currentTune->getPages().at(currentPage).getBeats().at(playhead).getNotes()) {
			final += pitchToSin(n.getPitch(), fGlobalTime, Square) * amplitude;
		}

		return final;
	}
};

int main() {

	Chiptune game;

	game.ConstructConsole(Chiptune::SCREEN_WIDTH, Chiptune::SCREEN_HEIGHT, 16, 16);
	game.Start();

	return 0;
}
