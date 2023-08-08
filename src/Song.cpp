#include "Song.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>


    using namespace std;

    Song::Song(float _valence, int _year, float _acousticness, std::vector<std::string> _artists, float _danceability, int _duration_ms, float _energy, bool _explicit_, std::string _id, float _instrumentalness,
     float _liveness, float _loudness, std::string _name, int _popularity, float _tempo){
        valence = _valence;
        year = _year;
        acousticness = _acousticness;
        artists = _artists;
        danceability = _danceability;
        duration_ms = _duration_ms;
        energy = _energy;
        explicit_ = _explicit_;
        id = _id;
        instrumentalness = _instrumentalness;
        liveness = _liveness;
        loudness = abs(_loudness);  // lower number is louder
        name = _name;
        popularity = _popularity;
        tempo = _tempo;
    }
    std::string Song::getName() const{
        return name;
    }

    std::vector<std::string> Song::getArtist() const{
        return artists;
    }
    int Song::getPopularity() const{
        return popularity;
    }
    int Song::getMood() const { 
        // 0 happyPoints is sad
        // 3 happyPoints is happy
        int happyPoints = 0;

        if(valence > 0.7) {
            happyPoints++;
        } else if (valence < 0.5) {
            happyPoints--;
        }

        if(energy > 0.6) {
            happyPoints++;
        } else if (energy < 0.45) {
            happyPoints--;
        }

        if(tempo >= 155 && tempo <= 200) {
            happyPoints++;
        }

        return happyPoints;

    }

    bool Song:: isSimilar(Song* other){
        // decide on which attributes are important, how to come up with a similarity score, and what the threshold for similarity is

        double similarity = 0;
        // went with the exponential function 25^(-|x-y|) for each attribute. This gives a value between 0 and 1, with 1 being the most similar. All attributes are weighted equally for now.
        similarity += std::pow(25, -abs(valence - other->valence));
        similarity += std::pow(25, -abs(year - other->year) / 55); // 55 is the range of years in the dataset
        similarity += pow(25, -abs(danceability - other->danceability));
        similarity += pow(25, -abs(energy - other->energy));
        similarity += explicit_ == other->explicit_ ? .5 : 0; // weighted at 0.5x
        similarity += pow(25, -abs(instrumentalness - other->instrumentalness));
        similarity += pow(25, -abs(liveness - other->liveness));
        double  higherLoudness = std::max(abs(loudness), abs(other->loudness));
        similarity += pow(25, -abs(loudness - other->loudness)/higherLoudness);    // divide by the higher loudness to normalize to a value between 0 and 1
        similarity += pow(25, -abs(tempo - other->tempo)/243)*1.5;   // 243 is the range of tempos in the dataset. tempo attribute is weighted at 1.5x
        similarity += pow(25, -abs(acousticness - other->acousticness));
        similarity /= 10.0;    // divide by 10 to get average
        // cout << "similarity between " << name << " and " << other->name << ": " << similarity << endl; // for testing purposes
        return similarity > .75;
    }

