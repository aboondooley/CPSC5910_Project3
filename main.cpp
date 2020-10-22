#include <iostream>
#include <istream>
#include <fstream>
#include "BST.h"
using namespace std;

/**
 * Tests the structure of the tree, number of nodes, number of leaves, the
 * height and whether it is empty
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst a BST object
 */
template<typename T>
void prelimTest(BST<T> &bst) {
    cout << "# of nodes:  " << bst.size() << endl;
    cout << "# of leaves: " << bst.getLeafCount() << endl;
    cout << "BST height:  " << bst.getHeight() << endl;
    cout << "BST empty?   " << (bst.empty() ? "true" : "false") << endl;
}

/**
 * Loads in data of any primitive type from a file into the already created BST
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst a BST object to put the data into
 * @param file (complete) file path to the data to be loaded
 */
template<typename T>
void addFromFile(BST<T> &bst, string file){
    ifstream inFile;
    inFile.open(file);
    string line;
    T value;
    cout << "** TEST INSERT **" << endl;
    cout << "Inserting in this order: ";
    if (inFile){
        while(getline(inFile, line)){
            istringstream v(line);
            while (v >> value){
                cout << value << " ";
                bst.add(value);
            }
        }
    } else {
        cout << "Error: cannot open file." << endl;
    }
    cout << endl;
}

/**
 * Tests setting up the tree with an already created BST object
 * Asks the user for the file path, then adds all elements from the file to
 * the tree using addFromFile, and does the preliminary test (best and after
 * adding) to see the structure of the tree before and after
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst an empty BST object to set up
 * @param phrase used to prompt the user for the file path
 */
template<typename T>
void testSetUp(BST<T> &bst, string phrase){
    string file; // = "..\\strings.dat";
    cout << "** CREATE BST **" << endl;
    prelimTest(bst);
    cout << endl;
    cout << phrase;
    cin >> file;
    cout << endl;
    addFromFile(bst, file);
    prelimTest(bst);
    cout << endl;

}

/**
 * Tests each of the three traversals!
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst a BST object to traverse
 */
template<typename T>
void testTraversals(BST<T> &bst){
    cout << "pre-order:   " << bst.getPreOrderTraversal() << endl;
    cout << "pre-order:   " << bst.getInOrderTraversal() << endl;
    cout << "post-order:  " << bst.getPostOrderTraversal() << endl;
}

/**
 * Tests whether the tree has a particular element in it
 * Prints false if not found and true if the element is found
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst a BST object to check for values in
 * @param value value of type T to find in the tree
 */
template<typename T>
void testHas(BST<T> &bst, T value){
    cout << "has(" << value << "): " << (bst.has(value) ? "true" : "false" ) <<
    endl;
}

/**
 * Tests the remove() function, prints out the elements to remove in the
 * correct order then does the structure and traversal tests to make sure
 * everything removed correctly
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst the BST object of type T to remove from
 * @param toRemove an array of elements of type T to remove
 * @param size the size of the array of elements to remove
 */
template<typename T>
void testRemove(BST<T> &bst, T *toRemove, int size){
    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < size; i++){
        cout << toRemove[i] << " ";
        bst.remove(toRemove[i]);
    }
    cout << endl;
    prelimTest(bst);
    testTraversals(bst);
    cout << endl;
}

/**
 *
 * @tparam T the type of element the BST holds (any primitive type)
 * @param bst the BST object of type T to add to
 * @param toAdd an array of elements of type T to add
 * @param size the size of the array of elements to add
 */
template<typename T>
void testAddAgain(BST<T> &bst, T *toAdd, int size){
    cout << "** TEST INSERT (AGAIN) **" << endl;
    cout << "Inserting in this order: ";
    for (int i = 0; i < size; i++){
        cout << toAdd[i] << " ";
        bst.add(toAdd[i]);
    }
    cout << endl;
    prelimTest(bst);
    testTraversals(bst);
    cout << endl << endl;
}

/**
 * Main entry point to test both int and string BSTs
 * @return 0
 */
int main() {

    cout << "Welcome! " << endl <<
    "This program creates Binary Search Trees from data read from an input "
    "file." << endl <<
    "The number of nodes and leaves, as well as the height and whether the "
    "tree is empty is reported." << endl <<
    "All three types of traversal are given for the tree contents (pre-order,"
    " in-order, and post-order)." << endl <<
    "Then, the has(), remove(), and add() methods are tested." << endl <<
    endl <<
    "The BST will work for any primitive data type!" << endl <<
    "Please try it on ints and strings!" << endl <<
    "Enjoy" << endl << endl;


    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl << endl;

    BST<int> ibst;
    string phrase = "Enter integer file: ";
    testSetUp(ibst, phrase);

    cout << "** TEST TRAVERSALS **" << endl;
    testTraversals(ibst);
    cout << endl;

    cout << "** TEST CONTAINS **" << endl;
    int r[] = {20, 40, 10, 70, 99, -2, 59, 43};
    int size = 8;
    for (int i = 0; i < size; i++){
        testHas(ibst, r[i]);
    }
    cout << endl;

    testRemove(ibst, r, size);
    testAddAgain(ibst, r, size);


    cout << "*****************************" << endl;
    cout << "* STRING BINARY SEARCH TREE *" << endl;
    cout << "*****************************" << endl << endl;

    BST<string> sbst;
    string phrase2 = "Enter string file: ";
    testSetUp(sbst, phrase2);

    cout << "** TEST TRAVERSALS **" << endl;
    testTraversals(sbst);
    cout << endl;

    cout << "** TEST CONTAINS **" << endl;
    string a[] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron", "opal"};
    int size2 = 8;
    for (int i = 0; i < size2; i++){
        testHas(sbst, a[i]);
    }


    cout << endl;

    testRemove(sbst, a, size2);
    testAddAgain(sbst, a, size2);

    cout << "Goodbye!" << endl;

}
