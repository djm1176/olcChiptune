#pragma once
#include "olcConsoleGameEngine.h"
struct Style {
	Style();

	static Style& Default();

	int borderWidth;
	bool dropShadow ;

	int foregroundColor;
	int backgroundColor;
	int borderColor;
	int accentColor;
	int highlightColor;
	int disabledColor;

};

extern Style DefaultGlobalStyle;