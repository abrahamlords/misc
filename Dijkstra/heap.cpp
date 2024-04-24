//
// Created by Abraham Lords on 11/17/20.
//

#include "heap.h"

MinHeap::MinHeap() {
    arraySize = 25;
    heap = new HeapElement*[arraySize];
    size = 0;
}

MinHeap::MinHeap(int arraySize) {
    this->arraySize = arraySize;
    heap = new HeapElement*[arraySize];
    size = 0;
}

int MinHeap::getSize() {
    return size;
}

//MinHeap::MinHeap(int* set, int setSize) {
//    arraySize = setSize + 1;
//    heap = set;
//    size = setSize;
//    buildHeap();
//}

void MinHeap::minHeapify(int i) {
    if (i < 1 || i > size) {
        //cout << "\n\n minHeapify index out of range \n";
        return;
    }

    int leftI = leftIndex(i);
    int rightI = rightIndex(i);
    int smallest;

    if ( leftI <= size && heap[leftI] < heap[i] ) { // if in range and left is smaller than this
        smallest = leftI;   // left is smallest
    } else {
        smallest = i;       // smallest is this
    }
    if ( rightI <= size && heap[rightI] < heap[smallest] ) { // compares current smallest with right side
        smallest = rightI;
    }
    if (smallest != i) { // if smallest is not parent the swap
        //exchange heap i with heap smallest
        HeapElement* elementPtrAtI = heap[i]; // temp placeholder
        heap[i] = heap[smallest];
        heap[smallest] = elementPtrAtI;

        minHeapify(smallest); // recursively work through tree (array)
    }
}

int MinHeap::parentIndex(int i) {
    return i/2; // <-- equal to floor(i/2)
}

int MinHeap::leftIndex(int i) {
    return 2*i;
}

int MinHeap::rightIndex(int i) {
    return 2*i + 1;
}


void MinHeap::insert(HeapElement* heapElementPtr) {
    size++;
    heap[size] = heapElementPtr;
    heap[size]->distance = INF;
    decreaseKey(size, heapElementPtr->distance);
}

HeapElement* MinHeap::getMin() {
    return heap[1];
}

HeapElement* MinHeap::extractMin() { // returns heap[1] and decreases size variable
    if (size < 1) {
        cout << "congratulations. you played yourself" << endl;
    }
    HeapElement* min = heap[1];
    heap[1] = heap[size];
    size--;
    minHeapify(1);
    return min;
}

void MinHeap::decreaseKey(int elementIndex, int newVal) { // changes key val at index
    if (newVal > heap[elementIndex]->distance) {
        cout << "new key bigger than current" << endl;
    }
    heap[elementIndex]->distance = newVal;
    while ( elementIndex > 1 && heap[parentIndex(elementIndex)]->distance > heap[elementIndex]->distance) {
        // exchange heap[elementIndex] with heap[parentIndex]
        HeapElement* elementPtrAtI = heap[elementIndex];
        heap[elementIndex] = heap[parentIndex(elementIndex)];
        heap[parentIndex(elementIndex)] = elementPtrAtI;

        elementIndex = parentIndex(elementIndex);
    }
}

void MinHeap::buildHeap() { // strategically calls minHeapify
    for ( int i = size/2; i > 0; i-- ) {
        minHeapify(i);
    }
}

void MinHeap::heapsort() { //  not needed
    buildHeap();
    for ( int i = size; i > 1; i-- ) {
        HeapElement* elementPtrAtI = heap[i];
        heap[i] = heap[1];
        heap[1] = elementPtrAtI;
        size--;

        minHeapify(i);
    }
}
void MinHeap::expandArray() { // in case adding vertex .. implements dynamic array
    int oldArraySize = arraySize;
    arraySize *= 2;
    HeapElement** newArray = new HeapElement*[arraySize];
    for ( int i = 1; i <= oldArraySize; i++ ) {
        *newArray[i] = *heap[i];
    }
    delete[] heap;
    heap = newArray;
}

void MinHeap::indexedPrint() { // for testing purposes
    for ( int i = 1; i <= size; i++ ) {
        //cout << "i: " << i << " - " << heap[i] << "    ";
        cout << i << "-" << heap[i] << "  ";
    }
    cout << endl;
}