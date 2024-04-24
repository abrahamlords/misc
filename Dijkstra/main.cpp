#include <iostream>
#include <string>
#include <math.h>
#include "main.h"
#include "heap.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stof;


int main(int argc, char** argv) {

/// RECEIVE GRAPH ///
//get vertex and edge quantities
    int* quants = getVertEdgeQuants();
    int vertexQuant = quants[0];
    int edgeQuant = quants[1];
    delete[] quants;

// make array
    adjacencyListEntry **adjacencyListPtr = new adjacencyListEntry *[vertexQuant];

    // I had to explicitly initialize each line to NULL, otherwise I would get weird errors
    for ( int i = 0; i <= vertexQuant; i++ ) {
        adjacencyListPtr[i] = NULL;
    }
// fill array
    fillAdjacencyList(adjacencyListPtr, edgeQuant);
//process queries
    int command = 0;
    // loops until it recieves a stop command (3)
    while ( command != 3 ) {
        string findParams = ""; // initialize find paramaters in case there is a find command
        command = getCommand(findParams); // returns command code

        if (command == 1) { // if command == write
            cout << "Command: write" << endl;
            printAdjacencyList( adjacencyListPtr, vertexQuant, edgeQuant, vertexQuant ); // prints adjacency list
        }
        if (command == 2) { // if command == find
            cout << "Command: find " << findParams << endl;

            // extract source node, target node, and flag from findParams
            // first move chars to strings then stoi()
            string sourceString = "";
            string targetString = "";
            string flagString = "";

            int charIndex = 0; // start at beginning of string
            char c = findParams.at(charIndex++); // initialize char

            while (c != ' ') { // builds source string until it reaches ' '
                sourceString += c;
                c = findParams.at(charIndex++); // stores new c and advances index
            }

            c = findParams.at(charIndex++);
            while (c != ' ') { // builds target string string until it reaches ' '
                targetString += c;
                c = findParams.at(charIndex++);
            }

            c = findParams.at(charIndex++); // builds flag string until it reaches the end
            while (c != ' ' && charIndex < findParams.size()) {
                flagString += c;
                if ( charIndex < findParams.size()) { // only gets next char if their is one
                    c = findParams.at(charIndex++);
                } else {
                    charIndex++;    // otherwise advances charIndex to exit while loop
                }
            }
            flagString += c; // captures last char in string since string builder is at start of loop

            int sourceName = stoi(sourceString);
            int targetName = stoi(targetString);
            int flag = stoi(flagString);

            ///// error catching decision logic /////

            bool run = true; // stops dijkstra from running if there is an error, or if there is nothing to actually find
            // if source and target are out of range
            if (sourceName < 1 || targetName < 1 || sourceName > vertexQuant || targetName > vertexQuant) {
                cout << "Error: one or more invalid nodes" << endl;
                run = false;
            }
            // if invalid flag val
            if (flag != 0 && flag != 1) {
                cout << "Error: invalid flag value" << endl;
                run = false;
            } else {
                // if source equals target .. no need for dijkstra algorithm
                if (sourceName == targetName) {
                    if (flag == 0) {
                        cout << "Length: 0";
                    }
                    if (flag == 1) {
                        cout << "Path: " << targetName;
                    }
                    run = false;
                }
            }

            // if no errors or simple cases -> run
            if (run) {
                // if only it worked
                //dijkstra(adjacencyListPtr, sourceName, targetName, vertexQuant);
            }
        }
        // if stop command
        if (command == 3) {
            cout << "Command: stop" << endl;
            // supposed to delete everything
            return 0;
        }
        // if any invalid command
        if (command < 1 || command > 3) {
            cout << "COMMAND ERROR";
            return 36;
        }
    }
    return 66;
}