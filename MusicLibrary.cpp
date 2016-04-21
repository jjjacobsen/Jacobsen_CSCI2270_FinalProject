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
	for(int i = 0; i < tableSize; i++){
		hashTable[i] = NULL;
	}

	ifstream file;
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
}

MusicLibrary::~MusicLibrary(){
	; // destructor
}

void MusicLibrary::displaySongs(){
	Song *tmp = new Song;
	for(int x = 0; x < tableSize; x++){
		cout << "songs at hashTable index " << x << ": ";
		if(hashTable[x] != NULL){
			tmp = hashTable[x];
			while(tmp != NULL){
				if(tmp->next != NULL){
					cout << tmp->title << ", ";
				}
				else{
					cout << tmp->title;
				}
				tmp = tmp->next;
			}
			cout << endl;
		}
		else{
			cout << "no songs at current index" << endl;
		}
	}
}

void MusicLibrary::addSong(string name, string ar, string al, string le){
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

void MusicLibrary::deleteSong(string name){
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
		rename("outfile.txt","songs.txt");
	
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

Song* MusicLibrary::searchBySong(string name){
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

vector<Song*> MusicLibrary::searchByArtist(string ar){
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

void MusicLibrary::newSong(std::string name, std::string ar, std::string al, std::string le){
	char comma = ',';
	string entry = name + comma + ar + comma + al + comma + le;
	ofstream file;
	file.open("songs.txt", ios_base::app);
	if(file.good()){
		file << entry << "\n";
	}
	file.close();
}

vector<Song*> MusicLibrary::shufflePlay(){
	int x = numSongs(); Song *tmp = new Song;
	vector<Song*> shuffle;
	/*
	while(shuffle.size() < x){
		int num = rand() % 10 + 1;
		cout << num << endl;
		if(hashTable[num] != NULL){
			tmp = hashTable[num];
			while(tmp->next != NULL){
				tmp = tmp->next;
			}
			while(tmp->added == true && tmp->previous != NULL){
				tmp = tmp->previous;
			}
			if(tmp->added == true){
				cout << "anotha one" << endl;
			}
			else{
				shuffle.push_back(tmp);
				tmp->added = true;
			}
		}
	}
	
	for(int i = 0; i < tableSize; i++){
		if(hashTable[i] != NULL){
			Song *tmp = hashTable[i];
			while(tmp->next != NULL){
				tmp->added = false;
				tmp = tmp->next;
			}
			tmp->added = false;
		}
	}
	*/
	
	return shuffle;
}

void MusicLibrary::timer(std::string length){
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

double MusicLibrary::timeConverter(string time){
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

int MusicLibrary::numSongs(){
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

int MusicLibrary::hashSum(std::string key, int s){
	int sum = 0;
	for(int x = 0; x < key.size(); x++){
		sum = sum + key[x];
	}
	sum = sum % s;
	return sum;
}
