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
	std::string fileName;
	std::string playlistName;
};

class MusicLibrary
{
	public:
		MusicLibrary();
		~MusicLibrary();
		// Below are functions for building the hash table with all the songs and simple searching/managing stuff
		int hashSum(std::string key, int s);
		void displaySongs();
		void addSong(std::string name, std::string ar, std::string al, std::string le); // this only adds a song to the hashTable, it doesn't change the txt file so additions wont save between successive program runs
		void deleteSong(std::string name);
		Song* searchBySong(std::string name);
		std::vector<Song*> searchByArtist(std::string ar);
		void newSong(std::string name, std::string ar, std::string al, std::string le); // this changes the txt file
		// The two guys below is a little side project
		double timeConverter(std::string time);
		void timer(std::string length);
		// Below are functions regarding the playlists
		void addPlaylist(std::string fileName);
		void displayPlaylists();
		int displayPlaylist(std::string playlistname);
		void addSongPlaylist(std::string name, Playlist *pl);
		Playlist* getSelectedPlaylist(std::string name);
		void removeSongPlaylist(std::string name, Playlist *pl);
		void newPlaylist(std::string name);
		void removePlaylist(std::string name);
		// below are functions for the queue
		void enqueue(Song, MusicLibrary);
		Song dequeue(MusicLibrary);
		void printQueue(MusicLibrary);
		bool queueIsFull();
		bool queueIsEmpty();
		void queueAllSongs(MusicLibrary);

	private:
		// Below are private members for songs and playlists
		int totalPlaylists = 0; // this is just initialized to 0, in the constructor function this value will change
		std::vector<Playlist> allPlaylists; // location where the playlists are stored
		int tableSize = 10;
		Song* hashTable[10]; // this is just gonna be a big hash table to hold all the songs
		// Below are private members for the queue
		int queueSize;
		int head;
		int tail;
		int queueCount;
		Song *arrayQueue;
};

#endif // MUSICLIBRARY_H
