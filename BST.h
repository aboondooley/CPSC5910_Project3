//
// Created by Alie on 10/17/2020.
//

#ifndef P3_BST_BST_H
#define P3_BST_BST_H


class BST {

public:
    /**
     * No argument constructor
     */
    BST();

    /**
     * Destructor
     */
    ~BST();

    /**
     * Copy constructor
     * @param other the BST object to copy
     */
    BST(const BST &other);

    /**
     * Assignment operator overload
     * @param rhs BST object to copy
     * @return me!
     */
    BST &operator=(BST &rhs);

    /**
     * Checks if the key (int) exists in the tree/set
     * @param key the key value to check for
     * @return true if the value is in the tree, false if not
     * @post the key is still in the tree
     */
    bool has(int key) const;

    /**
     * Adds the key value in the appropriate spot in the tree, if it is not
     * already there
     * @param newKey the key value to add
     * @post the key is only in the tree once
     */
    void add(int newKey);

    /**
     * Removes the specified key value and reorganizes the tree, if
     * necessary, so it is still a BST
     * @param key the key value to add
     * @post the tree is still a BST
     */
    void remove(int key);

    /**
     * Checks whether the tree is empty
     * @return true if empty, false if not
     */
    bool empty() const;

    /**
     * Checks the size of the tree
     * @return the number of nodes in the tree
     */
    int size() const;

    /**
     * Checks how many leaves are in the tree
     * @return the number of nodes that are leaves
     */
    int getLeafCount() const;

private:
    /**
     * Node struct to build our tree with
     */
    struct Node{
        int key;
        Node *left, *right;

        // convenience constructor
        Node(int k, Node *lch, Node *rch){
            key = k;
            left = lch; // always think of left before right
            right = rch;
        }

        /**
         * Finds the maximum value in the tree, with the root being the
         * current node
         * @return the maximum value
         */
        int findMax() const;

    public:
        /**
         * Checks whether the node is a leaf
         * @return true if it is a leaf, false if not
         */
        bool isLeaf() const;
    };
    /**
     * The root of the BST object
     */
    Node *root;

    /**
     * Recursive helper function for has()
     * @param me the root of the subtree in which to look for the key
     * @param key the value to search for
     * @return true if the value exists, false if not
     */
    static bool has(Node *me, int key);

    /**
     * Recursive helper for the add() method
     * @param me the root of the subtree in which to add the key to
     * @param key the value to add
     * @return me or the new right or left child node
     */
    static Node *add(Node *me, int key);

    /**
     * Recursive helper for the remove() method
     * @param me the root of the subtree in which to remove the key
     * @param key the value to remove
     * @return me or the new left or right child node
     */
    static Node *remove(Node *me, int key);

    /**
     * Recursive helper for the copy() method
     * @param me the root of the subtree to copy
     * @return a copy of the subtree
     */
    static Node *copy(Node *me);

    /**
     * Recusrive helper for the clear() method
     * @param me the root of the subtree to delete
     */
    static void clear(Node *me);

    /**
     * Recursive helper for the size() method
     * @param me the root of the subtree of which to check the size
     * @return size of the subtree
     */
    static int size(Node *me);

    /**
     * Recursive helper for getLeafCount()
     * @param me the root of the subtree of which to count the number of leaves
     * @return the number of leaves in the subtree
     */
    static int getLeafCount(Node *me);
};


#endif //P3_BST_BST_H
