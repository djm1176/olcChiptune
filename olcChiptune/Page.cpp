#include "Beat.h"
#include "Page.h"
#include <cassert>

Page::Page() : beats{ std::vector<Beat>(PAGE_BEATS) } {
}

std::vector<Beat>& Page::getBeats() {
	return beats;
}