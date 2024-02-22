#include "book.h"
#include "exception.h"

namespace PA6
{
    // Default constructor
    book::book()
    {
        title = "";
        author = "";
        year = "";
        tags = "";
    }

    // CONSTRUCTER
    book::book(const string &_title, const string &_author, string &_year, const string &_tags)
        : title(_title), author(_author), year(_year), tags(_tags) {}

    ///***************GET****************/////
    string book::getTitle() const { return title; }
    string book::getAuthor() const { return author; }
    string book::getYear() const { return year; }
    string book::getTag() const { return tags; }

    // READ FONCTION
    void book::read()
    {
        ifstream file("data.txt");  // Open the data.txt file for reading
        ofstream out("output.txt"); // Open the output.txt file for writing
        string line;
        string field;
        int count = 0;

        // Read the first line and get the catalog type
        getline(file, line);
        catalogType = line;
        out << "Catalog read: " << catalogType << endl;
        int wrong; // missing or duplicate expression write
        string title_, author_, year_, tags_;
        while (getline(file, line))
        {
            count = 0;
            try
            {
                istringstream split_line(line); // Create a string stream to split the line

                for (char c : line)
                {
                    if (c == '\"')
                    {
                        // If the character is a double quote
                        count++; // Increment the count
                    }
                }
                // Extract the data from each line
                getline(split_line, title_, '\"'); // Get the title
                getline(split_line, title_, '\"'); // Get the title again (assuming it was duplicated in the original code)

                getline(split_line, author_, '\"'); //// Get the director
                getline(split_line, author_, '\"'); // Get the director again

                getline(split_line, year_, '\"'); // get the year
                getline(split_line, year_, '\"'); // get the year again

                getline(split_line, tags_, '\"');
                getline(split_line, tags_, '\"');

                wrong = 0;
                // missing field exception

                if (title_.empty() || author_.empty() || year_.empty() || tags_.empty())
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
                    if (data[i].getTitle() == title_)
                    {
                        wrong = 2;
                        throw DuplicateEntry();
                    }
                }
                book b(title_, author_, year_, tags_); // get book constructer
                data.push_back(b);                     // add data vector book
            }
            catch (const DuplicateEntry &e)
            {
                // write dublicate exception
                out << "Exception: " << e.what() << endl;

                out << "\"" << title_ << "\" "
                    << "\"" << author_ << "\" "
                    << "\"" << year_ << "\" "
                    << "\"" << tags_ << "\" " << endl;
            }
            catch (const MissingField &e)
            {
                out << "Exception: " << e.what() << endl;
                // write missing exception
                out << (title_.empty() ? "" : "\"" + title_ + "\" ")
                    << (author_.empty() ? "" : "\"" + author_ + "\" ")
                    << (year_.empty() ? "" : "\"" + year_ + "\" ")
                    << (tags_.empty() ? "" : "\"" + tags_ + "\" ") << endl;
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

                    if (field != "title" && field != "author" && field != "year" && field != "tags")
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

                    Search(search, field, out);
                }
                else if (type == "sort") // If the command is 'sort'
                {

                    getline(s, field, '\"'); // get the field
                    getline(s, field, '\"');

                    if (field != "title" && field != "artist" && field != "year" && field != "tags")
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
                            << "\"" << item.getAuthor() << "\" "
                            << "\"" << item.getYear() << "\" "
                            << "\"" << item.getTag() << endl;
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
                    out << e.what() << std::endl;

                    out << type << " "; // print type
                    out << "\"" << field << "\""
                        << "\n"; // print field
                }
            }
        }
    }

    void book::Search(string &keyword, string &field, ofstream &out)
    {
        bool found = false;

        if (field == "title")
        {
            for (auto &entry : data)
            {
                if (entry.getTitle().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""   // print the title
                        << " \"" << entry.getAuthor() << "\"" // print the author
                        << " \"" << entry.getYear() << " \""  // print the year
                        << "\"" << entry.getTag() << endl;    // print the tags

                    break;
                }
            }
        }
        else if (field == "author")
        {
            for (auto &entry : data)
            {
                if (entry.getAuthor().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""   // print the title
                        << " \"" << entry.getAuthor() << "\"" // print the author
                        << " \"" << entry.getYear() << " \""  // print the year
                        << "\"" << entry.getTag() << endl;    // print the tags

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
                    out << "\"" << entry.getTitle() << "\""   // print the title
                        << " \"" << entry.getAuthor() << "\"" // print the author
                        << " \"" << entry.getYear() << " \""  // print the year
                        << "\"" << entry.getTag() << endl;    // print the tags

                    break;
                }
            }
        }
        else if (field == "tags")
        {
            for (auto &entry : data)
            {
                if (entry.getTag().find(keyword) != std::string::npos)
                {
                    out << "\"" << entry.getTitle() << "\""   // print the title
                        << " \"" << entry.getAuthor() << "\"" // print the author
                        << " \"" << entry.getYear() << " \""  // print the year
                        << "\"" << entry.getTag() << endl;    // print the tags

                    break;
                }
            }
        }
    }

    void book::sort(const std::string &field)
    {
        if (field == "title")
        {
            // Sort the data vector based on the title field
            std::sort(data.begin(), data.end(), [](const book &entry1, const book &entry2)
                      { return entry1.getTitle() < entry2.getTitle(); });
        }
        else if (field == "author")
        {
            // Sort the data vector based on the author field
            std::sort(data.begin(), data.end(), [](const book &entry1, const book &entry2)
                      { return entry1.getAuthor() < entry2.getAuthor(); });
        }
        else if (field == "year")
        {
            // Sort the data vector based on the year field
            std::sort(data.begin(), data.end(), [](const book &entry1, const book &entry2)
                      { return entry1.getYear() < entry2.getYear(); });
        }
        else if (field == "tags")
        {
            // Sort the data vector based on the tags field
            std::sort(data.begin(), data.end(), [](const book &entry1, const book &entry2)
                      { return entry1.getTag() < entry2.getTag(); });
        }
    }

    book::~book() {}
}