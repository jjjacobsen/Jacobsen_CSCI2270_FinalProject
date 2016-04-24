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
		cout << "6. Go To Playlists" << endl;
		cout << "7. Go To Queue" << endl;
		cout << "8. Quit" << endl;
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
		else if(path == "8"){
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
				bool on3 = true;
				while(on3 == true){
					cout << "1. Play Song" << endl;
					cout << "2. Back to Main Menu" << endl;
					string whatNext;
					cin >> whatNext;
					if(whatNext == "1"){
						ml.timer(node->length);
						on3 = false;
					}
					else if(whatNext == "2"){
						on3 = false;
					}
				}
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
				bool on2 = true;
				while(on2 == true){
					cout << "===Found Artist===" << endl;
					cout << "1. Display Songs" << endl;
					cout << "2. Back To Main Menu" << endl;
					string whereTo;
					cin >> whereTo;
					if(whereTo == "1"){
						for(int i = 0; i < list.size(); i++){
							if(i != list.size()-1){
								cout << list[i]->title << ", ";
							}
							else{
								cout << list[i]->title;
							}
						}
						cout << endl;
					}
					else if(whereTo == "2"){
						on2 = false;
					}
				}
			}
		}
		else if(path == "6"){
			bool on4 = true;
			while(on4){
				cout << "======PLAYLISTS======" << endl;
				cout << "1. Display Playlists" << endl;
				cout << "2. Open Specific Playlist" << endl;
				cout << "3. Create Playlist" << endl;
				cout << "4. Delete Playlist" << endl;
				cout << "5. Back to Main Menu" << endl;
				string anotha;
				cin >> anotha;
				if(anotha == "1"){
					ml.displayPlaylists();
				}
				else if(anotha == "2"){
					string wtf;
					getline(cin,wtf);
					string input;
					cout << "What playlist would you like to open: ";
					getline(cin,input);
					int test = ml.displayPlaylist(input);
					if(test == 1){
						bool on6 = true;
						Playlist *selected = ml.getSelectedPlaylist(input);
						while(on6){
							cout << "================" << endl;
							cout << "1. Add Song" << endl;
							cout << "2. Delete Song" << endl;
							cout << "3. Back to playlist menu" << endl;
							string nextinput;
							cin >> nextinput;
							if(nextinput == "1"){
								string wtf;
								getline(cin,wtf);
								string nextinput;
								cout << "What song would you like to add: ";
								getline(cin,nextinput);
								ml.addSongPlaylist(nextinput,selected);
							}
							else if(nextinput == "2"){
								string wtf;
								getline(cin,wtf);
								string nextinput;
								cout << "What song would you like to remove: ";
								getline(cin,nextinput);
								ml.removeSongPlaylist(nextinput,selected);
							}
							else if(nextinput == "3"){
								on6 = false;
							}
						}
					}
				}
				else if(anotha == "5"){
					on4 = false;
				}
				else if(anotha == "3"){
					// new playlist
					// MAKE SURE TO UPDATE THE TOTALPLAYLISTS PRIVATE MEMBER
				}
				else if(anotha == "4"){
					// delete playlist
				}
			}
		}
		else if(path == "7"){
			bool on5 = true;
			while(on5){
				cout << "=====Queue=====" << endl;
				cout << "1. Display Order" << endl;
				cout << "2. Add Song to Up Next" << endl;
				cout << "3. Play from all songs" << endl;
				cout << "4. Play playlist" << endl;
				cout << "5. Back to Main Menu" << endl;
				string last;
				cin >> last;
				if(last == "1"){
					// display the queue
				}
				else if(last == "2"){
					// add a song to queue
				}
				else if(last == "3"){
					// remake queue for all songs
				}
				else if(last == "4"){
					// play from a playlist
				}
				else if(last == "5"){
					on5 = false;
				}
			}
		}
	}

	return 0;
}
