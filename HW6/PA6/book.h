#ifndef BOOK_H
#define BOOK_H
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
class book : public Catalog<book>
{
private:
    string title;
    string author;
    string year;
    string tags;


public:
    book();//constructer
    book(const string &_title, const string &_author, string &_year, const string &_tags);//constructer

    //GET
    string getTitle() const;
    string getAuthor() const;
    string getYear() const;
    string getTag() const;

    void read() override;
    void Search(string &keyword, string &field, ofstream &out);
    void sort(const std::string &field);
    ~book();
};
}
#endif