#ifndef CSE310PROJEC2_BTREE_H
#define CSE310PROJEC2_BTREE_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


template <typename T>
class Node {
private:
    T* data;    // pointer to generic item
    Node<T>* parent;  // pointer to the parent node // latest edition made for BST removal - only used there and add() to accommodate
    Node<T>* left;  // pointer to left sub node
    Node<T>* right;  // pointer to right sub node
public:
//    Node();
    Node(T* item);
    ~Node();
    T* getData();
    Node<T>* getLeft();
    Node<T>* getRight();
    int getHeight();
    Node<T>* add(T* item);
    void removeNode();
    int compare2(Node<T>* nodePtr);
    bool has(T* item);
    void leftreePrint();
    void rightreePrint();
    void leftreeDelete();
    void rightreeDelete();
    void leftreeReturn(int& i, T**& inOrderArray);
    void rightreeReturn(int& i, T**& inOrderArray);
};

template <typename T>
Node<T>::Node(T* item) {
    data = item;
    parent = NULL;
    left = NULL;
    right = NULL;
}

template <typename T>
Node<T>::~Node() {
    delete data; // calls generic's deconstructor
    //data = NULL; // but I don't know how to make a struct deconstructor yet
    parent = NULL;
    left = NULL;
    right = NULL;
}

template <typename T>
Node<T>* Node<T>::getLeft() {
    return this->left;
}

template <typename T>
Node<T>* Node<T>::getRight() {
    return this->right;
}

template <typename T>
T * Node<T>::getData() {
    return data;
}

template <typename T>
int Node<T>::getHeight() {
    if (this == NULL) {
        return 0;
    } else {
        int leftHeight = this->left->getHeight();
        int rightHeight = this->right->getHeight();

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}

template <typename T>
Node<T>* Node<T>::add(T* item) { // adds to tree recursively for item in classic BST style // returns this node's pointer for hash tables and the like
    Node* newNode = new Node(item);
    int comparison = newNode->compare2(this);

    if (comparison > 0) {
        if (this->right == NULL) {
            this->right = newNode;
            newNode->parent = this; // new addition
        } else {
            this->right->add(item);
        }
    }
    if (comparison <= 0 )  {
        if (this->left == NULL) {
            this->left = newNode;
            newNode->parent = this; // new addition
        } else {
            this->left->add(item);
        }
    }
    return newNode;
}

template <typename T>
void Node<T>::removeNode() {
    if (this->parent == NULL) { // if root
        //find right most leaf on the left side and that's your new root
        Node<T>* curroot = this->left;
        while (curroot->right != NULL) {
            while (curroot->right != NULL) {
                curroot = curroot->right;
            }
            if (curroot->left != NULL) {
                curroot = curroot->left;
            }
        }
        //take leaf insert it into root
        //delete pointer to old leaf
        return;
    }
    if (this->right == NULL && this->left == NULL) { // if leaf
        this->parent == NULL;
        return;
    }
    // if branch
    if (this->left == NULL) { // if left is empty
        this->parent = this->right;
    } else {
        this->parent = this->left;
    }
}

template <typename T>
int Node<T>::compare2(Node<T>* that) { // compares this data with that data
    /// must used overloaded operators for your <T> to use compare2

    if (*(this->data) > *(that->data)) {
        return 1;
    } else {
        if (*(this->data) < *(that->data)) {
            return -1;
        }
    }
    return 0; // if equal
}

template <typename T>
bool Node<T>::has(T* item) { //searches tree recursively for item in classic BST style
    /// expects operator overloading to make comparisons

    if (item->compare2(this->data) == 0) {
        return true;
    }
    if (item->compare2(this->data) > 0) {
        if ( this->right != NULL) {
            if (this->right->has(item)) {
                return true;
            }
        }
    }
    if (item->compare2(this->data) < 0) {
        if (this->left != NULL) {
            if (this->left->has(item)) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void Node<T>::leftreePrint() {
    Node* curroot = this->left;             // starts at root->left
    if (curroot != NULL) {                  // proceed if not NULL
        if (this->left->left != NULL) {		// proceed if next two lefts are not NULL
            this->left->leftreePrint(); 	/// current root eventually becomes second to last left node
            if (curroot->right != NULL) {   // looks right upon return
                cout << *(curroot->data); 	// prints current before going right
                curroot->rightreePrint();	// goes right
            } else {                        // if no right
                cout << *(curroot->data); 	// prints current left before returning
            }
        } else {
            cout << *(curroot->data); 		/// first prints very left
            if (curroot->right != NULL) {   // looks right
                curroot->rightreePrint();	// goes right
            } 								// returns to previous call
        }
    }
}

template <typename T>
void Node<T>::rightreePrint() {
    Node* currootRight = this->right;           // starts at right
    if (currootRight != NULL) {                 // proceed if not NULL
        if (currootRight->left != NULL) {		// if has left
            currootRight->leftreePrint();		// go left
            if (currootRight->right != NULL) {	// looks right upon return
                cout << *(currootRight->data);  // prints current before going right
                currootRight->rightreePrint();	// goes right
            }  else {                           // if no right
                cout << *(currootRight->data); 	// prints current right before returning
            }
        } else {								// if doesn't have left
            cout << *(currootRight->data);		// print current
            if (currootRight->right != NULL) {	// look right
                currootRight->rightreePrint(); 	// go right
            }                                   // returns to previous call
        }
    }
}

template <typename T>
void Node<T>::leftreeDelete() {
    Node* curroot = this->left;				// starts at root->left
    if (curroot != NULL) {
        if (this->left->left != NULL) {		// proceed if not NULL
            this->left->leftreeDelete();	// proceed if next two lefts are not NULL
            if (curroot->right != NULL) {	/// current root eventually becomes second to last left node
                curroot->rightreeDelete();	// looks right upon return
                delete curroot;      	    // deletes current after going right
            } else {
                delete curroot;	            // deletes current left if no right before returning
            }
        } else {
            if (curroot->right != NULL) {	// looks right
                curroot->rightreeDelete();	// goes right
            }
            delete curroot; 		        /// deletes very left leaf first then works it's way up by recursively returning
        }                                   // goes to previous call
    }
}

template <typename T>
void Node<T>::rightreeDelete() {
    Node* currootRight = this->right;           // starts at right
    if (currootRight != NULL) {                 // proceed if not NULL
        if (currootRight->left != NULL) {       // if has left
            currootRight->leftreeDelete();	    // go left
            if (currootRight->right != NULL) {  // looks right upon return
                currootRight->rightreeDelete(); // goes right
                delete currootRight;            // deletes current after going right
            } else {
                delete currootRight;	            // deletes current right if no right before returning
            }
        } else {								// if doesn't have left
            if (currootRight->right != NULL) {	// look right
                currootRight->rightreeDelete(); // go right
            }
            delete currootRight;		        // deletes right
        }                                       // returns to previous call
    }
}

template <typename T>
void Node<T>::leftreeReturn(int& i, T**& inOrderArray) {
    Node* curroot = this->left;             // starts at root->left
    if (curroot != NULL) {                  // proceed if not NULL
        if (this->left->left != NULL) {		// proceed if next two lefts are not NULL
            this->left->leftreeReturn(i, inOrderArray); 	/// current root eventually becomes second to last left node
            if (curroot->right != NULL) {   // looks right upon return
                ///cout << "i :  "  << i << " stuff :  " << *(curroot->data); 	// prints current before going right
                inOrderArray[i] = curroot->data;
                i++;
                curroot->rightreeReturn(i, inOrderArray);	// goes right
            } else {                        // if no right
                ///cout << "i :  " << *(curroot->data); 	// prints current left before returning
                inOrderArray[i] = curroot->data;
                i++;
            }
        } else {
            ///cout << "i :  "  << i << " stuff :  " << *(curroot->data); 	            /// first prints very left
            inOrderArray[i] = curroot->data;
            i++;
            if (curroot->right != NULL) {   // looks right
                curroot->rightreeReturn(i, inOrderArray);	// goes right
            } 								// returns to previous call
        }
    }
}

template <typename T>
void Node<T>::rightreeReturn(int& i, T**& inOrderArray) {
    Node* currootRight = this->right;           // starts at right
    if (currootRight != NULL) {                 // proceed if not NULL
        if (currootRight->left != NULL) {		// if has left
            currootRight->leftreeReturn(i, inOrderArray);;		// go left
            if (currootRight->right != NULL) {	// looks right upon return
                ///cout << "i :  "  << i << " stuff :  " << *(currootRight->data);  // prints current before going right
                inOrderArray[i] = currootRight->data;
                i++;
                currootRight->rightreeReturn(i, inOrderArray);	// goes right
            } else {                        // if no right
                ///cout << "i :  " << *(currootRight->data); 	// prints current left before returning
                inOrderArray[i] = currootRight->data;
                i++;
            }
        } else {								// if doesn't have left
            ///cout << "i :  "  << i << " stuff :  " << *(currootRight->data);		// print current
            inOrderArray[i] = currootRight->data;
            i++;
            if (currootRight->right != NULL) {	// look right
                currootRight->rightreeReturn(i, inOrderArray); 	// go right
            }                                   // returns to previous call
        }
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//
//template <typename T>
//class BTree {
//private:
//    Node<T>* root;
//    int size;       //node count
//public:
//    BTree();
//    ~BTree();
//    Node<T>* add(T* item);
//    void removeNode(Node<T>* removalNode);
//    bool contains(T* item);
//    int getSize();
//    int getHeightRoot();
//    int getHeightLeft();
//    int getHeightRight();
//    void inOrderPrint();
//    T** inOrderArray();
//};
//
//template <typename T>
//int BTree<T>::getHeightLeft() {
//    return root->getLeft()->getHeight();
//}
//
//template <typename T>
//int BTree<T>::getHeightRight() {
//    return root->getRight()->getHeight();
//}
//
//template <typename T>
//int BTree<T>::getHeightRoot() {
//    return root->getHeight();
//}
//
//template <typename T>
//BTree<T>::BTree(){ // constructor
//    root = NULL;
//    size = 0;
//}
//
//template <typename T>
//BTree<T>::~BTree(){
//    if (size != 0) {
//        root->leftreeDelete();
//        root->rightreeDelete();
//        delete root; // deletes root's contents
//        root = NULL; // deletes pointer to empty contents
//        size = 0;
//    }
//}
//
//template <typename T>
//Node<T>* BTree<T>::add(T* item) { // returns Node* for hash table purposes and the like
//    if (size == 0) {
//        root = new Node<T>(item);
//        size++;
//        return root;
//    } else {
//        size++;
//        return root->add(item); // calls node's add(), not BTree's
//    }
//}
//
//template <typename T>
//void BTree<T>::removeNode(Node<T>* removalNode) {
//    removalNode->removeNode();
//    delete removalNode;
//}
//
//template <typename T>
//bool BTree<T>::contains(T* item) {
//    if (root->has(item)) {
//        return true;
//    }
//    return false;
//}
//
//template <typename T>
//int BTree<T>::getSize() {
//    return size;
//}
//
//template <typename T>
//void BTree<T>::inOrderPrint() { // prints in order of smallest data value to largest
//    if (root != NULL) {
//        root->leftreePrint();
//        cout << *(root->getData());// << endl;
//        root->rightreePrint();
//    }
//}
//
//template <typename T>
//T** BTree<T>::inOrderArray() { // prints in order of smallest data value to largest
//    T** inOrderArray = new T*[size];
//    int i = 0;
//    if (root != NULL) {
//        root->leftreeReturn(i, inOrderArray);
//        inOrderArray[i] = root->getData();
//        i++;
//        ///cout << *(root->getData()) << endl;
//        root->rightreeReturn(i, inOrderArray);
//    }
//    return inOrderArray;
//}
//
#endif //CSE310PROJEC2_BTREE_H
