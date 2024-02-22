#ifndef CATALOG_H
#define CATALOG_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

namespace PA6{
template <typename T>
class Catalog {
protected:
    vector<T> data;
    string catalogType;

public:
   
    Catalog();//constructer
    Catalog(const Catalog& oth);//copy constructer
    Catalog(const std::vector<T>& newData, const std::string& newCatalogType);//constructer
    virtual void read() = 0;
     ~Catalog();


};


template <typename T>
Catalog<T>::Catalog()
{
    // Default constructor
    catalogType = "";
}

template <typename T>
Catalog<T>::Catalog(const std::vector<T> &newData, const std::string &newCatalogType)
{
    // Constructor
    data = newData;
    catalogType = newCatalogType;
}

template <typename T>
Catalog<T>::Catalog(const Catalog &oth)
{
    // Copy constructor
    data = oth.data;
    catalogType = oth.catalogType;
}

template <typename T>
Catalog<T>::~Catalog()
{
    // destructor
}

}
#endif




