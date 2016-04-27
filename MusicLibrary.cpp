#include "MusicLibrary.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

using namespace std;

MusicLibrary::MusicLibrary(){
	// First part of constructor is to make the hash table
	for(int i = 0; i < tableSize; i++){ // just so I can assign all the values in hash table to NULL, not sure if I MUST do this but whatever
		hashTable[i] = NULL;
	}

	ifstream file; // this file read is a cheeky way I am able to parse the file by commas. I know I could use sstream but...
	file.open("songs.txt");
	if(file.good()){
		string spacer;
		while(getline(file,spacer)){
			string one; string two; string three; string four; string filler = ""; int count = 0;
			int x = spacer.length();
			for(int i = 0; i < x; i++){
				char a = spacer[i];
				if(a != ','){
					filler += a;
				}
				else{
					if(count == 0){
						one = filler;
						filler = "";
						count++;
					}
					else if(count == 1){
						two = filler;
						filler = "";
						count++;
					}
					else if(count == 2){
						three = filler;
						filler = "";
						count++;
					}
				}
			}
			four = filler;

			addSong(one,two,three,four);
		}
	}
	file.close();
	
	// Second part is to make the playlists
	ifstream file4; // this will check for all .txt files that make up playlists, then it will make the appropriate playlists
	bool theEnd = true; string partA = "playlist"; string partC = ".txt"; int count = 1; string partB; string fileName;
	while(theEnd){
		partB = to_string(count);
		fileName = partA + partB + partC;
		file4.open(fileName);
		if(file4.good()){
			addPlaylist(fileName);
			count++; totalPlaylists++; // gotta make sure to update that private member
		}
		else{
			theEnd = false;
		}
		file4.close();
	}
	
	// Third part is to make queue ready, I make a massive array for this queue
	queueSize = 200;
	arrayQueue = new Song[queueSize];
	head = 0;
	tail = 0;
	queueCount = 0;
}


MusicLibrary::~MusicLibrary(){
	; // destructor, don't need anything here
}


int MusicLibrary::hashSum(std::string key, int s){ // the essence of how I store everything in the hash table, as you should know
	int sum = 0;
	for(int x = 0; x < key.size(); x++){
		sum = sum + key[x];
	}
	sum = sum % s;
	return sum;
}


void MusicLibrary::displaySongs(){ // simply goes through each index in hash table and prints out all the songs
	Song *tmp = new Song;
	cout << "=====SONGS=====" << endl;
	for(int x = 0; x < tableSize; x++){
		if(hashTable[x] != NULL){
			tmp = hashTable[x];
			while(tmp != NULL){
				cout << tmp->title << " by " << tmp->artist << endl;
				tmp = tmp->next;
			}
		}
	}
}


void MusicLibrary::addSong(string name, string ar, string al, string le){ // this will add a song to the hash table
	int index = hashSum(name,tableSize);
	Song *node = new Song;
	node->title = name;
	node->artist = ar;
	node->album = al;
	node->length = le;
	if(hashTable[index] == NULL){
		hashTable[index] = node;
	}
	else{
		Song *tmp = hashTable[index];
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		node->previous = tmp;
		tmp->next = node;
	}
}


void MusicLibrary::deleteSong(string name){ // making this function was tricky because deleting from the middle of a file is hard. This also handles the hash table as well as the .txt file
	Song *node = searchBySong(name);
	if(node == NULL){
		cout << "Did not find song" << endl;
	}
	else{
		char comma = ',';
		string exit = node->title + comma + node->artist + comma + node->album + comma + node->length;
		
		string line;
		ifstream file2("songs.txt");
		ofstream file3("outfile.txt");
		while(getline(file2,line)){
			if(line != exit){
				file3 << line << "\n";
			}
		}
		file2.close();
		file3.close();
		remove("songs.txt");
		rename("outfile.txt","songs.txt"); // this method of copying the whole file except for one line and then renaming the new file wouldn't work for huge data sets, but for this small project it will do
		
		//This last part removes the song from the program after the .txt file is modified
		int index = hashSum(name,tableSize);
		if(node->previous == NULL && node->next == NULL){
			hashTable[index] = NULL;
		}
		else if(node->previous == NULL && node->next != NULL){
			node->next->previous = NULL;
			hashTable[index] = node->next;
			delete node;
		}
		else if(node->previous != NULL && node->next == NULL){
			node->previous->next = NULL;
			delete node;
		}
		else if(node->previous != NULL && node->next != NULL){
			node->next->previous = node->previous;
			node->previous->next = node->next;
			delete node;
		}
	}
}


Song* MusicLibrary::searchBySong(string name){ // returns a pointer to the song for whatever title you search for
	int index = hashSum(name,tableSize);
	Song *tmp = hashTable[index];
	if(tmp == NULL){
		return NULL;
	}
	else{
		while(tmp->title != name && tmp != NULL){
			if(tmp->next == NULL){
				return NULL;
			}
			else{
				tmp = tmp->next;
			}
		}
		return tmp;
	}
}


vector<Song*> MusicLibrary::searchByArtist(string ar){ // makes a vector of song pointers for every song that shares the same artist
	vector<Song*> list;
	for(int x = 0; x < tableSize; x++){
		Song *tmp = hashTable[x];
		while(tmp != NULL){
			if(tmp->artist == ar){
				list.push_back(tmp);
			}
			tmp = tmp->next;
		}
	}
	return list;
}


void MusicLibrary::newSong(std::string name, std::string ar, std::string al, std::string le){ // this just changes the .txt file, I separated the two add functions so I can use the first one when building the musiclibrary class and the other to save modifications between program runs
	char comma = ',';
	string entry = name + comma + ar + comma + al + comma + le;
	ofstream file;
	file.open("songs.txt", ios_base::app);
	if(file.good()){
		file << entry << "\n";
	}
	file.close();
}


double MusicLibrary::timeConverter(string time){ // this function is what allows me to take a string of 4:42 and then convert that into the number of seconds, I do this because my timer function needs seconds
	double returnVal = 0;
	string minutes = "";
	string seconds = "";
	bool before = true;
	for(int i = 0; i < time.size(); i++){
		if(time[i] == ':'){
			before = false;
		}
		else{
			if(before == true){
				minutes = minutes += time[i];
			}
			else if(before == false){
				seconds = seconds += time[i];
			}
		}
	}
	double min = stod(minutes);
	double sec = stod(seconds);
	min = min*60;
	returnVal = min + sec;
	return returnVal;
}


void MusicLibrary::timer(std::string length){ // side project, functions in here are derived from the libraries at the top
	string totalTime = length;
	double rawTime = timeConverter(totalTime);
	
	
	clock_t startTime = clock();
	double secondsPassed;
	cout << "Playing Song" << endl;
	bool flag = true;
	int currentTime = 0;
	int minutes = -1;
	int seconds = 0;
	while(flag){
		seconds = currentTime % 60;
		secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
		if(currentTime == secondsPassed){
			if(currentTime % 60 == 0){
				minutes++;
			}
			cout << ' ' << minutes << ':';
			if(seconds < 10){
				cout << '0' << seconds;
			}
			else{
				cout << seconds;
			}
			cout << "/" << length << '\r' << flush;
			currentTime++;
		}
		if(secondsPassed >= rawTime){
			cout << endl << "done" << endl;
			flag = false;
		}
	}
}


void MusicLibrary::addPlaylist(string fileName){ // just used to build the playlists inside program
	Playlist newPlaylist;
	newPlaylist.fileName = fileName;
	ifstream file5;
	file5.open(fileName);
	if(file5.good()){
		string name;
		getline(file5,name);
		newPlaylist.playlistName = name;
		string str;
		while(getline(file5,str)){
			Song *tmp = searchBySong(str);
			Song song;
			if(tmp != NULL){
				song.title = tmp->title;
				song.artist = tmp->artist;
				song.album = tmp->album;
				song.length = tmp->length;
				newPlaylist.playlist.push_back(song);
			}
		}
	}
	allPlaylists.push_back(newPlaylist);
}


void MusicLibrary::displayPlaylists(){ // simply shows what playlists there are
	if(allPlaylists.size() != 0){
		cout << "Current Playlists:" << endl;
		for(int i = 0; i < totalPlaylists; i++){
			cout << i+1 << ". " << allPlaylists[i].playlistName << endl;
		}
	}
	else{
		cout << "no playlists" << endl;
	}
}


int MusicLibrary::displayPlaylist(string playlistname){ // the reason this function returns an int is so that in the main.cpp file we can avoid going into the while loop for the next step if we don't find a playlist
	bool found = false;
	for(int i = 0; i < totalPlaylists; i++){
		if(allPlaylists[i].playlistName == playlistname){
			found = true;
			cout << "===" << playlistname << "===" << endl;
			for(int j = 0; j < allPlaylists[i].playlist.size(); j++){
				cout << allPlaylists[i].playlist[j].title << endl;
			}
		}
	}
	if(found == false){
		cout << "Did not find playlist" << endl;
		return 0;
	}
	return 1; // dont need else statement because if the code goes into the if statement above, once it hits the return statement the function ends
}


void MusicLibrary::addSongPlaylist(string name, Playlist *pl){
	Song *tmp = searchBySong(name);
	if(tmp == NULL){
		cout << "Did not find song in library" << endl;
	}
	else{
		Song newSong; // adds the song to the vector of songs in the playlist struct
		newSong.title = tmp->title;
		newSong.artist = tmp->artist;
		newSong.album = tmp->album;
		newSong.length = tmp->length;
		pl->playlist.push_back(newSong);
		
		ofstream file; // edits the .txt file so the change is saved
		file.open(pl->fileName, ios_base::app);
		if(file.good()){
			file << tmp->title << "\n";
		}
		file.close();
		
		displayPlaylist(pl->playlistName); // shows updated change
	}
}


Playlist* MusicLibrary::getSelectedPlaylist(string name){ // returns the pointer to a selected playlist
	for(int i = 0; i < totalPlaylists; i++){
		if(allPlaylists[i].playlistName == name){
			return &allPlaylists[i];
		}
	}
	return NULL;
}


void MusicLibrary::removeSongPlaylist(std::string name, Playlist *pl){ // very similar to the remove song from hash table function
	bool found = false;
	for(int i = 0; i < pl->playlist.size(); i++){
		if(name == pl->playlist[i].title){
			found = true;
		}
	}
	if(found == false){
		cout << "Did not find song in playlist" << endl;
	}
	else{
		for(int j = 0; j < pl->playlist.size(); j++){ // gets song out of program
			if(name == pl->playlist[j].title){
				pl->playlist.erase(pl->playlist.begin()+j);
			}
		}
		
		string line; // gets song out of .txt file
		string filename = pl->fileName;
		const char * filename2 = filename.c_str(); // need a const char * value for remove and rename functions below
		ifstream file2(filename2);
		ofstream file3("outfile.txt");
		while(getline(file2,line)){
			if(line != name){
				file3 << line << "\n";
			}
		}
		file2.close();
		file3.close();
		remove(filename2);
		rename("outfile.txt",filename2);
		
		displayPlaylist(pl->playlistName); // shows updated change
	}
}


void MusicLibrary::newPlaylist(std::string name){
	Playlist *node = new Playlist; // make the playlist
	string partA = "playlist"; string partC = ".txt"; string partB; string filename;
	totalPlaylists++;
	partB = to_string(totalPlaylists);
	filename = partA + partB + partC;
	node->playlistName = name;
	node->fileName = filename;
	
	const char * filename2 = filename.c_str();
	ofstream file(filename2); // makes the .txt file
	file << name << "\n";
	file.close();
	
	allPlaylists.push_back(*node); // adds playlist to program
}


void MusicLibrary::removePlaylist(std::string name){
	Playlist *node = getSelectedPlaylist(name);
	if(node == NULL){
		cout << "Did not find playlist to delete" << endl;
	}
	else{
		int marker;
		string filename = node->fileName;
		for(int i = 0; i < allPlaylists.size(); i++){ // this will get playlist out of program
			if(name == allPlaylists[i].playlistName){
				allPlaylists.erase(allPlaylists.begin()+i);
				marker = i;
			}
		}
		totalPlaylists--; // I don't think I need to do 'delete node;' on next line because the erase function above does that for me, not 100% sure tho
		// delete node; this will crash the program... "error in ./a.out: double free or corruption (fasttop): memory address
		
		const char *filename2 = filename.c_str(); // gets rid of .txt file
		remove(filename2);
		
		for(marker; marker < allPlaylists.size(); marker++){
			node = &allPlaylists[marker];
			string oldfilename = node->fileName;
			string partA = "playlist"; string partC = ".txt"; string partB;
			partB = to_string(marker+1);
			string filename3 = partA + partB + partC;
			node->fileName = filename3;
			
			const char *oldfilename2 = oldfilename.c_str();
			const char *filename4 = filename3.c_str();
			rename(oldfilename2,filename4);
		}
	}
}


void MusicLibrary::enqueue(Song song, MusicLibrary ml){
	bool check = ml.queueIsFull();
	if(check == false){
		arrayQueue[tail] = song;
		queueCount++;
		if(tail == queueSize-1){
			tail = 0;
		}
		else{
			tail++;
		}
		cout << song.title << " has been added to the queue" << endl;
	}
	else{
		cout << "Queue is full" << endl;
	}
}


Song MusicLibrary::dequeue(MusicLibrary ml){
	bool check = ml.queueIsEmpty(); Song value;
	if(check == false){
		value = arrayQueue[head];
		queueCount--;
		if(head == queueSize-1){
			head = 0;
		}
		else{
			head++;
		}
	}
	else{
		cout << "Queue is empty" << endl;
	}
	return value;
}


void MusicLibrary::printQueue(MusicLibrary ml){
	int j = head;
	if(ml.queueIsEmpty() == false){
		cout << "Currenly playing: " << arrayQueue[j].title << endl;
		cout << "Up Next" << endl;
		cout << "-------" << endl;
		j++;
		for(int i = 1; i < queueCount; i++){
			if(j < queueSize){
				cout << arrayQueue[j].title << endl;
				j++;
			}
			else{
				j = 0;
				cout << arrayQueue[j].title << endl;
				j++;
			}
		}
	}
	else{
		cout << "Empty" << endl;
	}
}


bool MusicLibrary::queueIsFull(){
	if(queueCount == 200){
		return true;
	}
	return false;
}


bool MusicLibrary::queueIsEmpty(){
	if(queueCount == 0){
		return true;
	}
	return false;
}


void MusicLibrary::queueAllSongs(MusicLibrary ml){
	for(int i = 0; i < tableSize; i++){
		if(hashTable[i] != NULL){
			Song *tmp = hashTable[i];
			while(tmp->next != NULL){
				enqueue(*tmp, ml);
				tmp = tmp->next;
			}
			enqueue(*tmp, ml);
		}
	}
}
