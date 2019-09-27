#ifndef OLCBEAT_H
#define OLCBEAT_H

#include "Note.h"
#include <vector>

class Beat {
public:
	Beat();
	~Beat();
	Beat(const Note& other);
	Beat(Beat&& other);
	Beat& operator=(const Beat& rhs);
	Beat& operator=(Beat&& rhs);

	Note getNote(int index);
	bool addNote(int pitch);
	bool removeNote(int pitch);

private:
	std::vector<Note*> *notes;


};

#endif