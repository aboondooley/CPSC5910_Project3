#include <iostream>
#include "BST.h"
using namespace std;

int main() {
    BST bst;
    cout << "Height: " << bst.getHeight() << endl;
    cout << "Size: " << bst.size() << endl;
    cout << "Leaves: " << bst.getLeafCount() << endl << endl;
    cout << bst.getInOrderTraversal() << endl << endl;
    cout << bst.getPreOrderTraversal() << endl << endl;
    cout << bst.getPostOrderTraversal() << endl << endl;

    int input[] = {40, 20, 10, 30, 60, 50, 70};
    for (int i = 0; i < 7; i++)
        bst.add(input[i]);
    cout << "Height: " << bst.getHeight() << endl;
    cout << "Size: " << bst.size() << endl;
    cout << "Leaves: " << bst.getLeafCount() << endl << endl;
    cout << bst.getInOrderTraversal() << endl << endl;
    cout << bst.getPreOrderTraversal() << endl << endl;
    cout << bst.getPostOrderTraversal() << endl << endl;
    return 0;
}
