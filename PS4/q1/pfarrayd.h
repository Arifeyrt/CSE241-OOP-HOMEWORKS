#ifndef PFARRAYD_H
#define PFARRAYD_H

#include <string>
using std::string;

class Exception
{};

class OutOfRange : public Exception
{
public:
    OutOfRange(string thisMessage, int thisIndex);
    string getMessage() const;
    int getIndex() const;

private:
    string message;
    int index;
};

// Objects of this class are partially filled arrays of doubles.
class PFArrayD
{
public:
    PFArrayD(); // Initializes with a capacity of 50.
    PFArrayD(int capacityValue);
    PFArrayD(const PFArrayD& pfaObject);
    void addElement(double element); // Precondition: The array is not full. Postcondition: The element has been added.
    bool full() const { return (capacity == used); } // Returns true if the array is full, false otherwise.
    int getCapacity() const { return capacity; }
    int getNumberUsed() const { return used; }
    void emptyArray() { used = 0; } // Empties the array.
    double& operator[](int index); // Read and change access to elements 0 through numberUsed-1.
    PFArrayD& operator=(const PFArrayD& rightSide);
    ~PFArrayD();

private:
    double* a; // For an array of doubles.
    int capacity; // For the size of the array.
    int used; // For the number of array positions currently in use.
};



OutOfRange::OutOfRange(string thisMessage, int thisIndex)
{
    message = thisMessage;
    index = thisIndex;
}

string OutOfRange::getMessage() const
{
    return message;
}

int OutOfRange::getIndex() const
{
    return index;
}

PFArrayD::PFArrayD()
{
    capacity = 50;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue)
{
    capacity = capacityValue;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD &pfaObject)
{
    capacity = pfaObject.capacity;
    used = pfaObject.used;
    a = new double[capacity];
    for (int i = 0; i < used; i++)
        a[i] = pfaObject.a[i];
}

void PFArrayD::addElement(double element)
{
    if (used >= capacity)
        throw OutOfRange("Cannot add element. Array capacity exceeded.", used);
    a[used] = element;
    used++;
}

double &PFArrayD::operator[](int index) 
{
    if (index < 0 || index >= used)
        throw OutOfRange("Invalid index. Out of range.", index);
    return a[index];
}

PFArrayD &PFArrayD::operator=(const PFArrayD &rightSide)
{
    if (this == &rightSide)
        return *this;

    if (capacity != rightSide.capacity)
    {
        delete[] a;
        a = new double[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;

    for (int i = 0; i < used; i++)
        a[i] = rightSide.a[i];

    return *this;
}

PFArrayD::~PFArrayD()
{
    delete[] a;
}


#endif // PFARRAYD_H