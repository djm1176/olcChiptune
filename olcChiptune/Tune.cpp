#include "Tune.h"
#include "Page.h"
#include "Beat.h"

Tune::Tune() : pages{ std::vector<Page>(DEFAULT_PAGE_COUNT) }, tempo{ DEFAULT_TEMPO }, playhead{ 0 }, name{ L"Untitled" }{}

Tune::~Tune() {
	pages.clear();
}


bool Tune::load(std::string filename) {
	//TODO: Implement loading according to header file
	//TODO: Develop a file format that is compatible between different versions
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

void Tune::toggleNote(int page, int beat, int note) {
	pages.at(page).getBeats().at(beat % Page::PAGE_BEATS).toggleNote(note);
}