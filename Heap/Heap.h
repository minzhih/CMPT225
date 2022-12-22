//#pragma once
#include<stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<class T>
class Heap{
public:
    //constructor(int) – a Heap with an underlying array size equal to the integer parameter
    Heap(int cap);
    //destructor – deallocates dynamic memory allocated by the Heap
    ~Heap();
    //copy constructor – a constructor that creates a deep copy of its constant Heap reference parameter
    Heap(const Heap& mh);
    /*overloads the assignment operator for Heap– (deep) copies its  constant Heap reference parameter into the calling object and returns a reference to the calling object; deallocates dynamic memory as necessary and behaves appropriately under self-assignment*/
    Heap<T> & operator=(const Heap & mh);
    /*insert function – inserts its template parameter in the heap, while maintaining the heap properties; if the Heap is full throws a runtime_error*/
    void insert (T x);
    /*removes and returns the root, while maintaining the heap properties; if the Heap is empty throws a runtime_error*/
    T remove();
    /*return the root*/
    T peek();
    /*returns a Heap object that contains the values in the calling object and its constant reference Heap parameter, the size of the returned heap should be equal to the sum of the current (not max) sizes of the calling object and the parameter; must run in O(n) time - not O(n log n) (or worse) - where n is the combined size of the two heaps.*/
    Heap<T> merge(const Heap<T> & mh);
    /*size – returns the number of items stored in the Heap, as an int*/
    int size() const;
    
    
private:
    T* arr;
    int hsize;
    int cap;
    //helper function
    void bubbleUP(int i);
    void bubbleDown(int i);
};

template <class T>
Heap<T>::Heap(int cap)
{
    hsize = 0;
    cap = cap;
    arr = new T[cap];
}

template <class T>
Heap<T>::~Heap()
{
    if (arr != nullptr)
            {
                delete[]arr;
                arr = nullptr;
                cap = 0;
                hsize = 0;
            }
}

template <class T>
Heap<T>::Heap(const Heap<T>& mh)
{
    hsize = mh.hsize;
    cap = mh.cap;
    //if the arr itself is not null delete array
    arr=new T [cap];
    for(int i= 1; i<=hsize; i++){
        arr[i]= mh.arr[i];
    }
}

template <class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& mh)
{
    if (this!= &mh)
            {
                this->cap =mh.cap;
                this->hsize = mh.hsize;
                this->arr=new T [cap];
                for(int i= 1; i<=hsize; i++){
                    arr[i]= mh.arr[i];
                }
    }
    return *this;
}

template <class T>
void Heap<T>::insert (T x)
{
    //if the Heap is full throws a runtime_error
    /*error有问题
    if(hsize>cap)
    {
        throw std::range_error("arr is full, could not insert");
    }*/
    arr[hsize]=x;
    bubbleUP(hsize);
    hsize++;
}

template <class T>
T Heap<T>::remove()
{
    /* error有问题
    if(arr==nullptr)
    {
        throw std::range_error("arr is empty, could not remove");
    }
    */
    T val=arr[0];
    arr[0]= arr[--hsize];
    bubbleDown(0);
    return val;
    
}

template <class T>
T Heap<T>::peek()
{
    T val=arr[0];
    return val;
}

template <class T>
Heap<T> Heap<T>::merge(const Heap<T> & mh)
{
    Heap<T> res(hsize+mh.hsize);
    for(int i=0;i<hsize;i++)
    {
        res.arr[res.hsize++]=arr[i];
    }
    for(int i=0;i<mh.hsize;i++)
    {
        res.arr[res.hsize++]=mh.arr[i];
    }
    for(int i=res.hsize-1;i>=0;i--)
    {
        res.bubbleDown(i);
    }
    return res;
}

template <class T>
int Heap<T>::size() const
{
    return hsize;
}

/*smallestm that has two parameters: the first is a vector containing elements of the template type, the second is an integer referred to as m.

The function should return a vector that contains the m smallest values in the function's vector parameter, in ascending order.*/
template <class T>
vector<T> smallestm(vector<T> a,int m)
{
    Heap<int> pq(m);
    vector<T> b(m);
    for(int i = 0; i < a.size(); i++)
    {
        if(i<m)
        {
            pq.insert(a[i]);
        }
        if(i>=m)
        {
            if(a[i]<pq.peek())
            {
                pq.remove();
                pq.insert(a[i]);
            }
        }
    }
    
    for(int j = 0; j < m; j++)
    {
        b[j]=pq.remove();
    }
    return b;
}


// Helper method for functions
template <class T>
void Heap<T>::bubbleUP(int i)
{
    int parent =(i-1)/2;
    if (i>0 &&arr[i]>arr[parent])
    {
        T temp =arr[i];
        arr[i]=arr[parent];
        arr[parent]=temp;
        bubbleUP(parent);
    }
}

template <class T>
void Heap<T>::bubbleDown(int i)
{
    int left=(2*i+1);
    int right=(2*i+2);
    int largest=i;
    if(left<hsize&& arr[left]>arr[i])
    {
        largest=left;
    }
    if(right<hsize && arr[right]>arr[largest])
    {
        largest=right;
    }
    if (largest != i)
    {
        int temp =arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        bubbleDown(largest);
    }
}

template <class T>
void showVec(vector<T> vec){
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}


