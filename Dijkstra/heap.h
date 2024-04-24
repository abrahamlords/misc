//
// Created by Abraham Lords on 11/17/20.
//

#ifndef CSE310PROJECC3_HEAP_H
#define CSE310PROJECC3_HEAP_H
#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::numeric_limits;

#define INF std::numeric_limits<int>::max();


class HeapElement {
public:
    int name;
    int predecessor;
    int distance;

    HeapElement(int name);
    //HeapElement(Vertex* vertex);
};

HeapElement::HeapElement(int name) {
    //this->vertex = vertex;
    this->name = name;
    predecessor = -1;
    distance = INF;
}




class MinHeap {
private:
    HeapElement** heap; // int array // first element at index 0
    int arraySize;
    int size;
public:
    MinHeap();
    MinHeap(int arraySize);
    MinHeap(int* set, int setSize);
    int getSize();
    HeapElement* atIndex(int i);

    int parentIndex(int i);
    int leftIndex(int i);
    int rightIndex(int i);

    void minHeapify(int i);
    void buildHeap();
    void heapsort();

    void insert(HeapElement* heapElementPtr);
    HeapElement* getMin();
    HeapElement* extractMin();
    void decreaseKey(int elementIndex, int newVal);

    void expandArray();
    void indexedPrint();

};

HeapElement* MinHeap::atIndex(int i){
    return heap[i];
};

#endif //CSE310PROJECC3_HEAP_H
