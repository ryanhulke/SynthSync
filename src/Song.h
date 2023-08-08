#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Song {
    float valence;
    int year;
    float acousticness;
    std::vector<std::string> artists;
    float danceability;
    int duration_ms;
    float energy;
    bool explicit_;
    std::string id;
    float instrumentalness;
    float liveness;
    std::string name;
    float loudness;
    int popularity;
    float tempo;

    public:

    Song(float _valence, int _year, float _acousticness, std::vector<std::string> _artists, float _danceability, int _duration_ms, float _energy, bool _explicit_, std::string _id, float _instrumentalness,
     float _liveness, float _loudness, std::string _name, int _popularity, float _tempo);

    std::string getName() const;
    std::vector<std::string> getArtist() const;
    int getPopularity() const;
    int getMood() const;

    bool isSimilar(Song* other);



};