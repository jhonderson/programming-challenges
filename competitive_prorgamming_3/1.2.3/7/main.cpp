
#include <iostream>

using namespace std;

void printPermutations(char* characters, unsigned int size)
{
    do {
        for (int i = 0; i < size; i++)
            cout << ' ' << characters[i];
        cout << endl;
    } while ( next_permutation(characters, characters + size) );   
}

int main()
{
    unsigned int size = 10;
    char characters[size];
    characters[0] = 'A';
    for (int i = 1; i < size; i++)
        characters[i] = characters[i - 1] + 1;

    printPermutations(characters, size);

    return 0;
}
