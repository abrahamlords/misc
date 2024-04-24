#include <iostream>
#include <string>
#include <math.h>
#include "defn.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stof;

#define MAX_LLL 20 // max linked list length in hash table

int getLineInt();
float getLineFloat();
void fillAppStruct(app_info* app);
void findName(string* queryLine, hash_table_entry** hashTablePtr, int tableSize);
void findCat(string* queryLine, categories* appCats, int catQuant);
void findFree(categories* appCats, int catQuant);
string* extractCat(string* queryLine, int& i) {
    string catName = "";
    char atI = queryLine->at(i);

    while( atI != ' ' ) {
        catName += atI;
        i++;
        atI = queryLine->at(i);
    }
    return &catName;
}
float extractFloat(string* queryLine, int& i) {
    string fload = "";
    char atI = queryLine->at(i);

    while( atI != ' ' ) {
        fload += atI;
        i++;
        atI = queryLine->at(i);
    }
    return stof(fload);
}
void findPriceRange(string* queryLine, categories* appCats, int catQuant);
void findAppRange(string* queryLine, categories* appCats, int catQuant);
void removeApp(string* catName, string* appName, hash_table_entry** hashTablePtr, int tableSize);
void processQueries(int queryQuant, hash_table_entry** hashTablePtr, int tableSize, categories* appCats, int catQuant);
categories* receiveCats(int catQuant);
int getHashIndex(string* appName, int tableSize);
bool TestForPrime( int val );
int firstPrimeAfter(int c);
void fillHashEntryStruct(hash_table_entry* hashTableEntry, Node<app_info>* nodePtr);
void putInHashTable(hash_table_entry** hashTablePtr, hash_table_entry* hashTableEntry, int hashIndex);
void printCatArray(categories* appCats, int catQuant);
void printHashTable(hash_table_entry** hashTablePtr, int tableSize);
Node<app_info>* placeInTree(app_info* appPtr, categories* appCats, int catQuant);
void runReport();


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


int main(  ) {

    int catQuant = getLineInt(); // receive number of categories
    categories* appCats = receiveCats(catQuant); // receive category names into structs then array

    int appQuant = getLineInt(); // receive number of apps to go into store

    ////// receive app info and place into data structures //////
    int tableSize = firstPrimeAfter(appQuant*2); // table size is determined by the first prime after double the app quantity
    hash_table_entry** hashTablePtr = new hash_table_entry*[tableSize]; // hash table implemented with separate chaining

    for (int i = 0; i < appQuant; i++) { // for all apps
        /// receive app info
        app_info* appPtr = new app_info; // new app info struct
        fillAppStruct(appPtr);  // receives app info and fills struct

        /// place app into tree
        Node<app_info>* nodePtr = placeInTree(appPtr, appCats, catQuant); // adds struct into BST based off name and then collects Node pointer used in BST

        /// place app into hash table
        hash_table_entry* hashTableEntry = new hash_table_entry; // this struct stores name, node*, and this.node->next

        fillHashEntryStruct(hashTableEntry, nodePtr); // fills entry
        string* appNameStrPtr = &(appPtr->appName); // string to determine has index
        int hashIndex = getHashIndex(appNameStrPtr, tableSize); // hash function = (sum of ascii values) mod (table size)
        putInHashTable(hashTablePtr, hashTableEntry, hashIndex); // inserts into hash table
    }

    int queryQuant = getLineInt(); // receive query count

    ////// process queries //////
    processQueries(queryQuant, hashTablePtr, tableSize, appCats, catQuant); // receives queries from cin, processes, and prints result // only find app for milestone

    //intCatArray(appCats, catQuant);
    //appTree->inOrderPrint(); // for testing porpoises
    //printHashTable(hashTablePtr, tableSize); // for testing porpoises
    ////// run report //////
    runReport();

    string reportCommand = "";
    getline(cin, reportCommand);
    if (reportCommand == "report") {
        cout << endl << endl << "-------------------- Report --------------------" << endl;
        // For BST :
        for ( int i = 0; i < catQuant; i++) {
            // print category name
            cout << "Category name : " << appCats[i].category << endl;
            // count total number of nodes
            cout << "\t Nodes :" << appCats[i].root->getSize() << endl;
            // the height of the tree
            cout << "\t Height : " << appCats[i].root->getHeightRoot() << endl;
            // the height of the left subtree
            cout << "\t Height of left subtree : " << appCats[i].root->getHeightLeft() << endl;
            // the height of the right subtree
            cout << "\t Height of right subtree : " << appCats[i].root->getHeightRight() << endl;
        }

        // For Hash Table :
        cout << "\n \nHash Table :" << endl;
        // print table that has chain lengths and qauntity per
        int entryCount = 0;
        int* entryTable = new int[MAX_LLL]; // entryTable[length] = tally of length

        for (int i = 0; i < tableSize; i++) {
            if (hashTablePtr[i] != NULL) {
                entryCount++;
                int ii = i;
                hash_table_entry* currentEntry = hashTablePtr[ii];

                int entryLinkedLength  = 0;
                while (currentEntry != NULL) {
                    entryLinkedLength++;
                    //currentEntry = currentEntry->next;
                    currentEntry = hashTablePtr[++ii];
                }
                entryTable[entryLinkedLength] = entryTable[entryLinkedLength] + 1;
            }
        }
        int i = 1;
        while (entryTable[i] > 0) {
            cout << "Length " << i << " : " << entryTable[i] << endl;
            i++;
        }
            // compute and print the load factor with n and m
        cout << "Load Factor = " << appQuant << " elements" << " / " << entryCount << " slots" << " = " << (float) appQuant / (float) entryCount << endl;
            // Implement find app with directly searching the BST instead of the hash table
        //newFindApp()
            // (easiest way : maybe ... use hash table to extract category and then search BST)
            // compare times

    }

    ////// grace //////
    for (int i = 0; i < catQuant; i++) {
        delete appCats[i].root;
    }
    delete[] hashTablePtr;
}















int getLineInt() { // reads from cin and converts to int
    string line = "";
    getline(cin, line);
    return stoi(line);
}

float getLineFloat() { // reads from cin and converts to float
    string line = "";
    getline(cin, line);
    return stof(line);
}

categories* receiveCats(int catQuant) { // recieves categories and returns array
    categories* appCats = new categories[catQuant]; // array of category structs (not struct pointers per requirement wording)
    // project requirement say to store structs, but I may need to make this into struct pointers later.
    // We don't need it for the milestone anyway
    for (int i = 0; i < catQuant; i++) { // for all categories
        categories* cat = new categories;   // make new cat struct
        BTree<app_info>* catRee = new BTree<app_info>(); // binary search tree for category
        cat->root = catRee; // fill cat struct
        getline(cin, cat->category); // fill cat struct
        appCats[i] = *cat;   // place in array
    }
    return appCats; // return array
}

void fillAppStruct(app_info* app) { // receives and fills
    getline(cin, app->category);
    getline(cin, app->appName);
    getline(cin, app->version);
    app->size = getLineFloat(); // receives and also changes string to float
    getline(cin, app->units);
    app->price = getLineFloat(); // receives and also changes string to float
}

Node<app_info>* placeInTree(app_info* appPtr, categories* appCats, int catQuant) {
    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        if (appPtr->category == appCats[i] . category) { // when there is a match
            return appCats[i] . root->add(appPtr); // add app to that category's tree ... returns nodePtr
        }
    }
    cout << "\"" << appPtr->category << "\" not found. Failed to add to Binary Search Tree.";
    return NULL; // failure
}

int getHashIndex(string* appName, int tableSize) { // returns hash function result
    long unsigned int i = 0; // long and unsigned to match name.size() int
    char letter = appName->at(i++); // gets then increments
    int asciiSum = 0;
    while (i < appName->size()) {  // for all app name letters
        asciiSum += (int)letter;  // add ascii val to total
        letter = appName->at(i++); // get next char then increment i
    }
    return asciiSum % tableSize; // return hash function result
}

bool TestForPrime( int val ) // given
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}

int firstPrimeAfter(int c) { // gets first prime after c
    c++; // note : after c
    while (!TestForPrime(c)) { // while not prime
        c++;
    }
    return c;
}

void fillHashEntryStruct(hash_table_entry* hashTableEntry, Node<app_info>* nodePtr) { // fills struct
    hashTableEntry->app_name = (nodePtr->getData())->appName; // Name of the application
    hashTableEntry->app_node = nodePtr; // Pointer to node in tree containing the application information
    hashTableEntry->next = NULL; // Next pointer for chain in separate chaining

}

void putInHashTable(hash_table_entry** hashTablePtr, hash_table_entry* hashTableEntry, int hashIndex) {
    hash_table_entry* atPlacementIndex = hashTablePtr[hashIndex]; //gets entry in case it's already occupied
    if (atPlacementIndex != NULL) { // if occupied implement separate chaining
        hashTableEntry->next = atPlacementIndex; // place at head
        hashTablePtr[hashIndex] = hashTableEntry; // put head in table
    } else {    // if not not occupied
        hashTablePtr[hashIndex] = hashTableEntry; // put in table
    }
}

void processQueries(int queryQuant, hash_table_entry** hashTablePtr, int tableSize, categories* appCats, int catQuant) {
    for (int i = 0; i < queryQuant; i++) { //for all queries
        string queryLine;
        getline(cin, queryLine); // get full query line

        if (queryLine.substr(0, 4) == "find") { // if first word is find
            if (queryLine.substr(5, 3) == "app") { // find by category
                findName(&queryLine, hashTablePtr, tableSize); // process find query
            }
            if (queryLine.substr(5, 8) == "category") { // find by category
                findCat(&queryLine, appCats, catQuant); // process find query
            }
            if (queryLine.substr(5, 5) == "price") { // find by category
                findFree( appCats, catQuant); // process find query
            }
        }

        if (queryLine.substr(0, 5) == "range") { // if first word is range
            int ii = 6;
            string catName = "";
            char atI = queryLine.at(ii);

            while (atI != ' ') {
                catName += atI;
                ii++;
                atI = queryLine.at(ii);
            }
            ii++;

            if (queryLine.substr(ii, 5) == "price") { // if second word is price
                findPriceRange(&queryLine, appCats, catQuant);
            }
            if (queryLine.substr(ii, 3) == "app") { // if second word is app
                findAppRange(&queryLine, appCats, catQuant);
            }
        }

        if (queryLine.substr(0, 6) == "delete") { // if first word is delete

            /////////////////////////////////////////////////////////////////////////
            cout << "--------- Delete function not yet implemented ---------" << endl;
            /////////////////////////////////////////////////////////////////////////

            int ii = 7;
            string* catName = new string;
            string* appName = new string;
            *catName = "";
            *appName = "";
            char atI = queryLine.at(ii);

            while (atI != ' ') {
                *catName += atI;
                ii++;
                atI = queryLine.at(ii);
            }
            ii++;
            atI = queryLine.at(ii);

            while (ii < queryLine.length()) {
                *appName += atI;
                ii++;
                //atI = queryLine->at(ii);
                if (ii < queryLine.length()) {
                    atI = queryLine.at(ii);
                }
            }

            //removeApp(catName, appName, hashTablePtr, tableSize);
            delete catName;
            delete appName;
        }
    }
}

void removeApp(string* catName, string* appNameStrPtr, hash_table_entry** hashTablePtr, int tableSize) {
    //find app in hash table
    int hashIndex = getHashIndex(appNameStrPtr, tableSize); // hash function = (sum of ascii values) mod (table size)
    hash_table_entry* atPlacementIndex = hashTablePtr[hashIndex]; //gets entry in case it's already occupied
    hash_table_entry* next = NULL;

    if (atPlacementIndex != NULL) { // if occupied
        bool found = false;
        while ( atPlacementIndex != NULL && found == false) {
            if (atPlacementIndex->app_name == *appNameStrPtr) {
                // we got em bois
                found = true;
                atPlacementIndex->app_node->removeNode();
            } else {
                atPlacementIndex = atPlacementIndex->next;
                //if (atPlacementIndex != NULL) {
                //    cout << "Application " << *appNameStrPtr << " not found in category " << *catName << "; unable to delete." << endl;
                //    return;
                //}
            }
        }

    } else {    // if not not occupied
        cout << "Application " << *appNameStrPtr << " not found in category " << *catName << "; unable to delete." << endl;
        return;
    }
    cout << "Application " << *appNameStrPtr << " from Category " << *catName << " successfully deleted." << endl;
}

void findName(string* queryLine, hash_table_entry** hashTablePtr, int tableSize) { // for all find queries

    string* appNamePtr = new string; //needs to by dynamically allocated because getHashIndex() takes a string*
    *appNamePtr = queryLine->substr(9, queryLine->size() - 9); // receives app name
    int hashIndex = getHashIndex(appNamePtr, tableSize);
    hash_table_entry* entry = hashTablePtr[hashIndex]; // gets hash table contents at supposed index for comparison

    if (entry == NULL) {
        cout << "Application " << *appNamePtr << " not found." << endl << endl;
        delete appNamePtr;
        return;
    }

    if (entry->app_name == *appNamePtr) { // if app name is at head of chat at index
        cout << "Found Application: " << *appNamePtr << endl;
        cout << *(entry->app_node->getData())<< endl; // gets name from node at hash table index
    } else { // check for separate chaining if entry isn't empty and app isn't at head
        hash_table_entry* next = entry->next; // look at next entry in chain
        while (next != NULL) { //while there are apps in chain
            if (next->app_name == *appNamePtr) { // if name matches
                cout << "Found Application: " << *appNamePtr << endl;
                cout << *(next->app_node->getData())<< endl; // gets name from node at hash table index
                delete appNamePtr;
                return; // return if found
            }
            next = next->next; // continue if not found
        }
        cout << "Application " << *appNamePtr << " not found." << endl << endl; // if not found in chain : not found
        delete appNamePtr;
        return; // here for readability
    }
}

void findCat(string* queryLine, categories* appCats, int catQuant) {
    string* catNamePtr = new string; //needs to by dynamically allocated because getHashIndex() takes a string*
    *catNamePtr = queryLine->substr(14, queryLine->size() - 14); // receives cat name
    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        if (*catNamePtr == appCats[i] . category) { // when there is a match
            if (appCats[i] . root != NULL) {    // and the tree is not empty
                    int treeSize = appCats[i] . root->getSize();
                    app_info** treeArray = (appCats[i] . root->inOrderArray());
                    //cout << endl << treeArray [0]->category << endl;
                    for (int ii = 0; ii < treeSize; ii++) {
                        cout << "\t" << treeArray[ii] -> appName << endl;
                    }
            } else {
                cout << "Category " << *catNamePtr << " no apps found" << endl;
            }
            delete catNamePtr;
            return;
        }
    }
    cout << "Category " << *catNamePtr << " not found";
    delete catNamePtr;
}

void findFree(categories* appCats, int catQuant) {
    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        int treeSize = appCats[i] . root->getSize();
        app_info** treeArray = (appCats[i] . root->inOrderArray());
        cout << "Free Applications in Category:   " << treeArray [0]->category << endl;
        bool found = false;
        for (int ii = 0; ii < treeSize; ii++) {
            if (treeArray[ii] -> price == 0) {
                cout << "\t" << treeArray[ii]->appName << endl;
                found = true;
            }
        }
        if ( !found ) {
            cout << "\tNo free applications found." << endl;
        }
    }
}

void findPriceRange(string* queryLine, categories* appCats, int catQuant) { // need to fix cat name duplicate get
    int i = 6; // 7 is the index right after the space after range
    //string* catName = extractCat(queryLine, i);
    string catName = "";
    // "price"
    string low = "";
    string high = "";
    char atI = queryLine->at(i);

    while (atI != ' ') {
        catName += atI;
        i++;
        atI = queryLine->at(i);
    }

    i += 7; // 7 here equals the number of chars in " price "
    atI = queryLine->at(i);

    while (atI != ' ') {
        low += atI;
        i++;
        atI = queryLine->at(i);
    }

    i++;
    atI = queryLine->at(i);

    while (atI != ' ' && (i < queryLine->length())) {
        high += atI;
        i++;
        //atI = queryLine->at(i);
        if (i < queryLine->length()) {
            atI = queryLine->at(i);
        }
    }

    float lowFloat = stof(low);
    float highFloat = stof(high);

    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        if (catName == appCats[i] . category) { // when there is a match
            if (appCats[i] . root != NULL) {    // and the tree is not empty
                int treeSize = appCats[i] . root->getSize();
                app_info** treeArray = (appCats[i] . root->inOrderArray());
                bool found = false; /// yes I know this is horrific
                for (int ii = 0; ii < treeSize; ii++) {
                    if ( lowFloat < treeArray[ii]->price && treeArray[ii]->price < highFloat) {
                        found = true;
                    }
                }
                if (found == true) {
                    printf("Applications in price range ($%.2f,$%.2f) in Category: ", lowFloat, highFloat);
                    cout << appCats[i].category << endl;
                } else {
                    printf("No applications found in %s for the given price range ($%.2f,$%.2f) \n", catName.c_str(), lowFloat, highFloat);

                }
                for (int ii = 0; ii < treeSize; ii++) {
                    if ( lowFloat < treeArray[ii]->price && treeArray[ii]->price < highFloat) {
                        cout << "\t" << treeArray[ii] -> appName << endl;
                    }
                }
            }
            return;
        }
    }
}

void findAppRange(string* queryLine, categories* appCats, int catQuant) { // need to fix cat name duplicate get catName /// non inclusive first letter range...?

    int i = 6; // 7 is the index right after the space after range
    //string* catName = extractCat(queryLine, i);
    string catName = "";
    // "price"
    char low;
    char high;
    char atI = queryLine->at(i);

    while (atI != ' ') {
        catName += atI;
        i++;
        atI = queryLine->at(i);
    }

    i += 5; // 7 here equals the number of chars in " app "
    atI = queryLine->at(i);

    while (atI != ' ') {
        low += atI;
        i++;
        atI = queryLine->at(i);
    }

    i++;
    atI = queryLine->at(i);

    while (atI != ' ' && (i < queryLine->length())) {
        high += atI;
        i++;
        //atI = queryLine->at(i);
        if (i < queryLine->length()) {
            atI = queryLine->at(i);
        }
    }

    int lowInt = (int) low;
    int highInt = (int) high;

    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        if (catName == appCats[i] . category) { // when there is a match
            if (appCats[i] . root != NULL) {    // and the tree is not empty
                int treeSize = appCats[i] . root->getSize();
                app_info** treeArray = (appCats[i] . root->inOrderArray());
                bool found = false;
                for (int ii = 0; ii < treeSize; ii++) {
                    int firstLetterInt = (int) treeArray[ii]->appName[0];
                    if ( lowInt < firstLetterInt &&  firstLetterInt < highInt) {
                        found = true;
                    }
                }
                if (found == true) {
                    cout << "Applications in Range (" << low << "," << high << ")" << " in Category: " << catName
                         << endl;
                } else {
                    cout << "No applications found in " << catName << " for the given range (" << low << "," << high << ")" << endl;
                }

                for (int ii = 0; ii < treeSize; ii++) {
                    int firstLetterInt = (int) treeArray[ii]->appName[0];
                    if ( lowInt < firstLetterInt &&  firstLetterInt < highInt) {
                        cout << "\t" << treeArray[ii] -> appName << endl;
                    }
                }
            } else {
                cout << "No applications found in " << catName << " for the given price range (" << low << ", " << high << ")" << endl;
            }
            return;
        }
    }
}

void printCatArray(categories* appCats, int catQuant) {
    for (int i = 0; i < catQuant; i++) { // searches for app category in list
        int treeSize = appCats[i] . root->getSize();
        app_info** treeArray = (appCats[i] . root->inOrderArray());
        cout << endl << treeArray [0]->category << endl;
        for (int ii = 0; ii < treeSize; ii++) {
            cout << treeArray[ii] -> appName << endl;
        }
    }
}

void printHashTable(hash_table_entry** hashTablePtr, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        if (hashTablePtr[i] != NULL) {
            cout << (hashTablePtr[i])->app_name << endl;
        }
    }
}

void runReport() {

}
