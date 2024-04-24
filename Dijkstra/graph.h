//
// Created by Abraham Lords on 11/17/20.
//

#ifndef CSE310PROJECC3_GRAPH_H
#define CSE310PROJECC3_GRAPH_H

class adjacencyListEntry {
public:
    int successor; // successor ... key is index of adjListEntry
    //Vertex* vertex;
    adjacencyListEntry* next; //next in adjacency list
    int weight; // weight from successor to next


    //adjacencyListEntry();
    adjacencyListEntry(int successor, int weight);
    void setKey(int key);
    void setNext(adjacencyListEntry* next);
    void setWeight(int weight);
    //Vertex* getVertex();
    int getKey();
    adjacencyListEntry* getNext();
    int getWeight();
};

//class Vertex {
//private:
//    int key;
//    Vertex* predecessor;
//    int distance;
//public:
//    Vertex();
//    Vertex(int key, int distance);
//    void setKey(int key);
//    void setPredecessor(Vertex* predecessor);
//    void setDistance(int distance);
//    int getKey();
//    Vertex* getPredecessor();
//    int getDistance();
//
//    void dijkstra(Vertex* startNode);
//    void relax();
//};


#endif //CSE310PROJECC3_GRAPH_H
