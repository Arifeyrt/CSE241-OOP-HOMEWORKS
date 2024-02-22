#ifndef MOVIE_H
#define MOVIE_H
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
class movie : public Catalog<movie>
{
private:
    string title;
    string director;
    string year;
    string genre;
    string starring;

public:
    movie();//constructer
    movie(const string &_title, const string &_director, string &_year, const string &_genre, const string &_starring);//constructer
    

    //GET
    string getTitle() const;
    string getDirector() const;
    string getYear() const;
    string getGenre() const;
    string getStarring() const;
    
    void read() override;
    void Search(string &keyword, string &field, ofstream &out);
    void sort(const std::string &field);
    ~movie();
};
}
#endif