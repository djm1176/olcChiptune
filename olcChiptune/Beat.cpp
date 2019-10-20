#include <iostream>
#include "Beat.h"
#include "Note.h"

Beat::Beat() : notes{std::vector<Note>()} {}

Note aNote;

bool Beat::addNote(int pitch) {
	//If there's no notes...
	if (notes.size() == 0) {
		Note newNote = Note(pitch);
		notes.push_back(newNote);
		aNote = newNote;
		return true;
	}
	else {
		//Create a note if we can
		for (Note n : notes) {
			if (n.getPitch() == pitch) return false;
			else {
				Note newNote = Note(pitch);
				notes.push_back(newNote);
				return true;
			}
		}
	}
}

void Beat::removeNote(int pitch) {
	//Remove the note if it exists
	for (int i = 0; i < notes.size(); ++i) {
		if (notes[i].getPitch() == pitch) {
			notes.erase(notes.begin() + i);
		}
	}
}

const std::vector<Note>& Beat::getNotes() {
	return notes;
}