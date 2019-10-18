#include "Beat.h"
#include "Page.h"

Page::Page() : beats{ Beat[PAGE_BEATS] } {
}

Beat& Page::getBeat (int time) {
	if (time < 0 || time >= PAGE_BEATS) {
		return beats[time];
	}
}