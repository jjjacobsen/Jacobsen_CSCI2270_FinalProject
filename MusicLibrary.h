#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H
#include <string>
#include <vector>

struct Song{
	std::string title;
	std::string artist;
	std::string album;
	std::string length;

	Song *next = NULL;
	Song *previous = NULL;
};

struct Playlist{
	std::vector<Song> playlist;
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
		std::vector<Song*> searchByArtist(std::string ar); // this will return a vector that contains all songs with the same artist
		void newSong(std::string name, std::string ar, std::string al, std::string le); // this changes the txt file
		void timer(std::string length);

	private:
		std::vector<Playlist> allPlaylists;
		double timeConverter(std::string time);
		int numSongs();
		int hashSum(std::string key, int s);
		int tableSize = 10;
		Song* hashTable[10]; // this is just gonna be a big hash table to hold all the songs
};

#endif // MUSICLIBRARY_H
