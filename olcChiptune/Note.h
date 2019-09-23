#ifndef NOTE_H
#define NOTE_H


#include <string>

class Note {
	virtual ~Note() = 0;


public:
	int GetVolume();
	int GetPitch();
	std::wstring GetPitchStr();

private:
	int* m_Volume;
	int* m_Pitch;


};

#endif