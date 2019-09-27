#include "Note.h"
#include "Beat.h"

Beat::Beat()
{
}

Beat::~Beat() {
	delete notes;
}