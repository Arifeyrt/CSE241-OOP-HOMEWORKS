#include <iostream>
#include <string>
using namespace std;

template<typename T1, typename T2>
class Pair{
    private:
        T1 first;
        T2 second;
    public:
        Pair(T1 f, T2 s){
            first = f;
            second = s;
        }
        T1 getFirst(){
            return first;
        }
        void setFirst(T1 f){
            first = f;
        }
        T2 getSecond(){
            return second;
        }
        void setSecond(T2 s){
            second = s;
        }
};

int main(){
    Pair<char, char> p('A', 'B');
    cout << "First is " << p.getFirst() << endl;
    p.setFirst('Z');
    cout << "First changed to " << p.getFirst() << endl;
    cout << "The pair is: " << p.getFirst() << ", " << p.getSecond() << endl;

    Pair<int, string> p2(34, "Bill");
    cout << "The pair is: " << p2.getFirst() << ", " << p2.getSecond() << endl;

    Pair<string, int> p3("Bill", 34);
    cout << "The pair is: " << p3.getFirst() << ", " << p3.getSecond() << endl;

    return 0;
}
