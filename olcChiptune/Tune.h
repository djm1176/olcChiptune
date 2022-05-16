#pragma once

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
	/// The name of this song.
	/// </summary>
	std::wstring name;

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
	std::vector<Page>& getPages();

	/// <summary>
	/// Creates a Page and returns a pointer to it
	/// </summary>
	/// <returns>Pointer to the created page, or nullptr if the page couldn't be created.</returns>
	Page* addPage();

	/// <summary>
	/// Adds a note given the page, beat, and note desired.
	/// </summary>
	/// <param name="page">The page to add to.</param>
	/// <param name="beat">The beat to add to.</param>
	/// <param name="note">The note to add to.</param>
	/// <returns>True if the note was added, false if the Page doesn't exist, or a Note already exists.</returns>
	bool addNote(int page, int beat, int note);


	void toggleNote(int page, int beat, int note);

private:
	std::vector<Page> pages;

};
