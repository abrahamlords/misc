#include <string>
#include <iostream>
#include "BTree.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::size_t;

struct app_info{
    static void operator delete(void* ptr, std::size_t sz) {
        //cout << "custom delete for size " << sz <<endl;
        delete (ptr); // ::operator delete(ptr) can also be used
    }
    static void operator delete[](void* ptr, std::size_t sz) {
        //cout << "custom delete for size " << sz <<endl;
        delete (ptr); // ::operator delete(ptr) can also be used
    }
    //~app_info();
    string category; // Name of category
    string appName; // Name of the application
    string version; // Version number
    float size; // Size of the application
    string units; // GB or MB
    float price; // Price in $ of the application
    bool operator==(const app_info& app);   // overloaded == compares appName when comparing app_infos
    bool operator<(const app_info& app);   // overloaded < compares appName when comparing app_infos
    bool operator>(const app_info& app);   // overloaded > compares appName when comparing app_infos
    friend ostream &operator<<(ostream& out, const app_info& app);   // overloaded << for printing whole struct
};

//app_info::~app_info() {
//    //delete & category; // Name of category
//    //  ...I need help
//}


//struct tree{ // A binary search tree
//    struct app_info record; // Information about the application
//    struct tree* left;  // Pointer to the left subtree
//    struct tree* right;  // Pointer to the right subtree
//};

struct categories{
    ~categories();
    string category; // Name of category
    BTree<app_info>* root;  // Pointer to root of search tree for this category
};

categories::~categories() {
    category = "";
    delete root;
}

struct hash_table_entry{
    string app_name; // Name of the application
    class Node<app_info>* app_node; // Pointer to node in tree containing the application information
    //struct tree* app_node;
    struct hash_table_entry* next; // Next pointer for chain in separate chaining
};


bool app_info::operator==(const app_info& app) {
    if (this->appName.compare(app.appName) == 0) {
        return true;
    }
    return false;
}
bool app_info::operator<(const app_info& app) {
    if (this->appName.compare(app.appName) < 0) {
        return true;
    }
    return false;
}
bool app_info::operator>(const app_info& app) {
    if (this->appName.compare(app.appName) > 0) {
        return true;
    }
    return false;
}
ostream &operator<<(ostream& out, const app_info& app) {
    out << "\tCategory: " << app.category << endl;
    out << "\tApplication Name: " << app.appName  << endl;
    out << "\tVersion: " << app.version  << endl;
    printf("\tSize: %.1f\n", app.size);
    //out << "\tSize: " << app.size     << endl;
    out << "\tUnits: " << app.units    << endl;
    printf("\tPrice: $%.2f\n", app.price);
    //out << "\tPrice: $" << app.price    << endl;
    return out;
}