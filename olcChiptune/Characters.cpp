#include "Characters.h"
#include "olcConsoleGameEngine.h"

void BoxDrawing::DrawBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, BoxType type, short col) {
	//Draw 4 corners
	targetGraphic.Draw(x1, y1, (type == BoxType::Line ? LINE_TOPLEFT : PIPE_TOPLEFT), col);
	targetGraphic.Draw(x2, y1, (type == BoxType::Line ? LINE_TOPRIGHT : PIPE_TOPRIGHT), col);
	targetGraphic.Draw(x1, y2, (type == BoxType::Line ? LINE_BOTLEFT : PIPE_BOTLEFT), col);
	targetGraphic.Draw(x2, y2, (type == BoxType::Line ? LINE_BOTRIGHT : PIPE_BOTRIGHT), col);

	//Draw top/bottom sides
	for (int i = x1 + 1; i < x2; i++) {
		targetGraphic.Draw(i, y1, (type == BoxType::Line ? LINE_HORIZONTAL : PIPE_HORIZONTAL), col);
		targetGraphic.Draw(i, y2, (type == BoxType::Line ? LINE_HORIZONTAL : PIPE_HORIZONTAL), col);
	}

	//Draw left/right sides
	for (int i = y1 + 1; i < y2; i++) {
		targetGraphic.Draw(x1, i, (type == BoxType::Line ? LINE_VERTICAL : PIPE_VERTICAL), col);
		targetGraphic.Draw(x2, i, (type == BoxType::Line ? LINE_VERTICAL : PIPE_VERTICAL), col);
	}
}

void BoxDrawing::DrawSolidBox(olcConsoleGameEngine& targetGraphic, int x1, int y1, int x2, int y2, short c, short col) {
	targetGraphic.DrawLine(x1, y1, x2, y1, c, col);
	targetGraphic.DrawLine(x1, y2, x2, y2, c, col);
	targetGraphic.DrawLine(x1, y1, x1, y2, c, col);
	targetGraphic.DrawLine(x2, y1, x2, y2, c, col);
}