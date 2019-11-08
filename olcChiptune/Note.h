#ifndef NOTE_H
#define NOTE_H

#include <string>


enum Accidentals { Flats, Sharps };

class Note {

public:
	const static int MAX_PITCH = 88;

	int getPitch();
	explicit Note(int pitch = 1);
	//~Note();
	//Note(const Note& other);
	//Note(Note&& other);
	//Note& operator=(const Note& rhs);
	//Note& operator=(Note&& rhs);

private:
	int m_Pitch;
};

#endif