#include "music.h"
namespace PA6
{
    music::music()
    {
        title = ""; // Default constructor
        artist = "";
        year = "";
        genre = "";
    }

    music::music(const std::string &_title, const std::string &_artist, const std::string &_year, const std::string &_genre)
    { // Constructor
        title = _title;
        artist = _artist;
        year = _year;
        genre = _genre;
    }

    string music::getTitle() const { return title; }
    string music::getArtist() const { return artist; }
    string music::getYear() const { return year; }
    string music::getGenre() const { return genre; }

    void music::read()
    {
        ifstream file("data.txt");
        ofstream out("output.txt");
        string line;
        string field;
        int count = 0;

        // Read the first line and get the catalog type
        getline(file, line);
        catalogType = line;
        int wrong; // missing or duplicate expression write
        out << "Catalog read: " << catalogType << endl;
        string t, a, y, g;
        while (getline(file, line))
        {
            count = 0;
            try
            {

                stringstream split_line(line);

                for (char c : line)
                {
                    if (c == '\"')
                    {            // If the character is a double quote
                        count++; // Increment the count
                    }
                }
                // Extract the data from each line
                getline(split_line, t, '\"'); // get the title
                getline(split_line, t, '\"'); // get the title again

                getline(split_line, a, '\"'); // get the author
                getline(split_line, a, '\"'); // get the author again

                getline(split_line, y, '\"'); // gett the year
                getline(split_line, y, '\"'); // get the year again

                getline(split_line, g, '\"'); // get the genre
                getline(split_line, g, '\"'); // get the genre again

                wrong = 0;
                // missing field exception
                if (t.empty() || a.empty() || y.empty() || g.empty())
                {
                    if (count != 8)
                    {
                        wrong = 1;
                        throw MissingField();
                    }
                }

                // dublicate enty exception
                for (int i = 0; i < data.size(); i++)
                {
                    if (data[i].getTitle() == t)
                    {
                        wrong = 2;
                        throw DuplicateEntry();
                    }
                }
                music m(t, a, y, g);
                data.push_back(m); // add data vector movie obje
            }
            catch (const DuplicateEntry &e)
            {
                // print dublicate exception

                out << "Exception: " << e.what() << endl;

                out << "\"" << t << "\" "
                    << "\"" << a << "\" "
                    << "\"" << y << "\" "
                    << "\"" << g << "\" " << endl;
            }
            catch (const MissingField &e)
            {
                // print missing exception
                out << "Exception: " << e.what() << endl;
                out << (t.empty() ? "" : "\"" + t + "\" ")
                    << (a.empty() ? "" : "\"" + a + "\" ")
                    << (y.empty() ? "" : "\"" + y + "\" ")
                    << (g.empty() ? "" : "\"" + g + "\" ") << endl;
            }
        }

        out << "\"" << data.size() << " unique entries\"" << endl;

        string line2;
        ifstream file1("command.txt"); // Open the command.txt file for reading
        while (std::getline(file1, line2))
        {
            string type, search, in, field; // read type search in and field
            int flag = 0;
            try
            {
                stringstream s(line2);

                s >> type;
                if (type == "search") // If the command is 'search'
                {

                    getline(s, search, '\"'); // get the search
                    getline(s, search, '\"');

                    s >> in; // Read 'in' keyword

                    getline(s, field, '\"'); // get the field
                    getline(s, field, '\"');

                    if (field != "title" && field != "artist" && field != "year" && field != "genre")
                    {
                        flag = 1;
                        throw WrongCommand(); // Throw an exception if the field name is not valid
                    }

                    else
                    {

                        // write type search in and field
                        out << type << " "
                            << "\"" << search << "\""
                            << " " << in << " "
                            << "\"" << field << "\"" << endl;
                    }

                    Search(search, field, out); // search fonction
                }

                else if (type == "sort") // If the command is 'sort'
                {

                    getline(s, field, '\"'); // get the field
                    getline(s, field, '\"');

                    if (field != "title" && field != "artist" && field != "year" && field != "genre")
                    {
                        flag = 2;
                        throw WrongCommand(); // Throw an exception if the field name is not valid
                    }
                    else
                    {
                        out << type << " "
                            << "\"" << field << "\"" << endl;
                    }
                    sort(field); // sort fonction

                    for (auto item : data) // print data
                    {
                        out << "\"" << item.getTitle() << "\" "
                            << "\"" << item.getArtist() << "\" "
                            << "\"" << item.getYear() << "\" "
                            << "\"" << item.getGenre() << endl;
                    }
                }
                else
                {
                    throw WrongCommand(); // Throw an exception if the field name is not valid
                }
            }
            catch (const WrongCommand &e)
            {
                if (flag == 1)
                {
                    out << e.what() << std::endl;
                    // Print the command type,search,in,field
                    out << type << " ";
                    out << "\"" << search << "\" ";
                    out << in << " ";
                    out << "\"" << field << "\""
                        << "\n";
                }
                if (flag == 2)
                {
                    out << e.what() << std::endl; // Print the exception message to the output file

                    out << type << " "; // print type

                    out << "\"" << field << "\""
                        << "\n"; // print field
                }
            }
        }
    }

    void music::Search(string &keyword, string &field, ofstream &out)
    {
        bool found = false;

        if (field == "title")
        {
            for (auto &entry : data)
            {
                if (entry.getTitle().find(keyword) != std::string::npos)
                {
                    // print title,artist,year,genre
                    out << "\"" << entry.getTitle() << "\""
                        << " \"" << entry.getArtist() << "\""
                        << " \"" << entry.getYear() << " \""
                        << "\"" << entry.getGenre() << endl;

                    break;
                }
            }
        }
        else if (field == "artist")
        {
            for (auto &entry : data)
            {
                if (entry.getArtist().find(keyword) != std::string::npos)
                {
                    // print title,artist,year,genre
                    out << "\"" << entry.getTitle() << "\""
                        << " \"" << entry.getArtist() << "\""
                        << " \"" << entry.getYear() << " \""
                        << "\"" << entry.getGenre() << endl;

                    break;
                }
            }
        }
        else if (field == "year")
        {
            for (auto &entry : data)
            {
                if (entry.getYear().find(keyword) != std::string::npos)
                {
                    // print title,artist,year,genre
                    out << "\"" << entry.getTitle() << "\""
                        << " \"" << entry.getArtist() << "\""
                        << " \"" << entry.getYear() << " \""
                        << "\"" << entry.getGenre() << endl;

                    break;
                }
            }
        }
        else if (field == "genre")
        {
            for (auto &entry : data)
            {
                if (entry.getGenre().find(keyword) != std::string::npos)
                {
                    // print title,artist,year,genre
                    out << "\"" << entry.getTitle() << "\""
                        << " \"" << entry.getArtist() << "\""
                        << " \"" << entry.getYear() << " \""
                        << "\"" << entry.getGenre() << endl;

                    break;
                }
            }
        }
    }

    void music::sort(const std::string &field)
    {
        if (field == "title")
        {
            // Sort the data vector based on the title field
            std::sort(data.begin(), data.end(), [](const music &entry1, const music &entry2)
                      { return entry1.getTitle() < entry2.getTitle(); });
        }
        else if (field == "artist")
        {
            // Sort the data vector based on the artist field
            std::sort(data.begin(), data.end(), [](const music &entry1, const music &entry2)
                      { return entry1.getArtist() < entry2.getArtist(); });
        }
        else if (field == "year")
        {
            // Sort the data vector based on the year field
            std::sort(data.begin(), data.end(), [](const music &entry1, const music &entry2)
                      { return entry1.getYear() < entry2.getYear(); });
        }
        else if (field == "genre")
        {
            // Sort the data vector based on the genre field
            std::sort(data.begin(), data.end(), [](const music &entry1, const music &entry2)
                      { return entry1.getGenre() < entry2.getGenre(); });
        }
    }

    music::~music() {}
}