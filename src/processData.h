#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Song.h"
#include "Graph.h"
#include "processData.h"
using namespace std;
void processRow(vector<string>& row, string line){
	stringstream s(line);
	string temp;
	string cell;
    for (int i = 0; i < 15; i++){
			getline(s, cell, ',');
			if (i == 3){ // format the artists in case they contain commas
				while (true) {
					getline(s, temp, ',');
					if ((temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '.' && temp[1] >= '0' && temp[1] <= 9)) { // if the next cell is a number, then we are done with artists
						row.push_back(cell);
						cell = temp;
						i++;
						break;
					} else {
						cell += "," + temp;
					}
				}
			} else if (i == 12) { // format the song name in case it contains commas
				while (true) {
					getline(s, temp, ',');
					if ((temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '.' && temp[1] >= '0' && temp[1] <= 9)) { // if the next cell is a number, then the song name doesn't contain a comma
						row.push_back(cell);	// when end of song name is reached, add to row and increment i
						cell = temp;
						i++;
						break;
					} else {
						cell += "," + temp;
					}
				}
			}
			row.push_back(cell);
		}
}
Song* createSong(vector<string>& row, string& line){
	processRow(row, line);
	// create a song object with the data from the row
	float valence = stof(row[0]);
	int year = stoi(row[1]);
	float acousticness = stof(row[2]);
	vector<string> artists;
	stringstream a(row[3]);
	for (string artist; getline(a, artist, ';');) {
		artists.push_back(artist);
	}
    float danceability = stof(row[4]);
    int duration_ms = stoi(row[5]);
    float energy = stof(row[6]);
    bool explicit_ = stoi(row[7]) == 1;
    string id = row[8];
    float instrumentalness = stof(row[9]);
    float liveness = stof(row[10]);
    float loudness 	= stof(row[11]);
    string name = row[12];
    int popularity = stoi(row[13]);
    float tempo = stof(row[14]);
	Song* song = new Song(valence, year, acousticness, artists, danceability, duration_ms, energy, explicit_, id, instrumentalness, liveness, loudness, name, popularity, tempo);
	return song;
}