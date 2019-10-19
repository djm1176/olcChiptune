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

std::vector<Page> Tune::getPages() {
	return pages;
}