#include "Note.h"

Note::Note(int volume, int pitch) : m_Volume{ new int{volume} }, m_Pitch{ new int{pitch} } {
	
}

Note::~Note() {
	delete m_Volume;
	delete m_Pitch;
}

Note::Note(const Note& other) : m_Volume{ new int{*other.m_Volume} }, m_Pitch{ new int{*other.m_Pitch} } {

}

Note::Note(Note&& other) : m_Volume{other.m_Volume}, m_Pitch{other.m_Pitch} {
	other.m_Volume = nullptr;
	other.m_Pitch = nullptr;
}

Note &Note::operator=(const Note& rhs) {
	if (this != &rhs) {
		*m_Volume = *rhs.m_Volume;
		*m_Pitch = *rhs.m_Pitch;
	}
	return *this;
}

Note &Note::operator=(Note&& rhs) {
	std::swap(m_Volume, rhs.m_Volume);
	std::swap(m_Pitch, rhs.m_Pitch);
	return *this;
}