#include "MusicLibrary.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

MusicLibrary::MusicLibrary(){
	for(int i = 0; i < tableSize; i++){
		hashTable[i] = NULL;
	}
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
				cout << tmp->title << " by: " << tmp->artist << " on: " << tmp->album << "; "
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
	;
}

void MusicLibrary::searchBySong(string name){
	;
}

void MusicLibrary::searchByArtist(string ar){
	;
}

void MusicLibrary::searchByAlbum(string al){
	;
}

7

8

9

10

int MusicLibrary::hashSum(std::string key, int s){
	int sum = 0;
	for(int x = 0; x < key.size(); x++){
		sum = sum + key[x];
	}
	sum = sum % s;
	return sum;
}
