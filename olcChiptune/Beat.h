#pragma once

#include "Note.h"
#include <vector>

class Beat {
public:
	Beat();
	
	std::vector<Note> &getNotes(); //TODO: If adding more properties, we need to return by non-const reference so we can modify
	bool addNote(int pitch);
	void toggleNote(int pitch);
	void removeNote(int pitch);

private:
	std::vector<Note> notes;

};
