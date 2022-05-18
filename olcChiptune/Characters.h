#pragma once

class olcConsoleGameEngine;

class BoxDrawing {
public:
	typedef short ConsoleColor;

	ConsoleColor Black = 0;
	ConsoleColor Blue = 1;
	ConsoleColor Green = 2;
	ConsoleColor Aqua = 3;
	ConsoleColor Red = 4;
	ConsoleColor Purple = 5;
	ConsoleColor Yellow = 6;
	ConsoleColor White = 7;
	ConsoleColor Gray = 8;
	ConsoleColor LightBlue = 9;
	ConsoleColor LightGreen = 10;
	ConsoleColor LightAqua = 11;
	ConsoleColor LightRed = 12;
	ConsoleColor LightPurple = 13;
	ConsoleColor LightYellow = 14;
	ConsoleColor BrightWhite = 15;

	enum class BoxType { Line, Pipe };
	static const int BOXDRAWINGS_START = 9472;

	static const wchar_t LINE_HORIZONTAL = BOXDRAWINGS_START + 0;
	static const wchar_t LINE_VERTICAL = BOXDRAWINGS_START + 2;
	static const wchar_t LINE_TOPLEFT = BOXDRAWINGS_START + 12;
	static const wchar_t LINE_TOPRIGHT = BOXDRAWINGS_START + 16;
	static const wchar_t LINE_BOTLEFT = BOXDRAWINGS_START + 20;
	static const wchar_t LINE_BOTRIGHT = BOXDRAWINGS_START + 24;
	static const wchar_t LINE_MIDLEFT = BOXDRAWINGS_START + 28;
	static const wchar_t LINE_MIDRIGHT = BOXDRAWINGS_START + 36;
	static const wchar_t LINE_TOPMID = BOXDRAWINGS_START + 44;
	static const wchar_t LINE_BOTMID = BOXDRAWINGS_START + 52;
	static const wchar_t LINE_MIDMID = BOXDRAWINGS_START + 52;


	static const wchar_t PIPE_HORIZONTAL = BOXDRAWINGS_START + 80;
	static const wchar_t PIPE_VERTICAL = BOXDRAWINGS_START + 81;
	static const wchar_t PIPE_TOPLEFT = BOXDRAWINGS_START + 84;
	static const wchar_t PIPE_TOPRIGHT = BOXDRAWINGS_START + 87;
	static const wchar_t PIPE_BOTLEFT = BOXDRAWINGS_START + 90;
	static const wchar_t PIPE_BOTRIGHT = BOXDRAWINGS_START + 93;
	static const wchar_t PIPE_MIDLEFT = BOXDRAWINGS_START + 96;
	static const wchar_t PIPE_MIDRIGHT = BOXDRAWINGS_START + 99;
	static const wchar_t PIPE_TOPMID = BOXDRAWINGS_START + 102;
	static const wchar_t PIPE_BOTMID = BOXDRAWINGS_START + 105;
	static const wchar_t PIPE_MIDMID = BOXDRAWINGS_START + 108;

	static void DrawBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, BoxType type = BoxType::Line, short col = 15);

	static void DrawSolidBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, short c = 9608, short col = 15);

};
