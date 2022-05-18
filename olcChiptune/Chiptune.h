#pragma once
#include "olcConsoleGameEngine.h"
#include "Tune.h"
#include "Window.h"

class Chiptune : public olcConsoleGameEngine {
public:
	static const int SCREEN_WIDTH = 192;
	static const int SCREEN_HEIGHT = 48;

	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;
	virtual float OnUserSoundSample(int nChannel, double fGlobalTime, float fTimeStep) override;

	virtual void OnMouseMove(int x, int y) override;
	virtual void OnMouseDown(int index) override;
	virtual void OnMouseUp(int index) override;
	virtual void OnMouseWheel(int direction) override;
	virtual void OnKeyDown(int key) override;
	virtual void OnKeyUp(int key) override;


protected:

	//Process a UI event (mouse/keyboard)
	//TODO handle this in a UI manager
	void ProcessEvent(Event e);

	struct PlayState {
		int m_beatOffset = 0; // The current beat, by the smallest subdivision
		int m_pageOffset = 0;
		bool isPlaying = false;
	};

	PlayState playstate;
	Tune* currentTune;
	
	std::vector<Window*> m_Windows;

};
