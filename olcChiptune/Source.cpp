#include <queue>
#include <string>
#include "olcConsoleGameEngine.h"
#include "Tune.h"
#include "Characters.h"

//Set to 1: The program will only refresh the screen when necesary
//Set to 0: The program will refresh the screen every frame
#define ENABLE_REFRESH_DETECTION 0


class Chiptune : public olcConsoleGameEngine {
public:
	enum WaveType {Sine, Square, Triangle, SawAnalog, SawDigital, Noise};

	static const int SCREEN_WIDTH = 70;
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
	int currentPitchOffset = 1; //TODO: Better name? This is the "bottom pitch" currently visible when scrolling up/down piano roll

	//TDOO: Create a data structure for multiple of these
	float tempo_target = 15.0f / 120.0f;
	float tempo_current = 0.0f;

	bool isPlaying = false;

	bool refreshDisplay = true; //Set this to TRUE if the screen should be redrawn.

	Tune* currentTune;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{

		EnableSound();
		currentTune = new Tune();


		//Debugging/Testing
		for(int i = 0; i < 12; i++) currentTune->addPage();

		//for (int i = 1; i <= 88; i++)
		//	currentTune->addNote(i / 16, i % 16, i);


		

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {

		//Check user input
		if (m_keys[VK_SPACE].bPressed) togglePlayback();

		if (m_keys[VK_UP].bPressed) {
			currentPitchOffset = clamp(currentPitchOffset + 1, 1, 88 - (SCREEN_HEIGHT - 5));
			refreshDisplay = true;
		}
		else if (m_keys[VK_DOWN].bPressed) {
			currentPitchOffset = clamp(currentPitchOffset - 1, 1, 88 - (SCREEN_HEIGHT - 5));
			refreshDisplay = true;
		}

		if (m_mouse[0].bPressed && m_mousePosX > 4 && m_mousePosX < ScreenWidth() - 1 && m_mousePosY > 2 && m_mousePosY < ScreenHeight() - 1) {
			currentTune->toggleNote(currentPage, m_mousePosX - 5, indexToPitch(m_mousePosY, currentPitchOffset, SCREEN_HEIGHT - 4));
		}

		//Behavior

		if (isPlaying) {
			if (tempo_current >= tempo_target) {
				(playhead++);
				refreshDisplay = true; //Playhead moved; redraw necessary
				if (playhead == Page::PAGE_BEATS) {
					playhead = 0;
					currentPage++;
				}
				tempo_current = 0;
			}
			tempo_current += fElapsedTime;
		}


		//Draw graphics
		if (!refreshDisplay) return true; //No need to draw on the screen if nothing changed

#if ENABLE_REFRESH_DETECTION 1
		refreshDisplay = false;
#endif
		
		//Changes were made (refreshDisplay is true) ... Let's redraw the screen...
		//Clear screen
		Fill(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SOLID, 0x000E);

		//Draw Timeline box
		BoxDrawing::DrawBox(*this, 4, 2, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BoxDrawing::BoxType::Pipe, 0x00E0);
		Draw(4, 2, BoxDrawing::PIPE_TOPMID, 0x00E0);
		Draw(4, SCREEN_HEIGHT - 1, BoxDrawing::PIPE_BOTMID, 0x00E0);
		DrawLine(0, 2, 3, 2, BoxDrawing::PIPE_HORIZONTAL, 0x00E0);
		DrawLine(0, SCREEN_HEIGHT - 1, 3, SCREEN_HEIGHT - 1, BoxDrawing::PIPE_HORIZONTAL, 0x00E0);

		for (int i = 0; i < SCREEN_HEIGHT - 4; i++) {
			static const bool WHITE_KEYS[]{1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0};
			//Draw piano roll thing
			int pitch = indexToPitch(i, currentPitchOffset, SCREEN_HEIGHT - 4);
			//DrawLine(0, i + 3, 3, i + 3, PIXEL_SOLID, (WHITE_KEYS[(pitch - 1) % 12] ? 0x000F : 0x00F0));
			//Draw name
			DrawString(0, i + 3, pitchToWstring(pitch), (WHITE_KEYS[(pitch - 1) % 12] ? 0x00F0 : 0x000F));
			//DrawString(9, i + 3, std::to_wstring((pitch + 8) / 12));
			
			
		}
		//Draw horizontal cursor bar
		if (m_mousePosY > 2 && m_mousePosY < ScreenHeight() - 1) DrawLine(5, m_mousePosY, ScreenWidth() - 2, m_mousePosY, PIXEL_QUARTER, 0x00E8);

		//Draw subdivisions
		for (int i = 0; i < Page::PAGE_BEATS / 4; i++) {
			DrawLine(5 + i * 4, 3, 5 + i * 4, ScreenHeight() - 2, i % 2 == 0 ? PIXEL_HALF : PIXEL_QUARTER, 0x00E6);
		}

		//Draw the playhead
		if (isPlaying)
			DrawLine(5 + playhead, 3, 5 + playhead, ScreenHeight() - 2, BoxDrawing::LINE_VERTICAL, 0x00E0);

		//Draw notes
		for(int i = 0; i < Page::PAGE_BEATS; i++)
			for(Note n: currentTune->getPages().at(currentPage).getBeats().at(i).getNotes())
				Draw(5 + i, pitchToIndex(n.getPitch(), currentPitchOffset, SCREEN_HEIGHT - 4), PIXEL_SOLID, 0x0000);

		//Draw info graphics

		//Title
		DrawString(1, 0, L"Title", 0x00E0);
		DrawString(7, 0, currentTune->name, 0x0007);

		//Tempo
		DrawString(1, 1, L"Tempo", 0x00E0);
		DrawString(7, 1, std::to_wstring(currentTune->tempo), 0x0007);

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
		else {
			//Everything that should happen when STOPPED...
			currentPage = 0;


		}
		refreshDisplay = true;
	}

	//Helper functions - TODO: Move to a header file?

	static int indexToPitch(int index, int offset, int height) {
		return 88 - height - index + offset - SCREEN_HEIGHT - 1;
	}

	static int pitchToIndex(int pitch, int offset, int height) {
		return 88 - height - pitch + offset - SCREEN_HEIGHT - 1;
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

	static std::wstring pitchToWstring(int pitch) {
		static std::wstring PITCH_FLATS[]{ L"A ", L"Bb", L"B ", L"C ", L"Db", L"D ", L"Eb", L"E ", L"F ", L"Gb", L"G ", L"Ab" };
		return PITCH_FLATS[(pitch - 1) % 12];
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

	game.ConstructConsole(Chiptune::SCREEN_WIDTH, Chiptune::SCREEN_HEIGHT, 12, 16);
	game.Start();

	return 0;
}
