#pragma once

#include "olcConsoleGameEngine.h"

namespace BoxDrawing {
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

	enum BoxType { Line, Pipe };
	const int BOXDRAWINGS_START = 9472;

	const wchar_t LINE_HORIZONTAL = BOXDRAWINGS_START + 0;
	const wchar_t LINE_VERTICAL = BOXDRAWINGS_START + 2;
	const wchar_t LINE_TOPLEFT = BOXDRAWINGS_START + 12;
	const wchar_t LINE_TOPRIGHT = BOXDRAWINGS_START + 16;
	const wchar_t LINE_BOTLEFT = BOXDRAWINGS_START + 20;
	const wchar_t LINE_BOTRIGHT = BOXDRAWINGS_START + 24;
	const wchar_t LINE_MIDLEFT = BOXDRAWINGS_START + 28;
	const wchar_t LINE_MIDRIGHT = BOXDRAWINGS_START + 36;
	const wchar_t LINE_TOPMID = BOXDRAWINGS_START + 44;
	const wchar_t LINE_BOTMID = BOXDRAWINGS_START + 52;
	const wchar_t LINE_MIDMID = BOXDRAWINGS_START + 52;


	const wchar_t PIPE_HORIZONTAL = BOXDRAWINGS_START + 80;
	const wchar_t PIPE_VERTICAL = BOXDRAWINGS_START + 81;
	const wchar_t PIPE_TOPLEFT = BOXDRAWINGS_START + 84;
	const wchar_t PIPE_TOPRIGHT = BOXDRAWINGS_START + 87;
	const wchar_t PIPE_BOTLEFT = BOXDRAWINGS_START + 90;
	const wchar_t PIPE_BOTRIGHT = BOXDRAWINGS_START + 93;
	const wchar_t PIPE_MIDLEFT = BOXDRAWINGS_START + 96;
	const wchar_t PIPE_MIDRIGHT = BOXDRAWINGS_START + 99;
	const wchar_t PIPE_TOPMID = BOXDRAWINGS_START + 102;
	const wchar_t PIPE_BOTMID = BOXDRAWINGS_START + 105;
	const wchar_t PIPE_MIDMID = BOXDRAWINGS_START + 108;

	void DrawBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, BoxType type = Line, short col = 15) {
		//Draw 4 corners
		targetGraphic.Draw(x1, y1, (type == Line ? LINE_TOPLEFT : PIPE_TOPLEFT), col);
		targetGraphic.Draw(x2, y1, (type == Line ? LINE_TOPRIGHT : PIPE_TOPRIGHT), col);
		targetGraphic.Draw(x1, y2, (type == Line ? LINE_BOTLEFT : PIPE_BOTLEFT), col);
		targetGraphic.Draw(x2, y2, (type == Line ? LINE_BOTRIGHT : PIPE_BOTRIGHT), col);

		//Draw top/bottom sides
		for (int i = x1 + 1; i < x2; i++) {
			targetGraphic.Draw(i, y1, (type == Line ? LINE_HORIZONTAL : PIPE_HORIZONTAL), col);
			targetGraphic.Draw(i, y2, (type == Line ? LINE_HORIZONTAL : PIPE_HORIZONTAL), col);
		}

		//Draw left/right sides
		for (int i = y1 + 1; i < y2; i++) {
			targetGraphic.Draw(x1, i, (type == Line ? LINE_VERTICAL : PIPE_VERTICAL), col);
			targetGraphic.Draw(x2, i, (type == Line ? LINE_VERTICAL : PIPE_VERTICAL), col);
		}
	}

	void DrawSolidBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, short c = 9608, short col = 15) {
		targetGraphic.DrawLine(x1, y1, x2, y1, c, col);
		targetGraphic.DrawLine(x1, y2, x2, y2, c, col);
		targetGraphic.DrawLine(x1, y1, x1, y2, c, col);
		targetGraphic.DrawLine(x2, y1, x2, y2, c, col);
	}

	short ToColor(ConsoleColor foreground, ConsoleColor background) {
		return (foreground << 1) + background;
	}



};
