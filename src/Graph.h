#pragma once
#include "Song.h"
#include <unordered_map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <iostream>
class Graph{
    
    public:
    std::unordered_map<Song*, std::vector<Song*>> adjList;
    void addEdge(Song* song1, Song* song2);

    void addSong(Song* song);
    bool BFSbySong(std::unordered_map<Song*, std::vector<Song*>> &adjList, std::string name);
    bool DFSbySong(std::unordered_map<Song*, std::vector<Song*>> &adjList, std::string name);
    bool BFSArtist(std::unordered_map<Song*, std::vector<Song*>>& adjList, std::string artist);
    bool DFSArtist(std::unordered_map<Song*, std::vector<Song*>>& adjList, std::string artist);
    std::vector<Song*> BFSMood(std::unordered_map<Song*, std::vector<Song*>>& adjList, int mood);
    std::vector<Song*> DFSMood(std::unordered_map<Song*, std::vector<Song*>>& adjList, int mood);
    
    // For debugging purposes
    void printMap();

};