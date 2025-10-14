#pragma once

class PokefaceData
{

	typedef unsigned int GLuint;

public:

	/** Get loaded Pokeface data, or load it if it hasn't been loaded yet. */
	static const std::deque<GLuint>& GetPokefaceData();

private:

	/** Load Pokeface data images from disk */
	static void InitPokefaceData();

	/**
	 * List of loaded Pokeface image ids.
	 *
	 * A deque is used here so that references to
	 * elements do not become invalidated when
	 * the container is resized
	 *
	 * (this may not be necessary)
	 *
	 * These are static values because we want them to
	 * stay loaded through new project loads. Attempting
	 * to reload them every time a new project is loaded
	 * causes undefined behavior where we may (and probably)
	 * will fail to open one of the image files (probably because
	 * its still open in this program).
	 */
	static std::deque<GLuint> PokefaceTextureIds;

	/** Has Pokeface data been loaded yet? */
	static bool bPokefaceDataLoaded;

	/** Did Pokeface data fail to load? */
	static bool bPokefaceDataLoadingFailed;
};
