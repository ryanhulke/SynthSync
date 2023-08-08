#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Song.h"
#include "processData.h"
#include "Graph.h"

using namespace std;
int main(){
	Graph graph;
	fstream file;
	file.open("input/refinedDataV2.csv", ios::in);
	vector<string> row;
	string line, cell, temp;
	getline(file, temp); // get rid of first line (column names)

	while(getline(file,line)){
		row.clear();
		Song* song = createSong(row,line);
		graph.addSong(song);
	}
	cout << endl << endl << endl;
	cout << "~~~~~~~~~~~~~~~~ Welcome to Synth Sync ~~~~~~~~~~~~~~~~" << endl;
    cout << endl;

    cout << "Have you run out of fun music to listen to? Look no further!" << endl;
    cout << "With our expert knowledge and taste we can recommend the best" << endl;
    cout << "songs for you base on whatever you're looking for!" << endl;
    cout << endl;

	int option = 0;
	int travType = 0; // traversal type
	bool DFS = false;
	while(option != -1) {
    

		cout << "---------- Enter -1 to Exit ----------" << endl << endl;

		cout << "Would you like to use BFS or DFS? (use 1 for BFS and 0 for DFS)" << endl;
		cin >> travType;
		if (travType == 0) {
			DFS = true;
		} else {
			DFS = false;
		}
		
		cout << "Please enter the corresponding menu option (number) based on what you are looking for: " << endl;
		cout << endl; // spacing
		cout << "~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~" << endl;
		cout << "1. Find songs similar to a song you like" << endl;
		cout << "2. Songs based on artist" << endl; // output adjacent songs to that specific artist's songs
		cout << "3. Songs by mood" << endl; 

		cin >> option;
		cout << endl; // spacing
		if (option == 1) {
			
			string songName;
			cout << "Please enter the name of a song you like: " << endl;
			std::getline(std::cin, songName);
			std::getline(std::cin, songName);

			if(DFS) { // USING DFS TRAVERSAL
				if (graph.DFSbySong(graph.adjList, songName) == false) {
					cout << "Sorry, we couldn't find that song." << endl;
				} 
			} else { // USING BFS TRAVERSAL
				if (graph.BFSbySong(graph.adjList, songName) == false) {
					cout << "Sorry, we couldn't find that song." << endl;
				} 
			}
			cout << endl; // spacing
			
		} else if (option == 2) {
				
			string artistName;
			cout << "Please enter the name of an artist you like: " << endl << endl;
			std::getline(std::cin, artistName);
			std::getline(std::cin, artistName);
			
			if(DFS) { // USING DFS TRAVERSAL
				if (graph.DFSArtist(graph.adjList, artistName) == false) {
					cout << "Sorry, we couldn't find that artist." << endl;
				} 
			} else { // USING BFS TRAVERSAL
				if (graph.BFSArtist(graph.adjList, artistName) == false) {
					cout << "Sorry, we couldn't find that artist." << endl;
				} 
			}
			
			cout << endl; // spacing

		} else if (option == 3) {
			int mood = 0;	// true = happy, false = sad
			string userMood;
			cout << "Enter 1 if you are looking for happy songs, and 0 if you are looking for sad songs: " << endl;
			std::getline(std::cin, userMood);
			std::getline(std::cin, userMood);
			mood = stoi(userMood);
			vector<Song*> songs;

			if(DFS) {
				songs = graph.DFSMood(graph.adjList, mood);
			} else {
				songs = graph.BFSMood(graph.adjList, mood);
			}
			
			
			cout << "Here are some songs with that mood: " << endl;
			for (Song* song : songs) {
				cout << "- " << song->getName() << ", By: ";
				for(int i = 0; i < song->getArtist().size(); i++) {
					cout << song->getArtist()[i] << " ";
				}
				cout << endl;
			}
			cout << endl; // spacing
			
		} else if (option < -1 || option > 3){
			cout << "Sorry, that is not a valid option." << endl;
		}
	}

    return 0;
}