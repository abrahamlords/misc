#include <iostream>
#include <string>
using namespace std;

int getLetterQuantity(string* clusterLinePtr, int &i);
string getLLastLine(string* clusterLinePtr);
void swapZsDecode(string &first, int j, int i);
int partionDecode(string &first, int lowIndex, int highIndex);
void quicksortDecode(string &first, int lowIndex, int highIndex);
//int getNextIndex(string &first, string &last, int textLineLength);
void insertionSortDecode(string &first, int lowIndex, int highIndex);  //inclusive range
int eggZit(int exitCode, int argc, char** argv);

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
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

    while (!cin.eof()) {                                //while not the end of file
        /// index line ///
        string *indexLinePtr = new string;
        getline(cin, *indexLinePtr);             // getline

        int indexLineLength = indexLinePtr->size();     // get line length of original line index (derived from cyclic array)

        if (indexLineLength != 0) {                     // if empty line -> cout << endl;   else -> continue
            int orgLineIndex = stoi(*indexLinePtr);

            //// cluster line ////
            string *clusterLinePtr = new string;
            getline(cin, *clusterLinePtr);          // get line of clusters

            /// get last from cluster ///
            string last = getLLastLine(clusterLinePtr);    // decodes cluster and puts in "last"
            int textLineLength = last.size();              // length of cluster line

            /// sort last to get first ///
            string first = last;                            // makes copy of last to sort to get first col
            if (c == "quick") {
                quicksortDecode(first, 0, textLineLength - 1);   // sorts last
            } else {
                insertionSortDecode(first, 0, textLineLength - 1);
            }

            int next[textLineLength];                       // declares int[] for indexes
            string lastCopy = last;                         // makes copy of last  // last will be consumed in

            /// get array of nexts ///
            for (int i = 0; i < textLineLength; i++) { // cycle through each char to find its corresponding next index
                char fchar = first[i];
                int j = 0;
                char lchar = last[j];
                while (j + 1 < textLineLength && fchar != lchar) {
                    j++;                // advances j until a match is found (indicating a next index)
                    lchar = last[j];
                }
                next[i] = j;            // store j in array of nexts
                last[j] = (char) 0;      // replace last[j] with NULL char to prevent dupicate j's in next[]
            }

            /// build original lines ///
            string orgLine = "";
            int pos = next[orgLineIndex]; // pos = index of next lastline char to fall into the original line
            for (int i = 0; i < textLineLength; i++) { // jumps around array according to pos, but keeps loop limited to amt of chars
                orgLine += lastCopy[pos];
                pos = next[pos]; // follows the array of nexts to construct orgLine
            }

            /// get decoded line from last[nexts] loop ///
            cout << orgLine;
            if (!cin.eof()) {
                cout << endl; //represent blank line
            }

        } else { /// handle empty lines ///
            if (!cin.eof()) {
                cout << endl; //represent blank line
            }
        }
    }

    return 0;
}

int getLetterQuantity(string* clusterLinePtr, int &i) { // reads cluster int
    string num = "";
    char c = clusterLinePtr[0][i];

    while (c != ' '  &&  i < clusterLinePtr->size()-1) { // advances to next next int based off the structure of cluster line
        num += c; // handles every deciaml place (ones, tens, hundreds)
        i++;
        c = clusterLinePtr[0][i]; // makes advancement
    }
    return stoi(num);
}

string getLLastLine(string* clusterLinePtr) {    /// get letter count / get last chars column ///
    string lastCharsCol = "";
    int i = 0;
    while ( i < clusterLinePtr->size()) {

        int letterQuantity = getLetterQuantity(clusterLinePtr, i); // reads cluster int

        char c = clusterLinePtr[0][++i]; // reads cluster letter

        for (int j = 0; j < letterQuantity; j++) { // fills last line with cluster letter * cluster int
            lastCharsCol += c;
        }
        i += 2;  // advances by 2 to account for spaces
    }
    return lastCharsCol;
}

void swapZsDecode(string &first, int j, int i) { // swaps string pointers in array
    char temp = first[j];
    first[j] = first[i];
    first[i] = temp;
}

int partionDecode(string &first, int lowIndex, int highIndex) {
    int pivotIndex = highIndex;
    int compareIndex = lowIndex;
    int storeIndex = lowIndex;

    while (compareIndex < pivotIndex) { // if pivot is greater than compared value
        int atPivot = (int)first[pivotIndex]; // gets char at lower bound - pass represents char index of line string
        int atCompare = (int)first[compareIndex]; // gets char at higher bound - pass represents char index of line string

        if (atPivot >= atCompare) {
            swapZsDecode(first, compareIndex, storeIndex); // the compared value is swapped with the value at storeIndex via pointer
            storeIndex++;                                       // then advances storeIndex
        }
        compareIndex++;     // goes to next
    }
    swapZsDecode(first, pivotIndex, storeIndex); // at this point, the storeIndex is at the final position of the current pivot
    pivotIndex = storeIndex;        // the new pivot gets updated and returned
    return pivotIndex;
}

void quicksortDecode(string &first, int lowIndex, int highIndex) {
    if (lowIndex < highIndex) {
        int q = partionDecode(first, lowIndex, highIndex); // creates sub-ranges of array to sort
        quicksortDecode(first, lowIndex, q - 1); // recursively sorts one side of pivot
        quicksortDecode(first, q + 1, highIndex); // recursively sorts one side of other side
    }
}

void insertionSortDecode(string &first, int lowIndex, int highIndex) { //inclusive range
    for (int j = lowIndex + 1; j <= highIndex; j++)  { //inclusive range
        char key = first[j];
        int atKey = (int)key;   // ascii val of char
        int i = j-1;            // compares key to left of key first then makes its way left

        while (i >= lowIndex && (int)first[i] > atKey) { //atCompare > atKey
            first[i + 1] = first[i]; // performas a shift
            i--;
        }
        first[i+1] = key; //acounts for the subtaction in the while loop
    }
}

int eggZit(int exitCode, int argc, char** argv) { // 0 if no args // 1 if wrong arg // 2 if 2many args
    if (exitCode > 0) { // if there are args then echo wrong input to show the exact error
        cout << "\"";
        for ( int i = 1; i < argc; i++) { // serves to dynamically echo all args in correct format
            string c = argv[i];
            cout << c;
            if (i+1 != argc) {
                cout << " ";
            }
        }
        cout << "\" is not a suported command. ";
    }
    cout << "Please use commands \"insertion\" or \"quick\"." << endl; // will print for any incorrect input
    return exitCode+1;
}

////////// fix ///////////
/// passes string
/// break up responsibilities

//void insertionSortDecode(string &first, int lowIndex, int highIndex) { //inclusive range
//    for (int j = lowIndex + 1; j <= highIndex; j++)  { //inclusive range
//        //string* key = cyclicLineArr[j];
//        //int atKey = (int)cyclicLineArr[j][0][pass];
//        char key = first[j];
//        int atKey = (int)first[j];
//        int i = j-1;
//        //int atCompare = (int)cyclicLineArr[i][0][pass];
//
//        while (i >= lowIndex && (int)first[j] > atKey) { //atCompare > atKey
//            //atCompare = (int)cyclicLineArr[i][0][pass];
//            first[i + 1] = first[i];
//            i--;
//        }
//        first[i+1] = key;
//    }
//}

/// int getNextIndex(string &first, string &last, int textLineLength) {
///     for (int i = 0; i < textLineLength; i++) {
///         char fchar = first[i];
///         int j = 0;
///         char lchar = last[j];
///         while (j+1 < textLineLength && fchar != lchar) {
///             j++;
///             lchar = last[j];
///         }
///         last[j] = (char)0;      // replace lat[j] with NULL char to prevent dupicate j's in next[]
///         return j;               // return j to store in array of nexts
///     }
/// }
///