#include "Note.h"

//#########################
//Constructors/Destructor
//#########################

//Default constructor
Note::Note(int pitch) : m_Pitch{pitch} { }

int Note::getPitch() {
	return m_Pitch;
}