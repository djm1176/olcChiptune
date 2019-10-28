#ifndef OLCPAGE_H
#define OLCPAGE_H

#include "Beat.h"
#include <vector>

class Page {
public:
	static const int PAGE_BEATS = 32;
	
	Page();
	std::vector<Beat>& getBeats();


private:
	std::vector<Beat> beats;

};



#endif