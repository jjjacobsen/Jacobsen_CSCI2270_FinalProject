#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H
#include <string>

struct Song{
	std::string title;
	std::string artist;
	std::album;
	int length;

	// if I figure out how add the mp3 file here

	Song *next = NULL;
	Song *previous = NULL;
};

class MusicLibrary
{
	public:
		MusicLibrary();
		~MusicLibrary();
		1
		2
		3
		4
		5
		6
		7
		8
		9
		10
		// the 10 public methods necessary

	private:
		int hashSum(std::string key, int s);
		int tableSize = 10;
		Song* hashTable[10]; // this is just gonna be a big hash table to hold all the songs
};

#endif // MUSICLIBRARY_H