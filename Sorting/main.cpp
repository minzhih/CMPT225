#include <iostream>
#include <stdexcept>
#include <vector>
#include "cmpt225sort.h"
using namespace std;

template <class T>
T* readFile(string infile, int & n)
{
    T* result;
    T next;
    n = 0;
 
    ifstream ist(infile.c_str()); // open file
    // Check if file opened correctly
    if (ist.fail()) {
        throw runtime_error(infile + " not found");
    }
 
    // Find file size
    while (ist >> next) {
        n++;
    }
 
    // Read file into array
    ist.close();
    ist.open(infile.c_str());
    result = new T[n];
    for (int i = 0; i < n; ++i) {
        ist >> result[i];
    }
 
    ist.close();
    return result;
}

int main()
{
    int n = 0;
        int* arr1 = readFile<int>("a3test1.txt", n);
        cout << "insertion sort comparisons = " << insertionsort<int>(arr1, n) << endl;
        float* arr2 = readFile<float>("a3test2.txt", n);
        cout << "quicksort comparisons = " << quicksort<float>(arr2, n) << endl;
        string* arr3 = readFile<string>("a3test3.txt", n);
        cout << "mergesort comparisons = " << mergesort<string>(arr3, n) << endl;
        cout << "shell sort comparisons = " << shellsort<string>(arr3, n) << endl;
    return 0;
}
