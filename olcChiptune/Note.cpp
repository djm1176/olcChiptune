#include "Note.h"

//#########################
//Constructors/Destructor
//#########################

//Default constructor
Note::Note(int volume, int pitch) : m_Volume{ new int{volume} }, m_Pitch{ new int{pitch} } { }

//Default destructor
Note::~Note() {
	delete m_Volume;
	delete m_Pitch;
}

//Copy Constructor
Note::Note(const Note& other) : m_Volume{ new int{*other.m_Volume} }, m_Pitch{ new int{*other.m_Pitch} } { }

//Move Constructor
Note::Note(Note&& other) : m_Volume{other.m_Volume}, m_Pitch{other.m_Pitch} {
	other.m_Volume = nullptr;
	other.m_Pitch = nullptr;
}

//Copy Assignment
Note &Note::operator=(const Note& rhs) {
	if (this != &rhs) {
		*m_Volume = *rhs.m_Volume;
		*m_Pitch = *rhs.m_Pitch;
	}
	return *this;
}

//Move Assignment
Note &Note::operator=(Note&& rhs) {
	std::swap(m_Volume, rhs.m_Volume);
	std::swap(m_Pitch, rhs.m_Pitch);
	return *this;
}

int Note::GetVolume() {
	return *m_Volume;
}

int Note::GetPitch() {
	return *m_Pitch;
}

int Note::GetOctave() {
	return 1 + ((*m_Pitch - 3) / 12);
}

int Note::GetOctavePitch() {
	return *m_Pitch % 12;
}

std::wstring Note::GetPitchStr(Accidentals accidentals) {
	return (*m_Volume > 0 ? (accidentals == Flats ? PITCH_FLATS[GetOctavePitch()] : PITCH_SHARPS[GetOctavePitch()]) : L"  ");
}

std::wstring Note::GetVolumeStr() {
	return (*m_Volume < 10 ? L"00" + std::to_wstring(*m_Volume) : (*m_Volume > 100 ? L"0" + std::to_wstring(*m_Volume) : L"100"));
}

std::wstring Note::GetOctaveStr() {
	return L" " + std::to_wstring(GetOctave());
}

//This should be the ONLY way that *m_Volume is modified
bool Note::SetVolume(int value) {
	if (value > 0 && value <= 100) {
		*m_Volume = value;
		return true;
	}
	return false;
}

//This should be the ONLY way that *m_Pitch is modified
bool Note::SetPitch(int value) {
	if (value >= 0 && value <= 88) {
		*m_Pitch = value;
		return true;
	}
	return false;
}

bool Note::SetOctave(int value) {
	return SetPitch(*m_Pitch + value * 12);
}

void Note::OffsetPitch(int amount) {
	SetPitch(*m_Pitch + amount);
}