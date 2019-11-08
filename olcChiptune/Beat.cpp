#include <iostream>
#include "Beat.h"
#include "Note.h"

Beat::Beat() : notes{std::vector<Note>()} {}


bool Beat::addNote(int pitch) {
	//If there's no notes...
	if (notes.size() == 0) {
		Note newNote = Note(pitch);
		notes.push_back(newNote);
		return true;
	}
	else {
		//Create a note if we can
		for (Note n : notes) {
			if (n.getPitch() == pitch) return false;

		}
		//None of the notes are this pitch, so we can make it
		Note newNote = Note(pitch);
		notes.push_back(newNote);
		return true;
	}
}

void Beat::toggleNote(int pitch) {
	for(Note n : notes) {
		if (n.getPitch() == pitch) {
			removeNote(pitch);
			return;
		}
	}

	//Didn't return, so add note
	addNote(pitch);
}

void Beat::removeNote(int pitch) {
	//Remove the note if it exists
	for (int i = 0; i < notes.size(); ++i) {
		if (notes[i].getPitch() == pitch) {
			notes.erase(notes.begin() + i);
		}
	}
}

std::vector<Note>& Beat::getNotes() {
	return notes;
}