#ifndef OLCPAGE_H
#define OLCPAGE_H

#include "Beat.h"
#include <vector>

class Page {
public:
	static const int PAGE_BEATS = 64; 
	
	Page();
	Beat& getBeat(int time);


private:
	std::vector<Beat> beats;

};



#endif