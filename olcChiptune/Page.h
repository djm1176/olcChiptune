#pragma once

#include "Beat.h"
#include <vector>

class Page {
public:
	static const int PAGE_BEATS = 64;
	
	Page();
	std::vector<Beat>& getBeats();


private:
	std::vector<Beat> beats;

};
