#include <iostream>
#include <string>

using namespace std;

class DynamicStringArray {
private:
    string* dynamicArray;
    int size;
public:
    //Default constructor
    DynamicStringArray() : dynamicArray(nullptr), size(0) {}

    //Copy constructor
    DynamicStringArray(const DynamicStringArray& source);

    //Assignment operator
    DynamicStringArray& operator=(const DynamicStringArray& source);

    //Destructor
    ~DynamicStringArray();

    int getSize() const { return size; }

    void addEntry(const string& str);

    bool deleteEntry(const string& str);

    string getEntry(int index) const;

};

DynamicStringArray::DynamicStringArray(const DynamicStringArray& source)
    : dynamicArray(nullptr), size(source.size)
{
    if (source.dynamicArray != nullptr) {
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = source.dynamicArray[i];
        }
    }
}

DynamicStringArray& DynamicStringArray::operator=(const DynamicStringArray& source)
{
    if (this == &source)
        return *this;

    delete[] dynamicArray;
    dynamicArray = nullptr;
    size = source.size;

    if (source.dynamicArray != nullptr) {
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = source.dynamicArray[i];
        }
    }
    return *this;
}

DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}

void DynamicStringArray::addEntry(const string& str)
{
    string* temp = new string[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = dynamicArray[i];
    }
    temp[size] = str;
    delete[] dynamicArray;
    dynamicArray = temp;
    size++;
}

bool DynamicStringArray::deleteEntry(const string& str)
{
    int indexToDelete = -1;
    for (int i = 0; i < size; i++) {
        if (dynamicArray[i] == str) {
            indexToDelete = i;
            break;
        }
    }
    if (indexToDelete == -1) {
        return false;
    }
    string* temp = new string[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != indexToDelete) {
            temp[j++] = dynamicArray[i];
        }
    }
    delete[] dynamicArray;
    dynamicArray = temp;
    size--;
    return true;
}

string DynamicStringArray::getEntry(int index) const
{
    if (index < 0 || index >= size) {
        return "";
    }
    return dynamicArray[index];
}

int main()
{
DynamicStringArray names;
// List of names
names.addEntry("Frank");
names.addEntry("Wiggum");
names.addEntry("Nahasapeemapetilon");
names.addEntry("Quimby");
names.addEntry("Flanders");
// Output list
cout << "List of names:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
// Add and remove some names
names.addEntry("Spuckler");
cout << "After adding a name:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
names.deleteEntry("Nahasapeemapetilon");
cout << "After removing a name:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
names.deleteEntry("Skinner");
cout << "After removing a name that isn't on the list:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
names.addEntry("Muntz");
cout << "After adding another name:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
// Remove all of the names by repeatedly deleting the last one
while (names.getSize() > 0) {
names.deleteEntry(names.getEntry(names.getSize() - 1));
}
cout << "After removing all of the names:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
names.addEntry("Burns");
cout << "After adding a name:" << endl;
for (int i = 0; i < names.getSize(); i++)
cout << names.getEntry(i) << endl;
cout << endl;
cout << "Testing copy constructor" << endl;
DynamicStringArray names2(names);
// Remove Burns from names
names.deleteEntry("Burns");
cout << "Copied names:" << endl;
for (int i = 0; i < names2.getSize(); i++)
cout << names2.getEntry(i) << endl;
cout << endl;
cout << "Testing assignment" << endl;
DynamicStringArray names3 = names2;
// Remove Burns from names2
names2.deleteEntry("Burns");
cout << "Copied names:" << endl;
for (int i = 0; i < names3.getSize(); i++)
cout << names3.getEntry(i) << endl;
cout << endl;
return 0;}