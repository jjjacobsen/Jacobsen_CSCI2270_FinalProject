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
	
	ifstream file4; // this will check for all .txt files that make up playlists, then it will make the appropriate playlists
	bool theEnd = true; string partA = "playlist"; string partC = ".txt"; int count = 1; string partB; string fileName;
	while(theEnd){
		partB = to_string(count);
		fileName = partA + partB + partC;
		file4.open(fileName);
		if(file4.good()){
			// make playlist in program
			count++; totalPlaylists++;
		}
		else{
			theEnd = false;
		}
		file4.close();
	}
}

MusicLibrary::~MusicLibrary(){
	; // destructor
}

void MusicLibrary::displaySongs(){ // simply goes through each index in hash table and prints out songs
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

Song* MusicLibrary::searchBySong(string name){ // returns a Song pointer for whatever title you search for
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

void MusicLibrary::addPlaylist(std::string fileName){
	; // THIS IS WHERE I LEFT OFF
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

int MusicLibrary::numSongs(){ // haven't used this function yet, thought I was going to but never did, keeping it in case it becomes useful
	int count = 0;
	for(int i = 0; i < tableSize; i++){
		if(hashTable[i] != NULL){
			Song *tmp = hashTable[i];
			while(tmp->next != NULL){
				count++;
				tmp = tmp->next;
			}
			count++;
		}
	}
	return count;
}

int MusicLibrary::hashSum(std::string key, int s){ // the essence of how I store everything, as you should know
	int sum = 0;
	for(int x = 0; x < key.size(); x++){
		sum = sum + key[x];
	}
	sum = sum % s;
	return sum;
}
