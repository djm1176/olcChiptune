#include "olcConsoleGameEngine.h"
#include <string>

class Demo : public olcConsoleGameEngine {

	float fTarget = 1.0f / 30.0f;
	float fCurrent = 0.0f;

	int currentChar = 0;

	// Inherited via olcConsoleGameEngine
	virtual bool OnUserCreate() override
	{
		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override
	{
		if (m_keys[VK_UP].bHeld && fCurrent >= fTarget) {
			fCurrent = 0.0f;
			currentChar++;
		}
		else if (m_keys[VK_DOWN].bHeld && fCurrent >= fTarget) {
			fCurrent = 0.0f;
			currentChar--;
		}

		for (int i = 0; i < ScreenHeight(); i++) {
			DrawString(4, i, std::to_wstring(static_cast<wchar_t>(i)));
		}


		fCurrent += fElapsedTime;

		return true;
	}
};

int main() {
	Demo demo;
	if(demo.ConstructConsole(64, 64, 16, 12))
		demo.Start();


}