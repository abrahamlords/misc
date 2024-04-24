#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

void fillCyclicLineArray(string** &cyclicLineArr, int lineLength, string* inputPtr);
void quicksort(string** &cyclicLineArr, int lowIndex, int highIndex, int pass);
int partion(string** &cyclicLineArr, int lowIndex, int highIndex, int pass);
void swapZs(string** &cyclicLineArr, int j, int i);
int duplicatesRangeFinder(string** &cyclicLineArr, int startIndexLine, int endIndexLine, int charIndex);
int clusterScan(string* last, int stringSize, int startIndex);
void printCLArray(string** &cyclicLineArray, int startIndex, int stopIndex, int place1, int place2);
void quicksortByASCII(string** &cyclicLineArray, int lineLowerBound, int lineUpperBound, int byCharIndex);
string* getLastLine(string** &cyclicLineArray, int lineLength);
int getOriginalStringIndex(string** &cyclicLineArray, string* inputPtr, int lineLength);
int fillClusterString(string* &clusterString, string* last, int lineLength);
void insertionSort(string** &cyclicLineArr, int lowerBound, int upperBound, int pass);
void insertionSortByASCII(string** &cyclicLineArray, int lineLowerBound, int lineUpperBound, int byCharIndex);
int eggZit(int exitCode, int argc, char** argv); // 0 if no args // 1 if wrong wrong arg // 2 if 2many args

////////////////////////////////////////////////////////////////////////////////////
// output:
// non empty lines in file
// chars in file
// clusters in file
/// change log :
// fillClusterString() now returns sigClusterCount               // not total cluster - signigificant clusters (size > 1)
// main()
//  - charsInFile
//  - clustersInEncodeFile
////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {

    if (argc != 2 ) {       // if there are too many or too few arguements
        if (argc > 2) {
            return eggZit(2, argc, argv);   // print instructions and return error code for too many
        } else {
            return eggZit(0, argc, argv);   // print instructions and return error code for too few
        }
    } else {
        string c = argv[1];
        if (c != "insertion" && c != "quick") {     // if correct number of args, but not correct args
            return eggZit(1, argc, argv);  // then print instructions and return error code for wrong args
        }
    }
    /// if correct args ///
    string c = argv[1]; // stores sorting method
    int nonEmptyLinesInFile = 0;
    int charsInFile = 0;
    int clustersInEncodeFile = 0;

    while (!cin.eof()) {                        //while not the end of file
        nonEmptyLinesInFile++;
        string* inputPtr = new string;          // initialize new string to store line
        getline(cin, *inputPtr);         // getline

        int lineLength = inputPtr->size();      // get line length

        if (lineLength != 0) {                                      // if empty line - cout << endl; else - continue
            cout << lineLength << endl;
            auto start = high_resolution_clock::now();

            string** cyclicLineArray = new string* [lineLength];         // create string* array of to scale

            fillCyclicLineArray(cyclicLineArray, lineLength, inputPtr);     // fill array with cyclical shifts
            //printCLArray(cyclicLineArray, 0, lineLength-1, 0, lineLength-1);     ///////////////////////////////
            //cout << endl;

            if (c == "quick") {
                quicksortByASCII(cyclicLineArray, 0,  lineLength-1, 0);
            }
            if (c == "insertion") {
                insertionSortByASCII(cyclicLineArray, 0,  lineLength-1, 0);
            }
            //cout << "-End of Sort-" << endl;

            //printCLArray(cyclicLineArray, 0, lineLength-1, 0, lineLength-1);    ///////////////////////////////
            //cout << endl;

            int originalStringIndex = getOriginalStringIndex(cyclicLineArray, inputPtr,
                                                             lineLength); // locate origianl string in sorted - return index
            string* last = getLastLine(cyclicLineArray, lineLength);    // get Last line

            string* clusterString = new string;                         // declare clusterString
            int clusterCount = fillClusterString(clusterString, last, lineLength);     // fill clusterString

            auto stop = high_resolution_clock::now();
            cout << lineLength - clusterCount << endl;
            auto duration = duration_cast<microseconds>(stop - start);
            cout << duration.count() << endl;

            ////cout << originalStringIndex << endl; // cout original line index above
            ////cout << *clusterString;      // and clustered last line on bottom
            if (!cin.eof()) {
                ////cout << endl;
            }
        } else {
            if (!cin.eof()) {
                ////cout << endl; //represent blank line
            }
        }
        //// next line ////
    }

    //cout << nonEmptyLinesInFile << endl;
    //cout << charsInFile << endl;
    //cout << charsInFile - clustersInEncodeFile << endl;

    return 0;
}
/// cyclicLineArray[string*][string][char]

int fillClusterString(string* &clusterString, string* last, int lineLength) {
    int startIndex = 0;
    int totClusterCount = 0;
    int sigClusterCount = 0;


    while (startIndex < lineLength && startIndex > -1) {   //loops through the string of last chars to idetify duplicate letters


        int stopIndex = clusterScan(last, lineLength, startIndex);  // stopIndex recieves the end of the last "cluster"
        *clusterString += to_string(stopIndex - startIndex + 1); // the difference between the range +1 gives # of chars in cluster
        //totClusterCount++;
        if ((stopIndex - startIndex + 1) > 1) {
            sigClusterCount++;
        }
        *clusterString += " ";
        *clusterString += last[0][startIndex];  // puts in char after count of said char
        startIndex = stopIndex + 1;     // recieves index of next cluster start to complete loop
        if (startIndex != lineLength) { // only adds space after char if it's not the final char in string
            *clusterString += " ";
        }
    }
    //return (totClusterCount - sigClusterCount);
    return sigClusterCount;
}

void insertionSort(string** &cyclicLineArr, int lowerBound, int upperBound, int pass) { //inclusive range
    for (int j = lowerBound + 1; j <= upperBound; j++)  { //inclusive range
        string* key = cyclicLineArr[j];
        int atKey = (int)cyclicLineArr[j][0][pass];
        int i = j-1;

        while (i >= lowerBound && (int)cyclicLineArr[i][0][pass] > atKey) { //atCompare > atKey
            cyclicLineArr[i + 1] = cyclicLineArr[i];
            i--;
        }
        cyclicLineArr[i+1] = key;
    }
}

void insertionSortByASCII(string** &cyclicLineArray, int lineLowerBound, int lineUpperBound, int byCharIndex) { // inclusive bounds
    if (lineLowerBound < lineUpperBound) {
        insertionSort(cyclicLineArray, lineLowerBound, lineUpperBound, byCharIndex);
        //printCLArray(cyclicLineArray, lineLowerBound, lineUpperBound, byCharIndex, byCharIndex + 1);

        int scanIndex = lineLowerBound;
        while (scanIndex < lineUpperBound) {
            int stopIndexLine = duplicatesRangeFinder(cyclicLineArray, scanIndex, lineUpperBound, byCharIndex);
            if (scanIndex != stopIndexLine) {
                insertionSortByASCII(cyclicLineArray, scanIndex, stopIndexLine, byCharIndex + 1);
                //printCLArray(cyclicLineArray, scanIndex, stopIndexLine, byCharIndex, byCharIndex + 1);
            }
            scanIndex = stopIndexLine + 1;
        }
    }
}

void quicksortByASCII(string** &cyclicLineArray, int lineLowerBound, int lineUpperBound, int byCharIndex) { // inclusive bounds
    if (lineLowerBound < lineUpperBound) {
        quicksort(cyclicLineArray, lineLowerBound, lineUpperBound, byCharIndex);
        //printCLArray(cyclicLineArray, lineLowerBound, lineUpperBound, byCharIndex, byCharIndex + 1);

        int scanIndex = lineLowerBound;
        while (scanIndex < lineUpperBound) {
            int stopIndexLine = duplicatesRangeFinder(cyclicLineArray, scanIndex, lineUpperBound, byCharIndex);
            if (scanIndex != stopIndexLine) {
                quicksortByASCII(cyclicLineArray, scanIndex, stopIndexLine, byCharIndex + 1);
                // printCLArray(cyclicLineArray, scanIndex, stopIndexLine, byCharIndex, byCharIndex + 1);
            }
            scanIndex = stopIndexLine + 1;
        }
    }
}



int clusterScan(string* last, int stringSize, int startIndex) {  // scans for duplicate chars to form final output cluster string
    char atStart = last[0][startIndex]; // starts at previous end of last scan and gets char at that index
    char atCompare = last[0][startIndex+1]; // compares to next over

    while (atStart == atCompare) {      // while there's a match
        startIndex++;                   // advances lower compare index
        if (startIndex == stringSize-1) { // if at the end of string
            return startIndex;            // return final index of string
        }
        atStart = last[0][startIndex];     // takes char at lower compare index
        atCompare = last[0][startIndex+1]; // takes char at higher compare index
    }
    return startIndex; //  outputs an inclusive range of duplicates , will return original start (range size of 0) if there is no duplicates
}

int duplicatesRangeFinder(string** &cyclicLineArr, int startIndexLine, int endIndexLine, int charIndex) { // returns lines with same char at charIndex // will never return startIndex >= arraySize
/// make sure endIndexLine is within Array bounds
    if (startIndexLine < endIndexLine) {
        int atStartLine = cyclicLineArr[startIndexLine][0][charIndex]; // starts at previous end of last scan and gets char at that index
        int atNextLine = cyclicLineArr[startIndexLine + 1][0][charIndex]; // gets next // "pass" represents the index of the compared chars

        while (atStartLine == atNextLine) {  // while there's a match
            startIndexLine++;               // advances lower compare index

            if (startIndexLine == endIndexLine) {  // if at end of range
                return startIndexLine;            // return return endIndexLine
            } // else
            atStartLine = cyclicLineArr[startIndexLine][0][charIndex]; // sets up for next loop
            atNextLine = cyclicLineArr[startIndexLine + 1][0][charIndex]; //
        }
        return startIndexLine;  // outputs an inclusive range of duplicates , will return original start (range size of 0) if there is no duplicate
    }
    cout << "\n\n\n startIndexLine >= endIndexLine somehow \n\n\n";
    return 999999999;
}

int getOriginalStringIndex(string** &cyclicLineArray, string* inputPtr, int lineLength) {
    for (int i = 0; i < lineLength; i++) {  // goes through cyclic array lines to find the original line
        if (inputPtr == cyclicLineArray[i]) {   // does this by comparing by pointers
            return i;      // captures original String Index
        }
    }
    return -1;  // returns -1 if no such pointer is found
}

string* getLastLine(string** &cyclicLineArray, int lineLength) { // returns a string filled with the last chars in the sorted list of cyclic lines
    string* last = new string[lineLength]; // this equals the last chars in the sorted list of cyclic lines
    for (int i = 0; i < lineLength; i++) { // cycles through array and takes last char of each line
        *last += cyclicLineArray[i][0][lineLength-1];
    }
    return last;
}

void fillCyclicLineArray(string** &cyclicLineArr, int lineLength, string* inputPtr) { // fills square array full of cyclic shifts of original
    cyclicLineArr[0] = inputPtr; // original line goes at 0
    string str = *inputPtr;      // dereferenced so I can use that sweet syntactic sugar []

    for (int cyclicIndex = 1; cyclicIndex < lineLength; cyclicIndex++) {

        string* shiftedInput = new string; // creates new string* for every new line
        string shiftedStr = *shiftedInput;

        for (int i = cyclicIndex; i < lineLength; i++) { // fills end of string first
            *shiftedInput += unsigned(str[i]);
        }
        for (int ii = 0; ii < cyclicIndex; ii++) { // fills the rest with the starting chars
            *shiftedInput += unsigned(str[ii]);
        }
        cyclicLineArr[cyclicIndex] = shiftedInput;  // stores pointer in master array
    }

}

void quicksort(string** &cyclicLineArr, int lowIndex, int highIndex, int pass) {
    if(lowIndex < highIndex) {
        int q = partion(cyclicLineArr, lowIndex, highIndex, pass); // creates sub-ranges of array to sort
        quicksort(cyclicLineArr, lowIndex, q-1, pass); // recursively sorts one side of pivot
        quicksort(cyclicLineArr, q+1, highIndex, pass); // recursively sorts one side of other side
    }
}

int partion( string** &cyclicLineArr, int lowIndex, int highIndex, int pass) {
    int pivotIndex = highIndex;
    int compareIndex = lowIndex;
    int storeIndex = lowIndex;

    while (compareIndex < pivotIndex) { // if pivot is greater than compared value
        int atPivot = (int)cyclicLineArr[pivotIndex][0][pass]; // gets char at lower bound - pass represents char index of line string
        int atCompare = (int)cyclicLineArr[compareIndex][0][pass]; // gets char at higher bound - pass represents char index of line string

        if (atPivot >= atCompare) {
            swapZs(cyclicLineArr, compareIndex, storeIndex); // the compared value is swapped with the value at storeIndex via pointer
            storeIndex++;                                       // then advances storeIndex
            //if (atPivot == atCompare) { // if these are equal
            //    hasDuplicates = 1;   // it means that there are duplicates at this char index // hasDuplicates is passed by reference
            //}
        }
        compareIndex++; // goes to next
    }
    swapZs(cyclicLineArr, pivotIndex, storeIndex); // at this point, the storeIndex is at the final position of the current pivot
    pivotIndex = storeIndex;        // the new pivot gets updated and returned
    return pivotIndex;
}

void swapZs(string** &cyclicLineArr, int j, int i) { // swaps string pointers in array
    string* temp = cyclicLineArr[j];
    cyclicLineArr[j] = cyclicLineArr[i];
    cyclicLineArr[i] = temp;
}

void printCLArray(string** &cyclicLineArray, int startIndex, int stopIndex, int place1, int place2) { // prints specified range (inclusive) of master array
    cout << "String length: " << cyclicLineArray[0]->size() << endl;
    for (int i = startIndex; i <= stopIndex; i++) {
        printf("%p  -%s- ", cyclicLineArray[i], cyclicLineArray[i][0].c_str());
        printf(" char at place %d:", place1);
        printf(" %c  %*d", cyclicLineArray[i][0][place1], 3, (int)cyclicLineArray[i][0][place1]);
        printf(" char at place %d:", place2);
        printf(" %c  %*d",  cyclicLineArray[i][0][place2], 3, (int)cyclicLineArray[i][0][place2]);
        printf("  line %d \n", i);
    }
}

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
    cout << "Please use commands \"insertion\" or \"quick\"." << endl;
    return exitCode+1;
}


/// int getLetterQuantity(string* clusterLinePtr, int &i) {
///     string num = "";
///     char c = clusterLinePtr[0][i];
///
///     while (c != ' '  &&  i < clusterLinePtr->size()-1) {
///         num += c;
///         i++;
///         c = clusterLinePtr[0][i];
///     }
///     return stoi(num);
/// }
///
/// string getLLastLine(string* clusterLinePtr) {
///     /// get letter count / get letter
///     string lastLine = "";
///     int i = 0;
///     while ( i < clusterLinePtr->size()) {
///
///         int letterQuantity = getLetterQuantity(clusterLinePtr, i);
///
///         char c = clusterLinePtr[0][++i];
///
///         for (int j = 0; j < letterQuantity; j++) {
///             lastLine += c;
///         }
///         i += 2;
///     }
///     return lastLine;
/// }
///
/// void swapZsDecode(string &first, int j, int i) { // swaps string pointers in array
///     char temp = first[j];
///     first[j] = first[i];
///     first[i] = temp;
/// }
///
/// int partionDecode(string &first, int lowIndex, int highIndex) {
///     int pivotIndex = highIndex;
///     int compareIndex = lowIndex;
///     int storeIndex = lowIndex;
///
///     while (compareIndex < pivotIndex) { // if pivot is greater than compared value
///         int atPivot = (int)first[pivotIndex]; // gets char at lower bound - pass represents char index of line string
///         int atCompare = (int)first[compareIndex]; // gets char at higher bound - pass represents char index of line string
///
///         if (atPivot >= atCompare) {
///             swapZsDecode(first, compareIndex, storeIndex); // the compared value is swapped with the value at storeIndex via pointer
///             storeIndex++;                                       // then advances storeIndex
///         }
///         compareIndex++; // goes to next
///     }
///     swapZsDecode(first, pivotIndex, storeIndex); // at this point, the storeIndex is at the final position of the current pivot
///     pivotIndex = storeIndex;        // the new pivot gets updated and returned
///     return pivotIndex;
/// }
///
/// void quicksortDecode(string &first, int lowIndex, int highIndex) {
///     if (lowIndex < highIndex) {
///         int q = partionDecode(first, lowIndex, highIndex); // creates sub-ranges of array to sort
///         quicksortDecode(first, lowIndex, q - 1); // recursively sorts one side of pivot
///         quicksortDecode(first, q + 1, highIndex); // recursively sorts one side of other side
///     }
/// }
///
/// //int getNextIndex(string* firstt, string* lastt, int textLineLength) {
/// //    string first = *firstt;
/// //    string last = *lastt;
/// //    for (int i = 0; i < textLineLength; i++) {
/// //        char fchar = first[i];
/// //        int j = 0;
/// //        char lchar = last[j];
/// //        while (j+1 < textLineLength && fchar != lchar) {
/// //            j++;
/// //            lchar = last[j];
/// //        }
/// //        last[j] = (char)0;      // replace lat[j] with NULL char to prevent dupicate j's in next[]
/// //        return j;               // return j to store in array of nexts
/// //
/// //        //char fchar = first[i];
/// //        //int j = 0;
/// //        //char lchar = last[j];
/// //        //while (j + 1 < textLineLength && fchar != lchar) {
/// //        //    j++;
/// //        //    lchar = last[j];
/// //        //}
/// //        //next[i] = j;            // store j in array of nexts
/// //        //last[j] = (char) 0;      // replace lat[j] with NULL char to prevent dupicate j's in next[]
/// //    }
/// //}
///
/// int decode() {
///     while (!cin.eof()) {
///         /// index line ///
///         string *indexLinePtr = new string;
///         getline(cin, *indexLinePtr);             // getline
///
///         int indexLineLength = indexLinePtr->size();     // get line length of original line index (derived from cyclic array)
///
///         if (indexLineLength != 0) {                     // if empty line -> cout << endl;   else -> continue
///             int orgLineIndex = stoi(*indexLinePtr);
///
///             //// cluster line ////
///             string *clusterLinePtr = new string;
///             getline(cin, *clusterLinePtr);          // get line of clusters
///
///             /// get last from cluster ///
///             string last = getLLastLine(clusterLinePtr);    // decodes cluster and puts in "last"
///             int textLineLength = last.size();
///
///             /// sort last to get first ///
///             string first = last;                            // makes copy of last to sort to get first col
///             quicksortDecode(first, 0, textLineLength - 1);   // sorts last
///
///             int next[textLineLength];                       // declares int[] for indexes
///             string lastCopy = last;                         // makes copy of last  // last will be consumed in
///
///             /// get array of nexts ///
///             for (int i = 0; i < textLineLength; i++) {
///                 char fchar = first[i];
///                 int j = 0;
///                 char lchar = last[j];
///                 while (j + 1 < textLineLength && fchar != lchar) {
///                     j++;
///                     lchar = last[j];
///                 }
///                 next[i] = j;            // store j in array of nexts
///                 last[j] = (char)0;      // replace lat[j] with NULL char to prevent dupicate j's in next[]
///             }
///
///             string orgLine = "";
///             int pos = next[orgLineIndex];
///             for (int i = 0; i < textLineLength; i++) {
///                 orgLine += lastCopy[pos];
///                 pos = next[pos];
///             }
///
///             /// get decoded line from last[nexts] loop ///
///             cout << orgLine;
///             if (!cin.eof()) {
///                 cout << endl; //represent blank line
///             }
///         } else {
///             if (!cin.eof()) {
///                 cout << endl; //represent blank line
///             }
///         }
///     }
///     return 0;
/// }
///