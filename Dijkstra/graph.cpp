//
// Created by Abraham Lords on 11/17/20.
//

#include "graph.h"
#include <limits>
using std::numeric_limits;


//adjacencyListEntry::adjacencyListEntry() {
//    successor = -1;
//    next = NULL;
//    weight = INF;
//}

adjacencyListEntry::adjacencyListEntry(int successor, int weight) {
    this->successor = successor;
    next = NULL;
    this->weight = weight;
}

void adjacencyListEntry::setKey(int key) {
    this->successor = key;
}

void adjacencyListEntry::setNext(adjacencyListEntry* next) {
    this->next = next;
}

void adjacencyListEntry::setWeight(int weight) {
    this->weight = weight;
}


int adjacencyListEntry::getKey() {
    return successor;
}

adjacencyListEntry* adjacencyListEntry::getNext() {
    return next;
}

int adjacencyListEntry::getWeight() {
    return weight;
}

//
//Vertex::Vertex() {
//    key = numeric_limits<int>::min();
//    predecessor = NULL;
//    distance = numeric_limits<int>::min();
//}
//
//Vertex::Vertex(int key, int distance) {
//    this->key = key;
//    predecessor = NULL;
//    this->distance = distance;
//}
//
//void Vertex::setKey(int key) {
//    this->key = key;
//}
//
//void Vertex::setPredecessor(Vertex* predecessor) {
//    this->predecessor = predecessor;
//}
//
//void Vertex::setDistance(int distance) {
//    this->distance = distance;
//}
//
//int Vertex::getKey() {
//    return key;
//}
//
//Vertex* Vertex::getPredecessor() {
//    return predecessor;
//}
//
//int Vertex::getDistance() {
//    return distance;
//}


//void Vertex::initializeSingleSource(Vertex* sourceVertex) {
// for all vertexes that arent source {
// v.distance = infinity
// v.predecessor = -1;
// }
// sourceVertex.distance = 0;
//}


