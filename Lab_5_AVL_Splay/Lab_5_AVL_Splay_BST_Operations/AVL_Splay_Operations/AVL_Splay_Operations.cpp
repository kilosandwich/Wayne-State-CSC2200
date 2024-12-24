
//These are the lab instructions, ok, looks like it's already provided
// Just gotta comment the code to actually figure out how the heck it works
// Lab_5 AVL-SPLAY Tree:
// 
// Sample implementation of AVL & Splay tree is provided
// The provided code mainly implements the insert, and the rotation:
// 
// Assignment:
// Run the supplied code in your visual studio IDE
// In addition to insertion and traversal (already provided), implement the following operations:
// 
// 
// This is it, add nothing else:
// 1-search
// 2_delete
// 3-findMin and findMax
// 4-isPresent
// Generate a dataset of integers for testing tree operations. The dataset should include various scenarios, such as sorted, reverse-sorted, and random data.
// Create funny data set generators
// Actually display them
// 
// Extra credit:
// Measure and record the time taken for insertion, search, and deletion operations on both AVL and Splay trees for each dataset scenario.
// Compare the performance of AVL vs. Splay Trees (Express your own opinion based on your data)
// Analyze and compare the performance of AVL and Splay trees based on your measurements.
// Create visualizations (e.g., graphs or charts) to illustrate the differences in performance.
// Discuss the possibility of optimizing the Splay tree splaying strategy or implement AVL tree balancing in a more efficient way.
//


#include <iostream>
#include <algorithm> // for max and min
#include <random> //for the random data set
#include <ctime> //for random number generator
#include <string>

using namespace std;

// Splay tree:
class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* up;
        string side = "";
        int height;
        //bruh gonna be honest, no clue why you keep using structures. 
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; //this is where the tree starts, so start your temp functions here. 

    int getHeight(Node* node) {
        return (node) ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    //bruh why does this return a node, that's silly, it's going IN. 
    //oh because it recursively inserts something at the keypoint node, NEAT. 
    //this allows it to be reused when you're deleting something. 
    Node* insert(Node* node, int key) {
        //this function inserts a key key into the tree at point node, if there is no node, then a new one is created with the key in it. 
        if (!node)
            return new Node(key);

        //if the key to be inserted is less than the Node to be in then insert to the left.
        if (key < node->key) {
            //the value of the left side of the node is reassigned, 
            node->left = insert(node->left, key);
            node->left->up = node;
            node->left->side = "left";


            //if the key to be inserted is greater than the node, then it is inserted to the right.
        }
        else if (key > node->key){
            node->right = insert(node->right, key);
            node->right->up = node;
            node->right->side = "right";
        }else{
            return node; // Duplicate keys not allowed 
        }
        //determine the node height. 
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));



        //balancing function bit THIS SHOULD HAVE BEEN A SEPARATE FUNCTION AND IT IS CONFUSING THAT IT ISN'T
        //calculate the balance of the tree. 
        int balance = getBalanceFactor(node);

        //how do I chop off this and make it into a balancing function so I don't have to think too hard. 
        // Left Heavy
        if (balance > 1) {
            if (key < node->left->key) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        // Right Heavy
        if (balance < -1) {
            if (key > node->right->key) {
                return rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node; //function was not returned, rotation successful, return node of attempted insertion
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    // Add more operations such as: search, delete, findMin, findMax:
   //THIS IS WHERE THE WORK GOES
    //DO THE WORK HERE

    Node* search(int valuetosearchfor, Node* searchNode) {
        Node* tempanswer = nullptr;
        if (searchNode == nullptr) {
            Node* tempnode = root; //start at the root of the tree.
        }

        if (searchNode->key == valuetosearchfor) {
            //return the value of the found location, this is important I assume. 
            return searchNode;
        }


        //recursively search through all remaining nodes because the key has NOT been found. 
        //if the left node exists, search down it. 
        if (searchNode->left) {
            tempanswer = search(valuetosearchfor, searchNode->left);
        }

        //if the right node exists, search down it
        //make sure you haven't found the answer first though. 
        if (searchNode->right and (tempanswer == nullptr)) {
            search(valuetosearchfor, searchNode->right);
        }
        //failed? Return nullptr so everyone knows how much of a failure you are. 
        return tempanswer;

    }

    //use this methods for actually deleting things. 
    void deleteThis(int valuetodelete) {
        root = deleteNode(root, valuetodelete);
    }

    //this method is for recursively deleting. For internal use only. 
    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            // Node with the key to delete found.

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: get the inorder successor (smallest in the right subtree)
            Node* temp = findMinNode(node->right);

            // Copy the inorder successor's content to this node
            node->key = temp->key;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->key);
        }

        return node;
    }

    //internal method for deleting stuff
    Node* findMinNode(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    //by the nature of tree, the bigger thing is on the right, and cannot be on the left, and the smaller thing is on the left, and cannot be on the right.
    Node* findMax() {
        Node* temp = root;
        while (temp->right) {
            temp = temp->right;
        }

        cout << " The maximum is: " << temp->key;
        return temp;
    }

    Node* findMin() {
        Node* temp = root;
        while (temp->left) {
            temp = temp->left;
        }

        cout << " The maximum is: " << temp->key;
        return temp;
    }

    //it's just the search method, but it checks if it's not a nullptr. 
    bool isPresent(int valuetofind) {
        return search(valuetofind, nullptr) != nullptr;

    }


    // Destructor to free memory (not optimal)
    ~AVLTree() {
        destroyTree(root);
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};


// Splay tree:
class SplayTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* splay(int key, Node* node) {
        if (!node) return nullptr;

        if (key < node->key) {
            if (!node->left) return node;
            if (key < node->left->key) {
                node->left->left = splay(key, node->left->left);
                node = rotateRight(node);
            }
            else if (key > node->left->key) {
                node->left->right = splay(key, node->left->right);
                if (node->left->right)
                    node->left = rotateLeft(node->left);
            }

            return (node->left) ? rotateRight(node) : node;
        }
        else if (key > node->key) {
            if (!node->right) return node;
            if (key < node->right->key) {
                node->right->left = splay(key, node->right->left);
                if (node->right->left)
                    node->right = rotateRight(node->right);
            }
            else if (key > node->right->key) {
                node->right->right = splay(key, node->right->right);
                node = rotateLeft(node);
            }

            return (node->right) ? rotateLeft(node) : node;
        }
        else {
            return node;
        }
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    Node* search(int key, Node* node) {
        //is the current node the key? Probably not
        if (!node || node->key == key) {
            return splay(key, node);
        }

        //check down the leg of the tree to the left. 
        if (key < node->key) {
            if (!node->left) {
                return splay(key, node);
            }
            return search(key, node->left);
        }

        //check down the leg of the tree to the right. 
        else {
            if (!node->right) {
                return splay(key, node);
            }
            return search(key, node->right);
        }
    }

    //min of a splay tree is always on the left. REMEMBER THIS IS NOT
    //A BINARY HEAP THING WHERE THE MINIMUM IS AT THE ROOT. 
    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        root = splay(node->key, root);
        return node;
    }

    //max of a splay tree is always on the right. 
    Node* findMax(Node* node) {
        while (node && node->right) {
            node = node->right;
        }
        root = splay(node->key, root);
        return node;
    }

    //deleteNode function, takes key input, and node starting point. 
    Node* deleteNode(int key, Node* node) {
        if (!node) return nullptr;

        root = splay(key, root);

        if (root->key != key) {
            return root; // Key not found, return the current root.
        }

        Node* leftSubtree = root->left;
        Node* rightSubtree = root->right;

        delete root; // Delete the current root.

        //annoying reorganization.
        if (!leftSubtree) {
            root = rightSubtree;
        }
        else {
            root = splay(key, leftSubtree);
            root->right = rightSubtree;
        }

        return root;
    }



public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        root = splay(key, root);
        if (!root || root->key != key) {
            Node* newNode = new Node(key);
            if (!root) {
                root = newNode;
            }
            else if (key < root->key) {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullptr;
                root = newNode;
            }
            else {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullptr;
                root = newNode;
            }
        }
    }

    // Add more operations such as: search, delete, findMin, findMax:
    //THIS IS WHERE YOU ARE SUPPOSED TO DO STUFF RIGHT HERE BOSS
    //I AM ADDING MORE COMMENTS SO I DIRECT MY EYES TO THIS
    // 121212121212121 HERE 1212121212121212

    //ease of use functions for complicated nonsense functions 
    Node* search(int key) {
        return search(key, root);
    }

    void deleteNode(int key) {
        root = deleteNode(key, root);
    }

    Node* findMin() {
        return findMin(root);
    }

    Node* findMax() {
        return findMax(root);
    }




    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    // Destructor to free memory (not optimal)
    ~SplayTree() {
        destroyTree(root);
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};




int main() 
{
    // AVL tree and a Splay tree
    AVLTree   avlTree;
    SplayTree splayTree;
    int const arraysizething = 100; //this will be for the size of arrays for ordered data, reverse ordered data, and random data. 

    // Insert some values into the AVL tree
    int Keys[] = { 50, 30, 70, 20, 40, 60, 80 };

    //I don't get this kinda insertion, but I'm going to copy this format. 
    for (int key : Keys) {
        avlTree.insert(key);
        splayTree.insert(key);
    }
    //USE THE ABOVE THING FOR TEST CASES.

    //ordered keys generator
    int Keys1[arraysizething];
    AVLTree   avlTree1;
    SplayTree splayTree1;
    //ordered data
    for (int i = 0; i < arraysizething; i++) {
        Keys1[i] = i + 1;
    }
    for (int key : Keys1) {
        avlTree1.insert(key);
        splayTree1.insert(key);
    }
    
    // Display AVL tree
    cout << "Inorder traversal of the AVL tree: ";
    avlTree1.inorder();

    // Display Splay tree
    cout << "Inorder traversal of the Splay tree: ";
    splayTree1.inorder();

    

    //reverse ordered keys generator
    AVLTree   avlTree2;
    SplayTree splayTree2;
    int Keys2[arraysizething];
    //ordered data
    for (int i = (arraysizething-1); i >= 0; i--) {
        Keys2[i] = i +1;
    }

    for (int key : Keys2) {
        avlTree2.insert(key);
        splayTree2.insert(key);
    }
    // Display AVL tree
    cout << "Inorder traversal of the AVL tree: ";
    avlTree2.inorder();

    // Display Splay tree
    cout << "Inorder traversal of the Splay tree: ";
    splayTree2.inorder();

    //random order key generator
    AVLTree   avlTree3;
    SplayTree splayTree3;
    int Keys3[arraysizething];
    //ordered data
    srand(static_cast<unsigned int>(time(nullptr))); //initial random number generator

    for (int i = 0; i < arraysizething; i++) {
        Keys3[i] = rand() % 100; //generate a random number between 0 and 100
    }

    for (int key : Keys3) {
        avlTree3.insert(key);
        splayTree3.insert(key);
    }



    // Display AVL tree
    cout << "Inorder traversal of the AVL tree: ";
    avlTree3.inorder();

    // Display Splay tree
    cout << "Inorder traversal of the Splay tree: ";
    splayTree3.inorder();

    return 0;
}
