#include <iostream>
#include <fstream>
#include <string>
#include "MusicLibrary.h"
#include <vector>
using namespace std;

int main(){
	MusicLibrary ml;

	bool on = true;
	while(on == true){
		cout << "======Main Menu======" << endl;
		cout << "1. Display Songs" << endl;
		cout << "2. Add Song" << endl;
		cout << "3. Delete Song" << endl;
		cout << "4. Search for Song" << endl;
		cout << "5. Search by Artist" << endl;
		cout << "6. Quit" << endl;
		string path;
		cin >> path;
		if(path == "1"){
			ml.displaySongs();
		}
		else if(path == "2"){
			string wtf;
			getline(cin,wtf);
			string name;
			cout << "Enter title: ";
			getline(cin,name);
			string ar;
			cout << "Enter artist: ";
			getline(cin,ar);
			string al;
			cout << "Enter album: ";
			getline(cin,al);
			string le;
			cout << "Enter length: ";
			getline(cin,le);
			ml.addSong(name,ar,al,le);
			ml.newSong(name,ar,al,le);
		}
		else if(path == "6"){
			cout << "Cya" << endl;
			on = false;
		}
		else if(path == "4"){
			string wtf;
			getline(cin,wtf);
			string name;
			cout << "Enter Song: ";
			getline(cin,name);
			Song *node = ml.searchBySong(name);
			if(node == NULL){
				cout << "Did not find song" << endl;
			}
			else{
				cout << node->title << " by " << node->artist << " on " << node->album << endl;
			}
		}
		else if(path == "3"){
			string wtf;
			getline(cin,wtf);
			string title;
			cout << "Enter Song: ";
			getline(cin,title);
			ml.deleteSong(title);
		}
		else if(path == "5"){
			string wtf;
			getline(cin,wtf);
			string ar;
			cout << "Enter Artist: ";
			getline(cin,ar);
			vector<Song*> list = ml.searchByArtist(ar);
			if(list.size() == 0){
				cout << "Artist Not Found" << endl;
			}
			else{
				for(int i = 0; i < list.size(); i++){
					cout << list[i]->title << ", ";
				}
				cout << endl;
			}
		}
	}

	return 0;
}
