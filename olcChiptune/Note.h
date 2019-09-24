#ifndef NOTE_H
#define NOTE_H


#include <string>

class Note {

public:
	int GetVolume();
	int GetPitch();
	std::wstring GetPitchStr();
	explicit Note(int volume = 100, int pitch = 0);
	~Note();
	Note(const Note& other);
	Note(Note&& other);
	Note& operator=(const Note& rhs);
	Note& operator=(Note&& rhs);

private:
	int *m_Volume;
	int *m_Pitch;


};

#endif