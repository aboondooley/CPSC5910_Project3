//
// Created by Alie on 10/17/2020.
//

#ifndef P3_BST_BST_H
#define P3_BST_BST_H
#include <algorithm>
#include <sstream>

/**
 * BST Template Class is a binary search tree which holds elements of any
 * primitive type. The elements are ordered in ascending order going left to
 * right, for example the largest value in the tree will be found on the
 * bottom level on the left-most side.
 * A you can get the height, number of nodes (size), number of leaves,
 * whether the tree is empty, and check the three types of traversals of the
 * tree (pre-order, in-order, and post-order.)
 * You can also add, remove, and see if a particular element is in the tree.
 * The tree can have up to one instance of an element - no duplicates.
 * @tparam KeyType the type of the elements in the BST object - can be any
 * primitive type
 */
template<typename KeyType>
class BST {
private:
    struct Node; // forward declaration

public:
    /**
     * No argument constructor
     */
    BST() {
        root = nullptr;
    }

    /**
     * Destructor
     */
    ~BST(){
        clear(root); // delete the root and everything below
    }

    /**
     * Copy constructor
     * @param other the BST object to copy
     */
    BST(const BST &other) {
        root = copy(other.root);
    }

    /**
     * Assignment operator overload
     * @param rhs BST object to copy
     * @return me!
     */
    BST<KeyType> &operator=(BST<KeyType> &rhs) {
        if (&rhs != this){
            clear(root);
            root = copy(rhs.root);
        }
        return *this;
    }

    /**
     * Checks if the key (int) exists in the tree/set
     * @param key the key value to check for
     * @return true if the value is in the tree, false if not
     * @post the key is still in the tree
     */
    bool has(KeyType key) const {
        return has(root, key);
    }

    /**
     * Adds the key value in the appropriate spot in the tree, if it is not
     * already there
     * @param newKey the key value to add
     * @post the key is only in the tree once
     */
    void add(KeyType newKey) {
        root = add(root, newKey);
    }

    /**
     * Removes the specified key value and reorganizes the tree, if
     * necessary, so it is still a BST
     * @param key the key value to add
     * @post the tree is still a BST
     */
    void remove(KeyType key) {
        root = remove(root, key);
    }

    /**
     * Checks whether the tree is empty
     * @return true if empty, false if not
     */
    bool empty() const {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

    /**
     * Checks the size of the tree
     * @return the number of nodes in the tree
     */
    int size() const {
        return size(root);
    }

    /**
     * Checks how many leaves are in the tree
     * @return the number of nodes that are leaves
     */
    int getLeafCount() const {
        return getLeafCount(root);
    }

    /**
     * Returns the height of the tree. An empty tree has a height or zero
     * A tree with only a root has a height of one
     * A tree with a root and one child has a height of two, and so on
     * @return height
     */
    int getHeight() const {
        return getHeight(root);
    }

    /**
     * Gets the node values in order from the BST
     * @return a string containing the nodes' payloads in order
     */
    std::string getInOrderTraversal() const {
        return getInOrderTraversal(root);
    }

    /**
     * Gets the payload values in pre order from the BST
     * @return a string containing the nodes' payloads in pre order
     */
    std::string getPreOrderTraversal() const {
        return getPreOrderTraversal(root);
    }


    /**
     * Gets the payload values in post order from the BST
     * @return a string containing the nodes' payloads in post order
     */
    std::string getPostOrderTraversal() const {
        return getPostOrderTraversal(root);
    }

private:
    /**
     * Node struct to build our tree
     */
    struct Node {
        KeyType key;
        Node *left, *right;

        // convenience constructor
        Node(KeyType k, Node *lch, Node *rch){
            key = k;
            left = lch; // always think of left before right
            right = rch;
        }

        /**
         * Finds the maximum value in the tree, with the root being the
         * current node
         * @return the maximum value
         */
        KeyType findMax() const {
            if (right == nullptr)
                return key;
            else
                return right->findMax();
        }

        /**
         * Checks whether the node is a leaf
         * @return true if it is a leaf, false if not
         */
        bool isLeaf() const {
            if (left == nullptr && right == nullptr){
                return true;
            }
            return false;
        }
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
    static bool has(Node *me, KeyType key) {
        if (me == nullptr)
            return false;
        if (key < me->key)
            return has(me->left, key);
        if (key > me->key)
            return has(me->right, key);
        // key == me->key
        return true;
    }

    /**
     * Recursive helper for the add() method
     * @param me the root of the subtree in which to add the key to
     * @param newKey the value to add
     * @return me or the new right or left child node
     */
    static Node *add(Node *me, KeyType newKey) {
        if (me == nullptr)
            // this is where I go!!
            me = new Node(newKey, nullptr, nullptr);
        else if (newKey < me->key)
            me->left = add(me->left, newKey);
        else if (newKey > me->key)
            me->right = add(me->right, newKey);
        // else equal (key already in set) - do nothing
        return me;
    }

    /**
     * Recursive helper for the remove() method
     * @param me the root of the subtree in which to remove the key
     * @param key the value to remove
     * @return me or the new left or right child node
     */
    static Node *remove(Node *me, KeyType rKey) {
        if (me == nullptr)
            return nullptr; // nothing to remove, key not found
        if (rKey < me->key) {
            me->left = remove(me->left, rKey);
            return me;
        } else if (rKey > me->key) {
            me->right = remove(me->right, rKey);
            return me;
        } else {
            // FOUND IT!
            if (me->left == nullptr) {
                Node *myReplacement = me->right;
                delete me;
                return myReplacement;
            } else if (me->right == nullptr) {
                Node *myReplacement = me->left;
                delete me;
                return myReplacement;
            } else {
                // replace me with max element in my left subtree
                me->key = me->left->findMax();
                me->left = remove(me->left, me->key);
                return me;
            }
        }
    }

    /**
     * Recursive helper for the copy() method
     * @param me the root of the subtree to copy
     * @return a copy of the subtree
     */
    static Node *copy(Node *me) {
        if (me == nullptr) {
            return nullptr;
        }
        new Node(me->key, copy(me->left), copy(me->right));
    }

    /**
     * Recursive helper for the clear() method
     * @param me the root of the subtree to delete
     */
    static void clear(Node *me) {
        if (me != nullptr) {
            clear(me->left);
            clear(me->right);
            delete me;
        }
    }

    /**
     * Recursive helper for the size() method
     * @param me the root of the subtree of which to check the size
     * @return size of the subtree
     */
    static int size(Node *me) {
        if (me == nullptr)
            return 0;
        return 1 + size(me->right) + size(me->left);
    }

    /**
     * Recursive helper for getLeafCount()
     * @param me the root of the subtree of which to count the number of leaves
     * @return the number of leaves in the subtree
     */
    static int getLeafCount(Node *me) {
        if (me == nullptr)
            return 0;
        if (me->isLeaf())
            return 1;
        return getLeafCount(me->left) + getLeafCount(me->right);
    }

    /**
     * Recursive helper for getHeight()
     * @param me the root of the subtree to get the height of
     * @return height of the subtree
     */
    static int getHeight(Node *me) {
        if (me == nullptr)
            return 0;
        return 1 + std::max(getHeight(me->right), getHeight(me->left));
    }

    /**
    * Recursive helper for te getInOrderTraversal method
    * @param me the subtree to get the in-order traversal of
    * @return returns the nodes in-order from the subtree
    */
    static std::string getInOrderTraversal(Node *me) {
        if (me == nullptr) { // basecase
            return "";
        }
        std::stringstream ss; // create a stringstream object to collect the
        // tree elements that are returned
        ss << getInOrderTraversal(me->left) << me->key << " " <<
           getInOrderTraversal(me->right);
        return ss.str();
    }

    /**
     * Recursive helper for the getPreOrderTraversal method
     * @param me the subtree to get the pre-order traversal of
     * @return the nodes in pre-order from the subtree
     */
    static std::string getPreOrderTraversal(Node *me) {
        if (me == nullptr) {
            return "";
        }
        std::stringstream ss;
        ss << me->key << " " << getPreOrderTraversal(me->left) <<
           getPreOrderTraversal(me->right);
        return ss.str();
    }

    /**
     * Recursive helper for the getPostOrderTraversal method
     * @param me the subtree to get the post-order traversal of
     * @return the nodes in post-order from the subtree
     */
    static std::string getPostOrderTraversal(Node *me) {
        if (me == nullptr) {
            return "";
        }
        std::stringstream ss;
        ss << getPostOrderTraversal(me->left) <<
           getPostOrderTraversal(me->right) << me->key << " ";
        return ss.str();
    }

};



#endif //P3_BST_BST_H
