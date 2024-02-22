#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ImageEditor
{
private:
    vector<vector<vector<int>>> pixelData; // 3D vector holding pixel data read from file
    int width;                             //Width of image read from file
    int height;                            //Height of image read from file
    int max_color_value;

public:
    void MainMenu()
    {
        int choice = 5;
        do
        {
            cout << "Main Menu" << endl;
            cout << "0 - Exit" << endl;
            cout << "1 - Open An Image(D)" << endl;
            cout << "2 - Save Image Data(D)" << endl;
            cout << "3 - Scripts(D)" << endl;
            cin >> choice;

            switch (choice)
            {
            case 0:
                cout << "Exiting program..." << endl;
                exit(1);
                break;
            case 1:
                openAnImage();
                break;
            case 2:
                saveImageData();
                break;
            case 3:
                scripts();
                break;
            default:
                cout << "the wrong choice.try again" << endl;
                break;
            }
        } while (choice != 0);
    }

    void openAnImage()
    {

        cout << "SAVE IMAGE DATA MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter The Name Of The Image File" << endl;
        int choice = -1;
        cin >> choice;
        cout << endl;
        do
        {
            switch (choice)
            {
            case 0:
                MainMenu();
                break;
            case 1:
                openImage(); // open file and read
                openAnImage();
                break;
            default:
                cout << "the wrong choice.try again" << endl;
                break;
            }
        } while (choice != -1);
    }
    void openImage()
    {
        string filename;
        cin >> filename;
        cout << endl;
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file." << endl;
            return;
        }
        string format;
        file >> format >> width >> height >> max_color_value;

        if (format != "P3")
        {
            cout << "Invalid format!" << endl;
            return;
        }
//I'm creating a 3D vector. I'm putting the pixels in the file into that vector.
        vector<vector<vector<int>>> t_pixelData(height, vector<vector<int>>(width, vector<int>(3)));
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int pixel_value;
                    file >> pixel_value;
                    if (pixel_value > max_color_value)
                    {
                        cout << "Error: Pixel value exceeds maximum color value." << endl;
                        return;
                    }
                    t_pixelData[i][j][k] = pixel_value;
                }
            }
        }
        pixelData = t_pixelData;
        // Do something with the image vector
    }

    void saveImageData()
    {

        cout << "SAVE IMAGE DATA MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter A File Name" << endl;
        int choice = -1;
        cin >> choice;
        cout << endl;
        do
        {
            switch (choice)
            {
            case 0:
                MainMenu();
                break;
            case 1:
                saveImage();
                saveImageData();
                break;
            default:
                cout << "the wrong choice.try again" << endl;
                break;
            }
        } while (choice != -1);
    }
    void saveImage()
    {

        string filename;
        cin >> filename;
        cout << endl;
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file." << endl;
        }
        // Write the image format, dimensions and maximum color value to the file
        file << "P3\n";
        file << width << " " << height << "\n";
        file << "255\n";
 //re-saves color pixels to a new file
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int pixel_value = pixelData[i][j][k];
                    if (pixel_value > 255)
                    {
                        cout << "Error: Pixel value exceeds maximum color value." << endl;
                    }
                    file << pixel_value << " ";
                }
                file << "\t";
            }
            file << "\n";
        }

        cout << filename << endl;
    }

    void scripts()
    {

        cout << "SCRIPT MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Convert To Grayscale" << endl;
        int choice = -1;
        cin >> choice;
        cout << endl;
        do
        {
            switch (choice)
            {
            case 0:
                MainMenu();
                break;
            case 1:
                ConvertToGrayscale();
                break;
            default:
                cout << "the wrong choice.try again" << endl;
                break;
            }
        } while (choice != -1);
    }
    void ConvertToGrayscale()
    {

        cout << "CONVERT TO GRAYSCALE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
        int choice = -1;
        cin >> choice;
        cout << endl;
        do
        {
            switch (choice)
            {
            case 0:
                MainMenu();
                break;
            case 1:
                convert();
                MainMenu();
                break;
            default:
                cout << "the wrong choice.try again" << endl;
                break;
            }
        } while (choice != -1);
    }
    void convert()
    {

        float num1, num2, num3;

        cin >> num1 >> num2 >> num3;

        int grayScale; // variable holding the graying value

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {

                grayScale = (int)(num1 * pixelData[i][j][0]) + (num2 * pixelData[i][j][1]) + (num3 * pixelData[i][j][2]);
                if (grayScale > 255)
                    grayScale = 255;

                pixelData[i][j][0] = grayScale;
                pixelData[i][j][1] = grayScale;
                pixelData[i][j][2] = grayScale;
            }
        }
        
    }
};

int main()
{
    ImageEditor image;
    image.MainMenu();

    return 0;
}