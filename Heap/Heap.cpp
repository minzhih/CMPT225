//#pragma once
#include<stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include "Heap.h"
using namespace std;

int main(int argc, const char * argv[]) {

        Heap<int> pq1(3);
        pq1.insert(3);
        pq1.insert(1);
        pq1.insert(42);
     
        cout << "pq1 root = " << pq1.peek() << endl; //42
        int urgent = pq1.remove();
        cout << "pq1 root = " << pq1.peek() << endl; //3
        cout << "pq1 size = " << pq1.size() << endl; //2
        
        Heap<int> pq2(pq1);
        pq2.insert(13);
        Heap<int> pq3 = pq1.merge(pq2); // should contain duplicates
        cout << "pq3 size = " << pq3.size() << endl; //5
        cout << "pq2 root = " << pq2.peek() << endl; //13
    
        vector<int> vect;
        vect.push_back(10);
        vect.push_back(5);
        vect.push_back(2);
        vect.push_back(8);
        vect.push_back(6);
        vect.push_back(4);
        vect.push_back(3);
        vect.push_back(9);
        vect.push_back(1);
        cout << "getsmall = "  << endl;
    showVec(smallestm(vect,4));
}
