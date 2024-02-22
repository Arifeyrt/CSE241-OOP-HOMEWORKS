#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include "catalog.h"
#include "exception.h"



using namespace std;
namespace PA6{
class music : public Catalog<music>
{
private:
    string title;
    string artist;
    string year;
    string genre;

public:
    music();//constructer
    music(const std::string &_title, const std::string &_artist, const std::string &_year, const std::string &_genre);//constructer

    //GET
    string getTitle() const;
    string getArtist() const;
    string getYear() const;
    string getGenre() const;

    void read() override;
    void Search(string &keyword, string &field, ofstream &out);
    void sort(const std::string &field);
    ~music();
};
}
#endif