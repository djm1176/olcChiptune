#ifndef NOTE_H
#define NOTE_H

#include <string>

static std::wstring PITCH_FLATS[]{ L"A    ", L"Bb/A#", L"B    ", L"C    ", L"Db/C#", L"D    ", L"Eb/D#", L"E    ", L"F    ", L"Gb/F#", L"G    ", L"Ab/G#" };

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