#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Pixel
{
    int r;
    int g;
    int b;
};
class ppmImage{
public:
    // Constructor
    ppmImage(string filename);
    ppmImage(const int w, const int h);
    ppmImage();  // default consturcter

    //functions
    void saveimage(const string filename) const;// To save to /PPM file
    void readimage(const string filename);       // To read a PPM image in a file
    int getWidth() const { return width; }       // accessor
    int getHeight() const { return height; }     // accessor
    int getMaxPixelValue() { return maxPixelValue; }
    vector<Pixel> getPixelData() { return pixelData; }
    Pixel getPixelvalue(int index) const { return pixelData[index]; } // Rotate the pixel in the specified index
    void setHeight(int newHeight)
    {
        if (newHeight < 0)
            newHeight = 0;
        height = newHeight;
    }
    void setWidth(int newWidth)// To change the width value
    {
        if (newWidth < 0)
            newWidth = 0;
        width = newWidth;
    }
    void setMaxPixelValue(int newMaxPixelValue) { maxPixelValue = newMaxPixelValue; }//To change the maximum pixel value

    void setPixelData(vector<Pixel> newPixelData) { pixelData = newPixelData; }
    void printDim() // To print the dimensions of the PPM image
    {
        cout << height << " x " << width << endl;
    }

    Pixel &getPixel(int index, ppmImage &other)// To retrieve the pixel in the specified index

    {
        return other.pixelData[index];
    }
    int getPixel(int index, int color_channel) // To return the specified color channel of the pixel in the specified index
    {
        switch (color_channel)
        {
        case 0:
            return pixelData[index].r;
            break;
        case 1:
            return pixelData[index].g;
            break;
        case 2:
            return pixelData[index].b;
            break;
        default:
            exit(1);
            break;
        }
    }
    void setPixel(int index, Pixel pixel)// To replace the pixel in the specified index with the specified pixel value
    {
        pixelData[index].r = pixel.r;
        pixelData[index].g = pixel.g;
        pixelData[index].b = pixel.b;
    }


    //OPERATORS
    ppmImage operator+(const ppmImage &other);
    ppmImage operator-(const ppmImage &other);
    int &operator()(int row, int col, int channel);
    const int &operator()(int row, int col, int channel) const;
    friend ostream &operator<<(ostream &os, const ppmImage &img);

private:
    int height;               //the height of the image
    int width;               //  the width of the image
    int maxPixelValue;       //  the max mixel value of the image
    vector<Pixel> pixelData; //  //vector
};


// Default constructor resets all members.
ppmImage::ppmImage()
{
    width = 0;
    height = 0;
    maxPixelValue = 0;
}

//the filename argument reads the ppm image from the supplied file and sets the maxPixelValue value to 255.
ppmImage::ppmImage(string filename)
{
    readimage(filename);
    maxPixelValue = 255;
}

// Creates an empty ppm image given the width and height arguments. The pixels are set to black by default.
ppmImage::ppmImage(int w, int h)
{
    if (w < 0 || h < 0)
        exit(1);
    pixelData.resize(w * h);
    Pixel white = {0, 0, 0};
    for (int i = 0; i < w * h; i++)
    {
        pixelData[i] = white;
    }
    maxPixelValue = 255;
    width = w;
    height = h;
}

//saves the filename argument to the given file in ppm format.
void ppmImage::saveimage(string filename) const
{ 
    ofstream file(filename);
    if (!file.is_open())
    {
        exit(1);
    }
    string format = "P3";
    file << format << endl;

    file << width << " " << height << "\n";
    file << 255<<endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            file << pixelData[i * height + j].r << " " << pixelData[i * height + j].g << " " << pixelData[i * height + j].b << " ";
        }
       file << endl;
    }
   
}

//the filename argument reads the ppm image from the given file.
void ppmImage::readimage(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        exit(1);
    }
    string format;
    file >> format;
    if (format != "P3")
    {
        cout << "Invalid format!" << endl;
        exit(1);
    }
    file >> width >> height;
    file >> maxPixelValue;

    pixelData.resize(width * height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, g, b;
            file >> r >> g >> b;
            pixelData[i * height + j] = {r, g, b};
        }
        cout << "\n";
    }
}

ppmImage ppmImage::operator+(const ppmImage &other){
   // If the dimensions of the two images are not the same, terminate the program
    if (this->getWidth() != other.getWidth() || this->getHeight() != other.getHeight())
    {
        exit(0); // Exit if dimensions don't match
    }
    
    // Create a new ppmImage object named Result
    ppmImage result(getWidth(), getHeight());
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            int idx = i * width + j;
            int red = pixelData[idx].r + other.pixelData[idx].r;
            int green = pixelData[idx].g + other.pixelData[idx].g;
            int blue = pixelData[idx].b + other.pixelData[idx].b;
            Pixel p1;
            p1.r = red;
            p1.g = green;
            p1.b = blue;
           // if it is greater than 255, make it 255
            if (p1.r > 255) p1.r = 255;
            if (p1.g > 255) p1.g = 255;
            if (p1.b > 255) p1.b = 255;

            result.pixelData[idx] = p1;
        }
    }
    return result;
}


ppmImage ppmImage::operator-(const ppmImage &other){
    // If the dimensions of the two images are not the same, terminate the program
    if (getWidth() != other.getWidth() || getHeight() != other.getHeight())
    {
        exit(0); // Exit if dimensions don't match
    }

    // Create a new ppmImage object named Result
    ppmImage result(getWidth(), getHeight());

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = i * width + j;
            int red = pixelData[idx].r - other.pixelData[idx].r;
            int green = pixelData[idx].g - other.pixelData[idx].g;
            int blue = pixelData[idx].b - other.pixelData[idx].b;
            Pixel p1;
            p1.r = red;
            p1.g = green;
            p1.b = blue;
            if (p1.r < 0)
                p1.r = 0;
            if (p1.g < 0)
                p1.g = 0;
            if (p1.b < 0)
                p1.b = 0;

            // Yeni resim nesnesinin pixelData dizisine yeni piksel ekle
            result.pixelData[idx] = p1;
        }
    }
    return result;
}

// the << operator has been overloaded to print the ppmImage object via ostream
ostream &operator<<(ostream &os, const ppmImage &img)
{
    os << "P3" << endl;
    os << img.getWidth() << " " << img.getHeight() << endl;
    os << "255" << endl;
    for (int i = 0; i < img.getHeight(); i++)
    {
        for (int j = 0; j < img.getWidth(); j++)
        {

            Pixel p = img.getPixelvalue(i * img.getWidth() + j);
            os << p.r << " " << p.g << " " << p.b << " ";
        }
        os << endl;
    }
    return os;
}

// The () operator that returns the reference of the pixel in the specified row, column, and channel values
int &ppmImage::operator()(int row, int col, int channel)
{
    int index = row * width + col;
    switch (channel)
    {
    case 1:
        return pixelData[index].r;
        break;
    case 2:
        return pixelData[index].g;
        break;
    case 3:
        return pixelData[index].b;
        break;
    default:
        exit(1);
    }
}

// The () operator that returns the fixed reference of the pixel in the specified row, column, and channel values
const int &ppmImage::operator()(int row, int col, int channel) const
{
    int index = row * width + col;
    switch (channel)
    {
    case 1:
        return pixelData[index].r;
        break;
    case 2:
        return pixelData[index].g;
        break;
    case 3:
        return pixelData[index].b;
        break;
    default:
        exit(1);
    }
}



//************************* TEST FUNCTİONS********************************//
///////////////////////////////////////////////////////////////////////

// This function reads the specified PPM file and assigns its contents to destination_object.
int read_ppm(const string source_ppm_file_name, ppmImage &destination_object)
{
    destination_object.readimage(source_ppm_file_name);
    return 1;
}

// This function write the specified PPM file and assigns its contents to destination_object.
int write_ppm(const string destination_ppm_file_name, const ppmImage &source_object)
{
    source_object.saveimage(destination_ppm_file_name);
    return 1;
}


// This function reads filename_image1 and filename_image2 and saves the sum of them to filename_image3.
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);
    if (image1.getWidth() != image2.getWidth() || image1.getHeight() != image2.getHeight())
        return 0;
    ppmImage image3 = image1 + image2;
    image3.saveimage(filename_image3);
    return 1;
}


// This function extracts filename_image2 from filename_image1 and saves the result to filename_image3.
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);

    if (image1.getWidth() != image2.getWidth() || image1.getHeight() != image2.getHeight())
        return 0;
    ppmImage image3 = image1 - image2;
    image3.saveimage(filename_image3);
    return 1;
}

// This function prints the PPM image in filename_image1 to the screen.
int test_print(const string filename_image1)
{
    ppmImage image(filename_image1);
    cout << image;
    return 1;
}

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice)
{
    int result = 1;
    for (int i = 0; i < image_object_to_be_modified.getHeight(); i++)
    {
        for (int j = 0; j < image_object_to_be_modified.getWidth(); j++)
        {
            int &red = image_object_to_be_modified(i, j, 1);
            int &green = image_object_to_be_modified(i, j, 2);
            int &blue = image_object_to_be_modified(i, j, 3);

            if (swap_choice == 1)
            { // red green
                int temp = red;
                red = green;
                green = temp;
            }
            else if (swap_choice == 2)
            { // red blue
                int temp = red;
                red = blue;
                blue = temp;
            }
            else if (swap_choice == 3)
            { // blue green
                int temp = green;
                green = blue;
                blue = temp;
            }
            else
                result = 0;
        }
    }

    return result;
}
ppmImage single_color(const ppmImage &source, int color_choice)
{
    ppmImage copy_source(source.getWidth(), source.getHeight());

    // It loops for every pixel in the source image
    for (int i = 0; i < source.getHeight(); i++)
    {
        for (int j = 0; j < source.getWidth(); j++)
        {    
            // Accesses color channels by loop
            for (int c = 1; c <= 3; c++)
            {
                if (c == color_choice)// Copies the value for the selected color channel
                {
                    copy_source(i, j, c) = source(i, j, c);
                }
                else
                    copy_source(i, j, c) = 0;// Makes the value of the other color channels 0
            }
        }
    }
    return copy_source;
}

int main(int argc, char **argv)
{
    if (argc == 4 || argc == 5) // If the number of arguments is 4 or 5, the process continues.
    {
        int choice = atoi(argv[1]);
        string ppm_file_name1 = argv[2];//first file name
        string ppm_file_name2 = argv[3];//second file name
        string ppm_file_name3;//The third file name that is required
        ppmImage image1;// The first image to be processed
        ppmImage image2;// The second image to be processed
        switch (choice)
        {
        case 1:
            if (argc == 5)
            {
                ppm_file_name3 = argv[4];
                test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);// Performs the process of reading and collecting files
            }
            else
                exit(1);
            break;
        case 2:
            if (argc == 5)
            {
                ppm_file_name3 = argv[4];
                test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);// Performs the process of reading and extracting files
            }
            else
                exit(1);
            break;
        case 3:
            if (read_ppm(ppm_file_name1, image1) == 1)
            {
                swap_channels(image1, 2);// Changes the red and blue color channels
                write_ppm(ppm_file_name2, image1);
            }
            break;
        case 4:
            if (read_ppm(ppm_file_name1, image1) == 1)
            {
                swap_channels(image1, 3);// Changes the green and blue color channels
                write_ppm(ppm_file_name2, image1);
            }
            break;
        case 5:
            if (read_ppm(ppm_file_name1, image1) == 1)
            {
                image2 = single_color(image1, 1);// Creates an image that contains only the color red

                write_ppm(ppm_file_name2, image2);
            }
            break;
        case 6:
            if (read_ppm(ppm_file_name1, image1) == 1)
            {
                image2 = single_color(image1, 2);// Creates an image that contains only the color green

                write_ppm(ppm_file_name2, image2);
            }
            break;
        case 7:
            if (read_ppm(ppm_file_name1, image1) == 1)
            {
                image2 = single_color(image1, 3);// Creates an image that contains only the color blue

                write_ppm(ppm_file_name2, image2);
            }
            break;
        default:
            break;
        }
    }
    else
        exit(1);

    return 0;
}