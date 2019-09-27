#ifndef OLCPAGE_H
#define OLCPAGE_H

#include "Note.h"
#include <vector>

class Page {
public:
	~Page();
	std::vector<Note*> getBeat(int index);



private:
	std::vector<Note*> beats[32];


};



#endif