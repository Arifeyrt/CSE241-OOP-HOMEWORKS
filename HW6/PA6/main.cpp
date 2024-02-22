#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include "catalog.h"

#include "book.h"
#include "movie.h"
#include "music.h"
#include "exception.h"

using namespace PA6;
using namespace std;
int main()
{
    ifstream file("data.txt");
    string line;
    if (file.is_open())
    {
        // Read the first line from the file
        getline(file, line);
        if (line == "book")
        {
            // Create a Catalog object for books
            Catalog<book> *bookcatalog;
            bookcatalog = new book();
            bookcatalog->read();
        }
        else if (line == "movie")
        {
            // Create a Catalog object for movies
            Catalog<movie> *moviecatalog;
            moviecatalog = new movie();
            moviecatalog->read();
        }
        else if (line == "music")
        {
            // Create a Catalog object for music
            Catalog<music> *musiccatalog;
            musiccatalog = new music();
            musiccatalog->read();
        }
        else
        {
            cout << "Invalid catalog type: " << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file: " << endl;
    }

    return 0;
}