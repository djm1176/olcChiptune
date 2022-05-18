#pragma once

#include "Window.h" //Required for inheritance

#include <string>

class Chiptune;

class DebugWindow :
    public Window {

public:
	DebugWindow(int x, int y, int w, int h);

	void Log(const std::string& message);
	void Log(const std::wstring& message);

	void Draw(Chiptune& chiptune) override;

	~DebugWindow();

private:
	std::wstring* stack;
	int first, len;

};
