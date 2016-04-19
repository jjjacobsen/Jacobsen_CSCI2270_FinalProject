#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H
#include <string>

struct Song{
	std::string title;
	std::string artist;
	std::string album;
	std::string length;

	bool added = false;

	// if I figure out how, add the mp3 file here

	Song *next = NULL;
	Song *previous = NULL;
};

class MusicLibrary
{
	public:
		MusicLibrary();
		~MusicLibrary();
		void displaySongs();
		void addSong(std::string name, std::string ar, std::string al, std::string le); // this only adds a song to the hashTable, it doesn't change the txt file so additions wont save between successive program runs
		void deleteSong(std::string name);
		Song* searchBySong(std::string name);
		void searchByArtist(std::string ar);
		void searchByAlbum(std::string al);
		void newSong(std::string name, std::string ar, std::string al, std::string le); // this changes the txt file
		/*
		8
		9
		10
		*/
		// the 10 public methods necessary

	private:
		int hashSum(std::string key, int s);
		int tableSize = 10;
		Song* hashTable[10]; // this is just gonna be a big hash table to hold all the songs
};

#endif // MUSICLIBRARY_H
