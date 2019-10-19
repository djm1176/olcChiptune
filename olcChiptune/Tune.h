#pragma once
#ifndef OLCTUNE_H
#define OLCTUNE_H

#include <string>
#include <vector>
#include "Page.h"

class Tune {
public:
	const int DEFAULT_TEMPO = 120;
	const int DEFAULT_PAGE_COUNT = 1;

	Tune();

	~Tune();
	//Tune(const Tune& other);
	//Tune(Tune&& other);
	//Tune& operator=(const Tune& rhs);
	//Tune& operator=(Tune&& rhs);

	/// <summary>
	/// Load a Tune from disk in the current directory.
	/// </summary>
	/// <param name="filename">The name of the Tune to load. Extensions are handled internally.</param>
	/// <returns>True if the tune was loaded by filename successfully.</returns>
	bool load(std::string filename);

	/// <summary>
	/// Save a Tune to disk in the current directory.
	/// </summary>
	/// <param name="filename">The name of the Tune when saved.</param>
	/// <param name="overwrite">If true, any existing files are overwritten.</param>
	/// <returns>True if the Tune is successfully saved. False if unsuccessful or if overwrite is false and there is an existing Tune with the same name.</returns>
	bool save(std::string filename, bool overwrite = false);

	/// <summary>
	/// The tempo in beats per minute to play at playback.
	/// </summary>
	int tempo;

	/// <summary>
	/// The current position of time at playback.
	/// </summary>
	int playhead;

	/// <summary>
	/// Get all pages contained in this Tune.
	/// </summary>
	/// <returns>An std vector of Pages.</returns>
	std::vector<Page> getPages();

private:
	std::vector<Page> pages;

};

#endif