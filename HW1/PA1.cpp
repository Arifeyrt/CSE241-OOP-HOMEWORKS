#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

bool isValidNumber(char secretnum[], int size) {
    if (size < 1 || size > 9) { // if it is less than 1 or greater than 9 digits, it gives an E1 error
        cout << "E1" << endl;
        return false;
    }
    if (secretnum[0] == '0') { // the first digit cannot be 0
        cout << "EO" << endl;
        return false;
    }
    for (int i = 0; i < size; i++) { // should not contain any characters other than the numbers
        if (secretnum[i] < '0' || secretnum[i] > '9') {
            cout << "E2" << endl;
            return false;
        }
    }
    for (int i = 0; i < size; i++) { // the digits should be different from each other
        int digit = secretnum[i];
        for (int j = i + 1; j < size; j++) {
            if (digit == secretnum[j]) {
                cout << "E0" << endl;
                return false;
            }
        }
    }
    return true;
}

void Game(char num[], int N) {
    int count = 0;
    char numuser[N];
    int Cexact = 0;
    int Cmisplaced = 0;
    int digits = 0;
    do {
        Cexact = 0;
        Cmisplaced = 0;
        cin >> numuser;
        digits = strlen(numuser);
        
        if (digits != N) { // the size of the entered number and the secret number must be the same
            cout << "E1" << endl;
            break;
        }
       
        // error checking
        if (!isValidNumber(numuser, digits)) {
            break;
        }
        count++;
        if (count == 100) { // there is no right to try more than 100 times
            cout << "FAILED" << endl;
            break;
        }
        // finding exact and misplaced clues
        for (int i = 0; i < N; i++) { // comparing numbers at the same position
            if (numuser[i] == num[i]) {
                Cexact++;
            }
            for (int j = 0; j < N; j++) { // comparing numbers at different positions
                if (i != j && numuser[i] == num[j]) {
                    Cmisplaced++;
                }
            }
        }
        if (Cexact != N) {
            cout << Cexact << "  " << Cmisplaced << endl;
        }
        else {
            cout << "FOUND " << count << endl;
        }
    } while (count != 100 && Cexact != N && digits == N);
}



int main(int argc, char* argv[]) {
    srand(time(0));
    if (argc < 2) {// If there are at least 2 arguments, give an error and terminate the program.
        cout<<"EO";
        exit;
    }
    if (string(argv[1]) == "-r") {
        if (argc != 3) {
            cout << "E0"; // the -r command cannot be used alone, 3. it expects the number of digits of a random number as an argument.
            return 0;
        }
        int  N = atoi(argv[2]); // Convert the second argument to an integer
        if (N <= 0 || N >= 10) {//// sayı 0'dan küçük veya 10'dan büyük olamaz
           cout <<"E0"; 
           return 0;
        }
       
       //generating random numbers
        char num[N];
        num[0] = rand() % 9 + 1+'0'; //the first number is chosen randomly so that it is not zero
        for (int i = 1; i < N; i++) {
        num[i] = rand() % 10 + '0'; //other numbers are randomly selected
        for (int j = 0; j < i; j++) {
            if (num[i] == num[j]) {
                i--; // i is reduced to one to prevent the same number being selected twice
                break;
            }
        }
    }
        Game(num, N);
    }
    else if (string(argv[1]) == "-u") {
        if (argc != 3) {
            exit;//the -u command cannot be used alone, 3. it expects the number of digits of a random number as an argument.
        }
        int length = strlen(argv[2]);//determine the size of the number
        char secretNumber[length];
        strcpy(secretNumber, argv[2]);
        
        if (isValidNumber(secretNumber, length) == 0) {
            return 0;
        }

        Game(secretNumber, length);
    }
    else {
        cout<<"EO";
        return 0;
    }

    return 0;
}



