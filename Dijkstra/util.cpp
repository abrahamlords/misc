//
// Created by Abraham Lords on 11/17/20.
//

#include "util.h"
#include "heap.h"


MinHeap* initializeSingleSource(adjacencyListEntry** adjacencyListPtr, int sourceKey, int vertexTotal) { // for dijkstras
    MinHeap* priorityQ = new MinHeap(vertexTotal); // first makes priority Q which will eventually be returned

    // for all vertexes that arent source
    for (int i = 1; i < sourceKey; i++) {
        // v.distance = infinity
        // v.predecessor = -1;
        adjacencyListEntry* atIndex = adjacencyListPtr[i]; //gets entry at new index
        HeapElement* element = new HeapElement(i);
        priorityQ->insert(element); // insert
    }
    for (int i = sourceKey; i <= vertexTotal; i++) {
        adjacencyListEntry* atIndex = adjacencyListPtr[i]; //gets entry at new index
        HeapElement* element = new HeapElement(i);
        priorityQ->insert(element);// insert
    }

    HeapElement* sourceElement = new HeapElement(sourceKey); // addes source after add all but source
    sourceElement->distance = 0; // distance from itself is 0

    priorityQ->buildHeap(); // order it / build it
    return priorityQ;
}



void relax(HeapElement* u, HeapElement* v, int w) {// this was much easier set inline
    if (v->distance > u->distance + w) {
        v->distance = u->distance + w;
    // needs to update distances to v
    // aka decrease key
    }
}
int findHeapIndex(MinHeap* priorityQ, int name) { // in order array scan to retrieve element index in minHeap
    for ( int i = 1; i < priorityQ->getSize(); i++) {
        if (priorityQ->atIndex(i)->name == name) {
            return i;
        }
    }
    return -1; // if not found
}

//void updateDistance()

void dijkstra(adjacencyListEntry** adjacencyListPtr, int sourceKey, int targetKey, int vertexTotal) {
    //initialize single source
    MinHeap* priorityQ = initializeSingleSource(adjacencyListPtr, sourceKey, vertexTotal);
                            // update Q elements' distances based off adjacency List
                            // minHeapify
                            // extract min
    // make empty set S for vertices for path
    HeapElement** minPathSet = new HeapElement*[vertexTotal]; /// heapEl or vertex
    // insert all veritices into the min priority que // will have name of vertex and distance to
        //key val is distance here^
        //
    int i = 0;
    // while priority que is not empty
    while (priorityQ->getSize() > 0) {
        HeapElement* u = priorityQ->extractMin();
        int uName = u->name;


        // put in S
        minPathSet[i++] = u;

        // for each vertex V adjacent to u {

        adjacencyListEntry* succ = adjacencyListPtr[uName];
        while (succ != NULL) {
            int heapIndex = findHeapIndex(priorityQ, succ->successor);  // update distances
            if (heapIndex > 0 && heapIndex <= vertexTotal ) { // if in range
                HeapElement* v = priorityQ->atIndex(heapIndex);
                int w = succ->weight; // successor weight
                //relax(u, v, w);  // v is neighbor to u
                if (v->distance > u->distance + w) { // inline relax
                    priorityQ->decreaseKey(heapIndex, u->distance + w);
                    v->predecessor = uName;
                }
            }
            succ = succ->next; // get next neighbor
        }
    }
}
