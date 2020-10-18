//
// Created by Alie on 10/17/2020.
//

#ifndef P3_BST_BST_H
#define P3_BST_BST_H
#include <algorithm>

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

    int getHeight() const;

    std::string getInOrderTraversal() const;

    std::string getPreOrderTraversal() const;

    std::string getPostOrderTraversal() const;


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

    static int getHeight(Node *me);

    static std::string getInOrderTraversal(Node *me);

    static std::string getPreOrderTraversal(Node *me);

    static std::string getPostOrderTraversal(Node *me);
};

int BST::getHeight() const {
    return getHeight(root);
}

int BST::getHeight(BST::Node *me) {
    if (me == nullptr)
        return 0;
    return 1 + std::max(getHeight(me->right), getHeight(me->left));
}

BST::BST() {
    root = nullptr;
}


BST::~BST() {
    clear(root); // delete the root and everything below
}


BST::BST(const BST &other) {
    root = copy(other.root);
}


BST &BST::operator=(BST &rhs) {
    if (&rhs != this){
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

// Lab 4 methods below!!

bool BST::empty() const {
    if (root == nullptr) {
        return true;
    }
    return false;
}


bool BST::Node::isLeaf() const { // also method of BST::Node
    if (left == nullptr && right == nullptr){
        return true;
    }
    return false;
}


int BST::size() const {
    return size(root);
}

// recursive helper!
int BST::size(BST::Node *me) {
    if (me == nullptr)
        return 0;
    return 1 + size(me->right) + size(me->left);
}


int BST::getLeafCount() const {
    return getLeafCount(root);
}

// recursive helper!
int BST::getLeafCount(BST::Node *me) {
    if (me == nullptr)
        return 0;
    if (me->isLeaf())
        return 1;
    return getLeafCount(me->left) + getLeafCount(me->right);
}

// Lab 4 methods above!!

bool BST::has(int key) const {
    return has(root, key);
}

bool BST::has(BST::Node *me, int key) {
    if (me == nullptr)
        return false;
    if (key < me->key)
        return has(me->left, key);
    if (key > me->key)
        return has(me->right, key);
    // key == me->key
    return true;
}

void BST::add(int newKey) {
    root = add(root, newKey);
}

// recursive helper
BST::Node *BST::add(BST::Node *me, int newKey) {
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


void BST::remove(int key) {
    root = remove(root, key);
}


BST::Node *BST::remove(BST::Node *me, int key) {
    if (me == nullptr)
        return nullptr; // nothing to remove, key not found
    if (key < me->key) {
        me->left = remove(me->left, key);
        return me;
    } else if (key > me->key) {
        me->right = remove(me->right, key);
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
        }
    }

}


int BST::Node::findMax() const { // method of BST::Node
    if (right == nullptr)
        return key;
    else
        return right->findMax();
}


void BST::clear(BST::Node *me) {
    if (me != nullptr) {
        clear(me->left);
        clear(me->right);
        delete me;
    }
    // base case is nothing! The implied else - if the next is a nullptr then
    // we do nothing bc there is nothing to clear!
}


BST::Node *BST::copy(BST::Node *me) {
    if (me == nullptr) {
        return nullptr;
    }
    new Node(me->key, copy(me->left), copy(me->right));
}

std::string BST::getInOrderTraversal() const {
    return getInOrderTraversal(root);
}

std::string BST::getInOrderTraversal(BST::Node *me) {
    if (me == nullptr) {
        return "";
    }
    return getInOrderTraversal(me->left) + " " + std::to_string(me->key)
    + " " + getInOrderTraversal(me->right);
}

std::string BST::getPreOrderTraversal() const {
    return getPreOrderTraversal(root);
}

std::string BST::getPreOrderTraversal(BST::Node *me) {
    if (me == nullptr) {
        return "";
    }
    return std::to_string(me->key) + " " + getPreOrderTraversal(me->left) +
    " " + getPreOrderTraversal(me->right);
}

std::string BST::getPostOrderTraversal() const {
    return getPostOrderTraversal(root);
}

std::string BST::getPostOrderTraversal(BST::Node *me) {
    if (me == nullptr) {
        return "";
    }
    return getPostOrderTraversal(me->left) + " " +
    getPostOrderTraversal(me->right) + " " + std::to_string(me->key);
}


#endif //P3_BST_BST_H
