#include "movie.h"
#include "exception.h"
namespace PA6
{
    // Default constructor
    movie::movie()
    {
        title = "";
        director = "";
        year = "";
        genre = "";
        starring = "";
    }

    // CONSTRUCTER
    movie::movie(const string &_title, const string &_director, string &_year, const string &_genre, const string &_starring)
        : title(_title), director(_director), year(_year), genre(_genre), starring(_starring) {}

    ///***************GET****************/////
    string movie::getTitle() const { return title; }
    string movie::getDirector() const { return director; }
    string movie::getYear() const { return year; }
    string movie::getGenre() const { return genre; }
    string movie::getStarring() const { return starring; }

    // READ FONCTION
    void movie::read()
    {
        ifstream file("data.txt"); // Open the data.txt file for reading
        ofstream out("output.txt");
        string line;
        string field;
        int count = 0;

        // Read the first line and get the catalog type
        getline(file, line);
        catalogType = line; // catalogtype
        int wrong;          // missing or duplicate expression write
        out << "Catalog read: " << catalogType << endl;
        string title_, director_, year_, genre_, starring_;
        while (getline(file, line))
        {
            count = 0;
            try
            {

                istringstream split_line(line); // Create a string stream to split the line

                for (char c : line)
                {
                    if (c == '\"')
                    {            // If the character is a double quote
                        count++; // Increment the count
                    }
                }

                // Extract the data from each line
                getline(split_line, title_, '\"'); // Get the title
                getline(split_line, title_, '\"'); // Get the title again (assuming it was duplicated in the original code)

                getline(split_line, director_, '\"'); //// Get the director
                getline(split_line, director_, '\"'); // Get the director again

                getline(split_line, year_, '\"'); // get the year
                getline(split_line, year_, '\"'); // get the year again

                getline(split_line, genre_, '\"'); // get the genre
                getline(split_line, genre_, '\"'); // get the genre again

                getline(split_line, starring_, '\"'); // get the starring
                getline(split_line, starring_, '\"'); // get the starring again

                wrong = 0;
                // missing field exception
                if (title_.empty() || director_.empty() || year_.empty() || genre_.empty() || starring_.empty())
                {
                    if (count != 10)
                    {
                        wrong = 1;
                        throw MissingField();
                    }
                }

                // dublicate enty exception
                for (int i = 0; i < data.size(); i++)
                {
                    if (data[i].getTitle() == title_)
                    {
                        wrong = 2;
                        throw DuplicateEntry();
                    }
                }

                movie mo(title_, director_, year_, genre_, starring_); // get movie constructer
                data.push_back(mo);                                    // add data vector movie obje
            }
            catch (const DuplicateEntry &e)
            {
                // write dublicate exception
                out << "Exception: " << e.what() << endl;

                out << "\"" << title_ << "\" "
                    << "\"" << director_ << "\" "
                    << "\"" << year_ << "\" "
                    << "\"" << genre_ << "\" "
                    << "\"" << starring_ << "\" " << endl;
            }
            catch (const MissingField &e)
            {
                out << "Exception: " << e.what() << endl;

                // write missing exception
                out << (title_.empty() ? "" : "\"" + title_ + "\" ")
                    << (director_.empty() ? "" : "\"" + director_ + "\" ")
                    << (year_.empty() ? "" : "\"" + year_ + "\" ")
                    << (genre_.empty() ? "" : "\"" + genre_ + "\" ")
                    << (starring_.empty() ? "" : "\"" + starring_ + "\" ") << endl;
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

                    if (field != "title" && field != "director" && field != "year" && field != "genre" && field != "starring")
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

                    if (field != "title" && field != "director" && field != "year" && field != "genre" && field != "starring")
                    {
                        flag = 2;
                        throw WrongCommand(); // Throw an exception if the field name is not valid
                    }

                    else
                    {
                        out << type << " "
                            << "\"" << field << "\"" << endl;
                    }
                    sort(field); // Sort fonction

                    for (auto item : data) // write data
                    {
                        out << "\"" << item.getTitle() << "\" "
                            << "\"" << item.getDirector() << "\" "
                            << "\"" << item.getYear() << "\" "
                            << "\"" << item.getGenre() << "\" "
                            << "\"" << item.getStarring() << endl;
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

    void movie::Search(string &keyword, string &field, ofstream &out)
    {
        bool found = false;

        if (field == "title")
        {
            for (auto &entry : data)
            {
                if (entry.getTitle().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""     // Print the title
                        << " \"" << entry.getDirector() << "\"" // Print the director
                        << " \"" << entry.getYear() << " \""    // Print the year
                        << "\"" << entry.getGenre() << " \""    // Print the genre
                        << "\"" << entry.getStarring() << endl; // Print the starring

                    break;
                }
            }
        }
        else if (field == "director")
        {
            for (auto &entry : data)
            {
                if (entry.getDirector().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""     // Print the title
                        << " \"" << entry.getDirector() << "\"" // Print the director
                        << " \"" << entry.getYear() << " \""    // Print the year
                        << "\"" << entry.getGenre() << " \""    // Print the genre
                        << "\"" << entry.getStarring() << endl; // Print the starring

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
                    out << "\"" << entry.getTitle() << "\""     // Print the title
                        << " \"" << entry.getDirector() << "\"" // Print the director
                        << " \"" << entry.getYear() << " \""    // Print the year
                        << "\"" << entry.getGenre() << " \""    // Print the genre
                        << "\"" << entry.getStarring() << endl; // Print the starring

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
                    out << "\"" << entry.getTitle() << "\""     // Print the title
                        << " \"" << entry.getDirector() << "\"" // Print the director
                        << " \"" << entry.getYear() << " \""    // Print the year
                        << "\"" << entry.getGenre() << " \""    // Print the genre
                        << "\"" << entry.getStarring() << endl; // Print the starring
                    break;
                }
            }
        }

        else if (field == "starring")
        {
            for (auto &entry : data)
            {
                if (entry.getStarring().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""     // Print the title
                        << " \"" << entry.getDirector() << "\"" // Print the director
                        << " \"" << entry.getYear() << " \""    // Print the year
                        << "\"" << entry.getGenre() << " \""    // Print the genre
                        << "\"" << entry.getStarring() << endl; // Print the starring
                    break;
                }
            }
        }
    }

    void movie::sort(const std::string &field)
    {
        if (field == "title")
        {
            // Sort the data vector based on the title field
            std::sort(data.begin(), data.end(), [](const movie &entry1, const movie &entry2)
                      { return entry1.getTitle() < entry2.getTitle(); });
        }
        else if (field == "director")
        {
            // Sort the data vector based on the director field
            std::sort(data.begin(), data.end(), [](const movie &entry1, const movie &entry2)
                      { return entry1.getDirector() < entry2.getDirector(); });
        }
        else if (field == "year")
        {
            // Sort the data vector based on the year field
            std::sort(data.begin(), data.end(), [](const movie &entry1, const movie &entry2)
                      { return entry1.getYear() < entry2.getYear(); });
        }
        else if (field == "genre")
        {
            // Sort the data vector based on the genre field
            std::sort(data.begin(), data.end(), [](const movie &entry1, const movie &entry2)
                      { return entry1.getGenre() < entry2.getGenre(); });
        }
        else if (field == "starring")
        {
            // Sort the data vector based on the starring field
            std::sort(data.begin(), data.end(), [](const movie &entry1, const movie &entry2)
                      { return entry1.getStarring() < entry2.getStarring(); });
        }
    }

    movie::~movie() {}

}
