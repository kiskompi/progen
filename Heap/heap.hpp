#ifndef HEAP 
#define HEAP

#include <iostream>
#include <vector>
#include <iterator>

class Heap {
public:
    Heap();
    ~Heap();
    void insert(int element);
    int deletemin();
    void print();
    int size() { return heap.size(); }
private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
private:
    std::vector<int> heap;
};

#endif