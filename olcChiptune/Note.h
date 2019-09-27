#ifndef NOTE_H
#define NOTE_H


#include <string>

static std::wstring PITCH_FLATS[]{ L"A    ", L"Bb/A#", L"B    ", L"C    ", L"Db/C#", L"D    ", L"Eb/D#", L"E    ", L"F    ", L"Gb/F#", L"G    ", L"Ab/G#" };
static int MAX_PITCH = 88;

enum Accidentals { Flats, Sharps };

class Note {

public:
	int GetVolume();
	int GetPitch();
	int GetOctave();
	std::wstring GetVolumeStr();
	std::wstring GetPitchStr(Accidentals accidentals);
	std::wstring GetOctaveStr();

	static int GetOctave(int pitch);

	void OffsetPitch(int amount);

	explicit Note(int volume = 0, int pitch = 1);
	~Note();
	Note(const Note& other);
	Note(Note&& other);
	Note& operator=(const Note& rhs);
	Note& operator=(Note&& rhs);

private:
	int *m_Volume;
	int *m_Pitch;

	bool SetPitch(int amount);
	bool SetVolume(int amount);
	bool SetOctave(int amount);
	int GetOctavePitch();

};

#endif