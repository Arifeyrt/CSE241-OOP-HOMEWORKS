#include <iostream> 
using namespace std;
/**  * This function will throw exception with current_level iostream
 * * equal to exception_level  * This exception will be caught in main.  *   */
void throw_exception_at(int current_level, int exception_level)
{
    if (current_level != exception_level)
    {
        cout << "calling depth :" << current_level << endl;
        throw_exception_at(current_level + 1, exception_level);
    }
    throw "Exception thrown at level ";
    return;
}
int main()
{
    int level = 0;
    cout << "Enter level to throw exception at : ";
    cin >> level;
    try
    {
        throw_exception_at(0, level);
    }
    catch (char const *msg)
    {
        cout << msg << level << endl;
    }
}