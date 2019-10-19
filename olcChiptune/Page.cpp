#include "Beat.h"
#include "Page.h"
#include <cassert>

Page::Page() : beats{ std::vector<Beat>(PAGE_BEATS) } {
}

Beat& Page::getBeat (int time) {
	assert(time > -1 && time < PAGE_BEATS);
	return beats[time];
}