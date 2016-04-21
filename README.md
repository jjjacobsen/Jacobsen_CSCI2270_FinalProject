# Jonah Jacobsen's Final Project
For my project I am going to work alone. I intend to make the code behind an iPod. Although I won't have the ability to actually play sound from the program, everything from making playlists, playing by shuffle (random), or searching by artists will be there. I have even made a timer that will mimic a song being played (when you open the program search for the song "Test"). This code utilizes several of the data structures we studied this semester including hash tables, linked lists, and queues.

How to Run: Clone the repository into a directory in your vm. Open terminal and cd to the repository. Compile by typing "g++ -std=c++11 MusicLibrary.cpp main.cpp". Execute by typing "./a.out". I have provided a file called songs.txt that contains the info to some (dank) music already preloaded into the hash table. From here you can add or remove songs and these functions will not only modify the hash table, but also the .txt file, meaning that your changes are going to stay even after closing and reopening the program...

System Requirements: Use the cu-cs-vm. If you aren't then you will have to make sure all the libraries included at the top of the MusicLibrary.cpp file are properly installed for full functionality (the vm already has these installed for you).

Group Members: none

Contributors:

Open issues/bugs: Don't know how to exit the play song function without exiting the program. With the way I parse the file there cannot be any commas when entering the song information.
