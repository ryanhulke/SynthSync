#include "Graph.h"

    
    void Graph:: addEdge(Song* song1, Song* song2)
    { // gets called when the similarity threshold is met
        if (adjList.find(song1) == adjList.end())
            adjList[song1] = std::vector<Song*>();
        if (adjList.find(song2) == adjList.end())
            adjList[song2] = std::vector<Song*>();
        adjList[song1].push_back(song2);
        adjList[song2].push_back(song1);
    }
    void Graph:: addSong(Song* song){                    // gets called when a song is added to the graph
        if (adjList.find(song) == adjList.end()) adjList[song] = std::vector<Song*>();
        else return;                             // if the song is already in the graph, do nothing
        for (auto& [key, value] : adjList) {
            if (song->isSimilar(key)) {
                addEdge(song, key);
            }
        }
    }

    void Graph::printMap(){
        for(auto iter = adjList.begin();iter!=adjList.end();iter++){
            std::cout<<iter->first->getName()<<std::endl;
        }
        std::cout<<adjList.size()<<std::endl;
    }
    
    bool Graph::BFSbySong(std::unordered_map<Song*, std::vector<Song*>> &adjList, std::string songName) // Returns true if found
    {
        std::set<Song*> visited;
        std::queue<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first);
        q.push(iter->first);
        bool songFound = false;
        int printed = 0;

        while (!q.empty())
        {
            Song* s = q.front();
            q.pop();
            std::vector<Song*> neighbors = adjList[s];

            if (s->getName() == songName) {
                songFound = true;
                std::cout << "Here are some songs you might like: " << std::endl;
            }
            
            for (auto v : neighbors)
            {
                if (visited.count(v) == 0) // if it has not been visited
                {
                    if(songFound) {
                        std::cout << "- " << v->getName() << ", By: "; 
                        for(int i = 0; i < v->getArtist().size(); i++) {
						    std::cout << v->getArtist()[i] << " ";
					    }
                        std::cout << std::endl;
                        printed++;
                    }

                    if(printed >= 5) {
                        break;
                    }

                    visited.insert(v);
                    q.push(v);
                }
            }

            if(printed >= 5) { // Only print 5
                return true;
            }
        }

        return false;

    }


    bool Graph::DFSbySong(std::unordered_map<Song*, std::vector<Song*>> &adjList, std::string songName)
    {
        std::set<Song*> visited;
        std::stack<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first);
        q.push(iter->first);
        bool songFound = false;
        int printed = 0;

        while (!q.empty())
        {
            Song* u = q.top();
            if(songFound) { // Print song and artist
                std::cout << "- " << u->getName() << ", By: "; 
                for(int i = 0; i < u->getArtist().size(); i++) {
                    std::cout << u->getArtist()[i] << " ";
                }
                std::cout << std::endl;
                printed++;
            }
            if(printed >= 5) {
                return true;
            }
            if (u->getName() == songName) {
                songFound = true;
            }
            q.pop();
            std::vector<Song*> neighbors = adjList[u];

            for (auto v : neighbors)
            {
                if (visited.count(v) == 0)
                {
                    visited.insert(v);
                    q.push(v);
                }
            }
        }

        return false;
    }


    // This is supposed to do a BFS search but checking if the song is of the same artist IT DOES NOT WORK, NEEDS TO BE FIXED!!
    bool Graph::BFSArtist(std::unordered_map<Song*, std::vector<Song*>>& adjList, std::string artist){
        std::set<Song*> visited;
        std::queue<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first);
        q.push(iter->first);
        bool artistFound = false;
        int printed = 0;

        while (!q.empty())
        {
            Song* s = q.front();
            q.pop();
            std::vector<Song*> neighbors = adjList[s];

            if (s->getArtist()[0] == artist) {
                artistFound = true;
                std::cout << "Here are some songs you might like: " << std::endl;
            }
            
            for (auto v : neighbors)
            {
                if (visited.count(v) == 0) // if it has not been visited
                {
                    if(artistFound) {
                        std::cout << "- " << v->getName() << ", By: "; 
                        for(int i = 0; i < v->getArtist().size(); i++) {
						    std::cout << v->getArtist()[i] << " ";
					    }
                        std::cout << std::endl;
                        printed++;
                    }
                    if(printed >= 5) {
                        break;
                    }
                    visited.insert(v);
                    q.push(v);
                }
            }

            if(printed >= 5) { // Only print 5
                return true;
            }
        }

        return false;

    }

    bool Graph::DFSArtist(std::unordered_map<Song*, std::vector<Song*>>& adjList, std::string artist) {
        std::set<Song*> visited;
        std::stack<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first);
        q.push(iter->first);
        bool artistFound = false;
        int printed = 0;

        while (!q.empty())
        {
            Song* u = q.top();
            if(artistFound) { // Print song and artist
                std::cout << "- " << u->getName() << ", By: "; 
                for(int i = 0; i < u->getArtist().size(); i++) {
                    std::cout << u->getArtist()[i] << " ";
                }
                std::cout << std::endl;
                printed++;
            }
            if(printed >= 5) {
                return true;
            }
            if (u->getArtist()[0] == artist) {
                artistFound = true;
            }
            q.pop();
            std::vector<Song*> neighbors = adjList[u];

            for (auto v : neighbors)
            {
                if (visited.count(v) == 0)
                {
                    visited.insert(v);
                    q.push(v);
                }
            }
        }

        return false;
    }

    std::vector<Song*> Graph::BFSMood(std::unordered_map<Song*, std::vector<Song*>>& adjList, int mood) {
        std::vector<Song*> moodMatches;
        std::set<std::string> visited;
        std::queue<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first->getName());
        q.push(iter->first);
        if (mood == 0) {
            mood = -2; // Score needed to be considered sad 
        } else {
            mood = 3; // Score needed to be considered happy
        }

        while (!q.empty())
        {
            Song* s = q.front();
            q.pop();
            std::vector<Song*> neighbors = adjList[s];

            for (auto v : neighbors)
            {
                if (visited.count(v->getName()) == 0) // if it has not been visited
                {
                    if(v->getMood() == mood) { // if mood matches (3 is happy, -2 is sad- based on a happyScore)
                        moodMatches.push_back(v);
                    }
                    if(moodMatches.size() >= 5) { // only add until 5 songs are found
                        break;
                    }
                    visited.insert(v->getName());
                    q.push(v);
                }
            }

            if(moodMatches.size() >= 5) { // only add until 5 songs are found
                        break;
            }

        }

        return moodMatches;
    }
    
    std::vector<Song*> Graph::DFSMood(std::unordered_map<Song*, std::vector<Song*>>& adjList, int mood) {
        std::vector<Song*> moodMatches;
        std::set<std::string> visited;
        std::stack<Song*> q;
        auto iter = adjList.begin();
        visited.insert(iter->first->getName());
        q.push(iter->first);
        if (mood == 0) {
            mood = -2; // Score needed to be considered sad 
        } else {
            mood = 3; // Score needed to be considered happy
        }

        while (!q.empty())
        {
            Song* u = q.top();
            if(u->getMood() == mood) { // if mood matches
                moodMatches.push_back(u);
            }
            if(moodMatches.size() >= 5) {
                break;
            }
            q.pop();
            std::vector<Song*> neighbors = adjList[u];

            for (auto v : neighbors)
            {
                if (visited.count(v->getName()) == 0)
                {
                    visited.insert(v->getName());
                    q.push(v);
                }
            }
        }

        return moodMatches;
    }



