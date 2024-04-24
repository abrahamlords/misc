//
// Created by Abraham Lords on 9/12/20.
//

#ifndef CSE310PROJ1_LINKEDLIST_H
#define CSE310PROJ1_LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

///
//////////////// don't trust remove any remove or delete methods
///

class Node {
private:
    string* data;    // pointer to generic item
    Node* next;  // pointer to next node
public:
    Node(); // constructor
    Node(string* item);  // paramaterized constructor
    ~Node();    // destructor
    void setData(string* item);  // setter
    string* getData();   // getter
    void setNext(Node* node); // setter
    Node* getNext(); // getter
};


Node::Node() {
    data = NULL;
    next = NULL;
}


Node::Node(string* item) {
    data = item;
    next = NULL;
}


Node::~Node() {
    delete data;
}


void Node::setData(string* item) {
    data = item;
}


string* Node::getData() {
    return (data);
}


void Node::setNext(Node* node) {
    next = node;
}


Node* Node::getNext() {
    return next;
}




class LinkedList {
protected:
    Node* head;  // first node in list
    Node* current;   // used as temp node in methods instead of creating a new node every time
    Node* tail;  // last node in list
    int size;   // keeps track of size of list
public:
///
//////////////// don't trust remove any remove or delete methods
///
    LinkedList();   // constructor
    ///~LinkedList();  // destructor
    void addToFront(string* data);   // create a node containing T data and add it to the front of the
    void addToEnd(string* data);     // create a node containing T data and add it to the end of the
    int addAtIndex(string* data, int index);  // create a node containing T data and add it to the
    ///string* removeFromFront();   // Delete first item and return its contents
    ///string* removeFromEnd(); // Delete last item and return its contents
    void removeTheFirst(string* data);   // find first instance of T data and remove it
    void removeAllOf(string* data);  // find each instance of T data and remove it
    ///void deleteAtIndex(int index);  // deletes node on specified index
    char elementExists(string* data);    //Returns a T/F if element exists in list
    Node* find(string* data); //Look for data in the list, return a pointer to its node
    int indexOf(string* data);   //returns an index of the item in the list (zero-based)
    string* retrieveFront(); //returns the data contained in the first node, does not delete it
    string* retrieveEnd();   //returns the data contained in the last node, does not elete it
    string* retrieve(int index); //returns the data contained in node # index, does ot delete it, returns null if index is out of bounds or data does not exist
    void printList();   //Loop through each node and print the contents of the Node
    ///void empty();   //Empty out the list, delete everything
    int length();   //How many elements are in the list
    Node* nodeAtIndex(int index);    // returns the node at an index
    bool isEmpty(); // reports if the list is empty
};



LinkedList::LinkedList(){ // constrcutor
    head = NULL;
    current = NULL;
    tail = NULL;
    size = 0;
}


//LinkedList::~LinkedList(){ // destructor
//    empty();
//}


void LinkedList::addToFront(string* data){
    Node* newNode = new Node(data);
    if(isEmpty()) {             // if empty list --> set first node
        head = newNode;
        tail = head;
    } else {                    // else add to front
        newNode->setNext(head);
        head = newNode;
    }
    size++;
}


void LinkedList::addToEnd(string* data){  // edits size
    Node* newNode = new Node(data);
    if(isEmpty()) {                  // if empty list --> set first node
        head = newNode;
        tail = head;
        string* strang = head -> getData();
        cout << "addToEnd... Your head is now " << head << " " << head ->getData() << " \"" << *(strang) << endl;
    } else {
        newNode->setNext(NULL);   // else add to end
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;                         // edits size here
}


int LinkedList::addAtIndex(string* data, int index){
    if (index < 0 || index > (size + 1)) {          // if requested placement is out of range
        cout << "ERROR: addAtIndex(): index out of range" << endl;
        return -1;
    }
    if (index == 0) {                               // if requested placement is at head
        addToFront(data);
    }
    if (index == (size - 1)) {                      // if requested placement is immiediately after tail
        addToEnd(data);
    }
    if (index > 0 && index < size - 1) {                // if requested placement is between head and tail
        Node* newNode = new Node(data);;
        current = nodeAtIndex(index-1);               // current = node before request placement
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        size++;                                     // edits size here
    }
    // size incrementation is included in each case
    return 1;
}

///
//////////////// don't trust remove any remove or delete methods
///
//string* LinkedList::removeFromFront() { // Warning .. Cannot print NULL
//    if (isEmpty()) {                 // returns NULL if empty
//        cout << "<EMPTY LIST>";
//        return NULL;
//    }
//    string* item = head->getData();   // gets head data
//    current = head;
//    head = head->getNext();      // replaces head and head.next
//    delete current;                 // deletes old head
//    size--;
//    if (size == 0) {                // if it just removed the last item --> clear out pointers to NULL
//        empty();
//    }
//    return (item);
//}
//
//
//string* LinkedList::removeFromEnd(){   // Warning .. Cannot print NULL
//    if (isEmpty()) {                 // returns NULL if empty
//        cout << "<EMPTY LIST>";
//        return NULL;
//    }
//
//    string* item = tail->getData();    // gets tail data
//    delete tail;                     // deletes tail
//    size--;
//
//    if (size == 0) {                 // if it just removed the last item --> clear out pointers to NULL
//        empty();
//    } else {                         // else, proceed as normal
//        tail = nodeAtIndex(size-1);      // reset tail to Node right before it
//        tail->setNext(NULL);      // set tail.nex to NULL
//    }
//    return (item);
//}


//void LinkedList::removeTheFirst(string* data){ //edits size  // This method uses indexOf() instead of find() because, since there is no Node.previous, the index must be known for deletion anyway.
//    int index = indexOf(data);
//    if (index < 0) {
//        return;
//    }
//    deleteAtIndex(index);           // edits size in here
//}


//void LinkedList::removeAllOf(string* data){ // edits size  // This method uses indexOf() instead of find() because, since there is no Node.previous, the index must be known for deletion anyway.
//    int index = indexOf(data);
//    while (index > -1) {
//        deleteAtIndex(index);           // edits size in here
//        index = indexOf(data);
//    }
//}


//void LinkedList::deleteAtIndex(int index) {
//    if (index < 0 || index > (size)) {              // if requested index is out of range
//        cout << "ERROR: deleteAtIndex(): index out of range" << endl;
//    }
//    if (index == 0) {                               // if deletion index is at head
//        removeFromFront();                          // no need for output; // edits size in here
//    }
//    if (index == (size)) {                          // if deletion index is immiediately is at tail
//        removeFromEnd();                            // no need for output; // edits size in here
//    }
//    if (index > 0 && index < size) {                // if deletion index is between head and tail
//        current = nodeAtIndex(index-1);             // current = Node before deletion index
//        Node* temp = current->getNext();      // temp = deletion index
//        current->setNext((current->getNext())->getNext());
//        delete temp;                                // delete (temp = deletion index)
//        size--;
//    }
//    // size incrementation is included in each case
//}


char LinkedList::elementExists(string* data){ // I recommend using indexOf() directly
    if (indexOf(data) < 0) {
        return 'F';
    }
    return 'T';
}


Node* LinkedList::find(string* data){
    current = head;
    while (current != NULL) {                       // cycle through whole list from start
        if (*(current->getData()) == *data) {    // if data matches then return matching Node
            return current;
        }
        current = current->getNext();            // if not then continue to compare next node
    }
    cout << "Element not found" << endl;            // will return NULL if not found
    return NULL;
}


int LinkedList::indexOf(string* data){
    current = head;
    int i = 0;
    while (current != NULL) {                       // cycle through whole list from start
        if (*(current->getData()) == *data) {
//            cout << "indexOf() ... current.getData() = " << *(current->getData()) << " at index  " << i <<  endl;
            return i;                               // if data matches then return index
        }
        current = current->getNext();            // if not then continue to compare next node
        i++;
    }
    return -1;                                      // will return -1 if not found
}


string* LinkedList::retrieveFront(){
    return head->getData();
}


string* LinkedList::retrieveEnd(){
    return tail->getData();
}


string* LinkedList::retrieve(int index){
    return nodeAtIndex(index)->getData(); // nodeAtIndex() is a better name because the call name tells you what it returns
}


void LinkedList::printList(){
    current = head;              // starts at head
    while (current != NULL) {    // while node exists
        cout << "heckin " << (current->getData()) << ": -" << *(current->getData()) << endl;   // print node data
        current = current->getNext();    // move to next node
    }
    cout << endl;                // new line
}


//void LinkedList::empty(){
//    if (size == 0) {        // This first case is necessary for when no Nodes are in the list, but the Node pointers remain. (pointers to NULL)
//        head = NULL;
//        current = NULL;
//        tail = NULL;
//    } else {                // When list is full
//        current = head;     // start at beginning temp = head
//        while (current != NULL) {
//            delete head;    // delete formal head
//            current = current->getNext();    // advance temp
//            head = current; // new head = advanced temp
//        }
//    }
//}


int LinkedList::length() { // if size is off, then the whole code breaks and there is no need to count nodes
    return size;
}


Node* LinkedList::nodeAtIndex(int index) {
    current = head;
//    cout << "nodeAtIndex() ... requested index = " << index << endl;
    if (index < 0 || index > size) {          // if requested placement is out of range
        cout << "ERROR: addAtIndex(): index out of range" << endl;
        return NULL;
    }
    for (int i = 0; i < index; i++) {       // cycle through list
        current = current->getNext();
    }
//    cout << "nodeAtIndex() ... current.getData() = " << *(current->getData()) << endl;
    return current;
}


bool LinkedList::isEmpty() {
    if (head == NULL) {
        return true;
    }
    return false;
}



#endif //CSE310PROJ1_LINKEDLIST_H

