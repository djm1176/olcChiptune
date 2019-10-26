#include "Tune.h"


Tune::Tune() : pages{ std::vector<Page>(DEFAULT_PAGE_COUNT) }, tempo{ DEFAULT_TEMPO }, playhead{ 0 } {}

Tune::~Tune() {
	pages.clear();
}


bool Tune::load(std::string filename) {
	//TODO: Implement loading according to header file
	return false;
}

bool Tune::save(std::string filename, bool overwrite) {
	//TODO: Implement saving according to header file
	return false;
}

std::vector<Page>& Tune::getPages() {
	return pages;
}

Page* Tune::addPage() {
	//TODO: Is there ever a case where a page can't be added and nullptr should be returned?
	Page newPage = Page();
	pages.push_back(newPage);

	return &newPage;
}

bool Tune::addNote(int page, int beat, int note) {
	if (page >= pages.size()) return false;
	//Modulus to ensure bounds checking
	return pages.at(page).getBeats().at(beat % Page::PAGE_BEATS).addNote(note);
}