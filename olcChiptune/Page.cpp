#include "Page.h"
#include "Beat.h"

Page::Page() : beats{ std::vector<Beat>(PAGE_BEATS) } {}

std::vector<Beat>& Page::getBeats() {
	return beats;
}