#include <iostream>
#include <fstream>
#include <string>
#include "MusicLibrary.h"
using namespace std;

int main(){
	MusicLibrary ml;

	bool on = true;
	while(on == true){
		cout << "======Main Menu======" << endl;
		cout << "1. Display Songs" << endl;
		cout << "2. Add Song" << endl;
		cout << "3. Quit" << endl;
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
		}
		else if(path == "3"){
			cout << "Cya" << endl;
			on = false;
		}
	}

	return 0;
}