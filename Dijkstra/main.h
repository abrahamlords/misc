//
// Created by Abraham Lords on 11/17/20.
//

#ifndef CSE310PROJECC3_MAIN_H
#define CSE310PROJECC3_MAIN_H

#include "graph.cpp"
#include "util.cpp"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;

int getCommand(string& findParams) { // receives command line and translates it into a code number
    string queryLine = "";
    getline(cin, queryLine);

    if ( queryLine.substr(0, 5) == "write" ) {
        return 1;
    }
    if (queryLine.substr(0, 4) == "find") { // if first word is find
        findParams = queryLine.substr(5, queryLine.size() - 4); // params passed by reference
        return 2;
    }

    if ( queryLine.substr(0, 4) == "stop" ) {
        return 3;
    }
    return -1; // invalid command
}

int* getVertEdgeQuants() { // gets edge and vertex totals
    string line = "";
    getline(cin, line);
    // receives chars from line for stoi conversion
    string vertexQuantString = "";
    string edgeQuantString = "";

    int substringSize = 0; // starts at beginning
    char c = line.at(substringSize++);

    while (c != ' ' && substringSize < line.size()) { // builds until space
        vertexQuantString += c;
        c = line.at(substringSize++);
    }

    c = line.at(substringSize++);
    while (c != ' ' && substringSize < line.size()) { // builds until end
        edgeQuantString += c;
        if ( substringSize <= line.size()) { // if not at end
            c = line.at(substringSize++); // build
        } else {
            substringSize++;    // otherwise just advance to exit
        }
    }
    edgeQuantString += c;   // captures last char since loop ends before

    int* araya = new int[2];  // stores in array for easy returning
    araya[0] = stoi(vertexQuantString);
    araya[1] = stoi(edgeQuantString);
    return araya; // returns both vals in array
}


void putInAdjacencyList(adjacencyListEntry** adjacencyListPtr, adjacencyListEntry* entryPtr, int arrayIndex) {
    adjacencyListEntry* atPlacementIndex = adjacencyListPtr[arrayIndex]; //gets entry in case it's already occupied
    if (atPlacementIndex != NULL) { // if occupied implement separate chaining
        entryPtr->setNext(atPlacementIndex); // place at head
        adjacencyListPtr[arrayIndex] = entryPtr; // put head in table
    } else {    // if not not occupied
        adjacencyListPtr[arrayIndex] = entryPtr; // put in table
    }
}

void printAdjacencyList(adjacencyListEntry** adjacencyListPtr, int vertexQuant, int edgeQuant, int arraySize) {
    cout << vertexQuant << " " << edgeQuant << endl; // first prints totals
    for (int i = 1; i <= arraySize; i++) {
        cout << i << " :";
        adjacencyListEntry* atPlacementIndex = adjacencyListPtr[i]; //gets entry in case it's already occupied
        while (atPlacementIndex != NULL) { // if occupied then print
            cout << " (" << atPlacementIndex->getKey() << "; " << atPlacementIndex->getWeight() << ")";

            atPlacementIndex = atPlacementIndex->getNext();
            if (atPlacementIndex != NULL) { // if there's a next vertex then print ;
                cout << ";";
            }
        }
        cout << endl;
    }
}

void fillAdjacencyList(adjacencyListEntry** adjacencyListPtr, int vertexQuant) { // receives lines and puts them in array of linked lists
    for (int i = 0; i < vertexQuant; i++) {
        string line;
        getline(cin, line);
        int adjListIndex = stoi(line);
        string keyString = ""; // first builds strings then uses stoi conversion
        string weightString = "";

        int charIndex = 0;
        char c = line.at(charIndex++);

        while (c != ' ') {
            c = line.at(charIndex++); // skips until it gets it gets to key
        }

        c = line.at(charIndex++);
        while (c != ' ') {
            keyString += c;
            c = line.at(charIndex++); // buils until space
        }

        c = line.at(charIndex++);
        while (c != ' ' && charIndex < line.size()) { // builds until end
            weightString += c;
            if ( charIndex < line.size()) {
                c = line.at(charIndex++);
            } else {
                charIndex++;
            }
        }
        weightString += c;

        // creates entry and then adds to linked list in array
        adjacencyListEntry* voretex = new adjacencyListEntry(stoi(keyString), stoi(weightString));
        putInAdjacencyList(adjacencyListPtr, voretex, adjListIndex);
    }
}

int eggZit(int exitCode, int argc, char** argv); // 0 if no args // 1 if wrong wrong arg // 2 if 2many args
int eggZit(int exitCode, int argc, char** argv) { // 0 if no args // 1 if wrong wrong arg // 2 if 2many args
    if (exitCode > 0) {
        cout << "\"";
        for ( int i = 1; i < argc; i++) {
            string c = argv[i];
            cout << c;
            if (i+1 != argc) {
                cout << " ";
            }
        }
        cout << "\" is not a suported command. ";
    }
    //cout << "Please use commands \"insertion\" or \"quick\"." << endl;
    return exitCode+1;
}

#endif //CSE310PROJECC3_MAIN_H



//if (argc != 2 ) {       // if there are too many or too few arguements
//    if (argc > 2) {
//        return eggZit(2, argc, argv);   // print instructions and return error code for too many
//    } else {
//        return eggZit(0, argc, argv);   // print instructions and return error code for too few
//    }
//} else {
//    string c = argv[1];
//    if (c != "insertion" && c != "quick") {     // if correct number of args, but not correct args
//        return eggZit(1, argc, argv);  // then print instructions and return error code for wrong args
//    }
//}
/// if correct args ///
//string c = argv[1]; // stores sorting method
//