#include "Style.h"

Style::Style() : borderWidth{ 1 }, dropShadow{ false },
foregroundColor{ FG_WHITE }, backgroundColor{ BG_DARK_RED }, borderColor{ FG_BLACK },
accentColor{ FG_DARK_RED }, highlightColor{ FG_CYAN }, disabledColor{ FG_GREY } {}

Style& Style::Default() { static Style _s; return _s; }