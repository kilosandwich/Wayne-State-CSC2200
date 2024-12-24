

// 
//Lab_8
//
//  Engineering Application: Real-Time Task Scheduling
//
//  In a real-time systems, tasks often have different priorities and deadlines.
//  Leftist trees can be employed to maintain a dynamic priority queue of tasks, 
//  allowing efficient insertion, deletion of the highest - priority task, and merging of task queues.
//
// Current implementaion: Leftist Heap with the following operations:
//  1- Insert Keys: Insert the following keys into tree1 :
//  2- deleteMin: Delete the minimum key from the Leftist Heap.
//  3- mergeWith: Merge the current heap with another Leftist Heap.
//  4- printLeftistOrder: Print the Leftist Heap in a leftist order(pre-order) traversal.
//
// Assignmnet:
//  Implement a real-time task scheduler using the Leftist Tree data structure. 
//  The scheduler should support the insertion of tasks with different priorities, execution of the highest-priority task, and merging of task queues.
//
// Task Representation (modify the existing code as needed):
//  Each task should be represented as a node in the Leftist Tree.
//  The key of each node represents the priority of the task.
//
// Dynamic Priority Queue Operations :
//  Use the insert method to add tasks with varying priorities to the scheduler.
//  Use the deleteMin method to execute and remove the highest - priority task.
//  Use the mergeWith method to combine two task queues efficiently.
//
// Task Information :
//  Each task should have additional information, such as a task identifier and estimated execution time.
//  Tasks can be represented by a class or a struct with these attributes.
//
// Simple User Interface :
// Create a simple user interface to interact with the task scheduler:
//  Allow users to add tasks with priorities, execute the highest - priority task, and view the current task queue.
//
// Implement a testing framework to validate the correctness of your task scheduler implementation.

// Extra credit:
//  Evaluate the performance of the scheduler by measuring the time complexity of key operations(insertion, deletion, merging) for varying numbers of tasks.
//
// Upload your updated code and test results to CANVAS
//

//first thing is first, trying to untanble what theis code actually says ONCE IT STOPS LAGGING AND LETS ME USE VISUAL STUDIO CODE
//let's break down the assignment, back to front:
//Create a user interface that allows users to add tasks with priorities
//user interface must also executie the highest priority task
//user interface must also allow one to view the current task order

//tasks need to be included in the tree, tasks must include:
//task idenfitier (string)
//estimated completion time

//also allow merging of task queues I guess



#include <iostream>
#include <string>
using namespace std;

//first thing's first, the smallest number is at the top on this tree. 
class LeftistTree {
private:
    //wait what you can define classes WITHIN a class? That's wild.
    //Good new Node class, you have been drafted as a TASK, that's right, all nodes are now tasks.
    class Node {
    public:
        int key; //this is priority.
        int npl; //what the heck is this I NEED TO FIND OUT (nah I guess I don't)
        Node* left;//left node it is pointing too
        Node* right;//right node it is pointing to

        string taskname = "";
        int estimatedCompletionTime = 0; //time measured in milliseconds, I don't want to think too hard about this.


        Node(int k) : key(k), npl(0), left(nullptr), right(nullptr) {}

        //create a new constructor for stuffing tasks into the system. We can think of how it works later. 
        Node(int k, string s, int e) {
            key = k;
            npl = 0;
            left = nullptr;
            right = nullptr;
            taskname = s;
            estimatedCompletionTime = e;

        }
    };

    Node* root;

    // Function to swap two nodes
    //swap function swaps memory address of two nodes. Nothing wrong with that, makes sense
    void customSwap(Node*& a, Node*& b) {
        Node* temp = a;
        a = b;
        b = temp;
    }

    // Function to merge two leftist trees
    //looks like this is a recursive function. ugg.
    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2; //no h1? Just h2 it is boss
        if (!h2) return h1; //no h2? just h1 it is

        //if h1's priority is greater than h2's priority, h2's priority is placed placed ahead
        if (h1->key > h2->key) {
            customSwap(h1, h2);
        }
        //h1's right node is now merged with h2
        h1->right = merge(h1->right, h2);

        if (!h1->left || h1->left->npl < h1->right->npl) {
            customSwap(h1->left, h1->right);
        }

        h1->npl = (h1->right ? h1->right->npl + 1 : 0);

        return h1;
    }

    // Function to print the tree in leftist order (pre-order)
    //as you can see, we jammed in things like task name yayyyyy.
    void printLeftistOrder(Node* node) {
        if (node) {
            cout << "Key: " << node->key << ", NPL: " << node->npl << ", Task Name: " << node->taskname << ", Estimated Completion Time:  " << node->estimatedCompletionTime;
            //print the nodes of the left and right of this node, then do it again
            if (node->left) {
                cout << ", Left NPL: " << node->left->npl << ", Task Name: " << node->left->taskname << ", Estimated Completion Time:  " << node->left->estimatedCompletionTime;
            }
            if (node->right) {
                cout << ", Right NPL: " << node->right->npl << ", Task Name: " << node->right->taskname << ", Estimated Completion Time:  " << node->right->estimatedCompletionTime;
            }
            cout << endl;

            printLeftistOrder(node->left);
            printLeftistOrder(node->right);
        }
    }

public:
    LeftistTree() : root(nullptr) {}

    // Insert a new key into the leftist tree
    void insert(int key) {
        Node* new_node = new Node(key);
        root = merge(root, new_node);
    }
    //This function is a copy of the insert function, except this time it has a task name and estimated completion time. 
    void insert(int key, string n, int e) {
        Node* new_node = new Node(key, n,e);
        root = merge(root, new_node);
    }

    // Delete the minimum key from the tree and return it
    int deleteMin() {
        if (!root) {
            cout << "Tree is empty. Cannot delete minimum." << endl;
            return -1; // Return a default value or handle the case as needed
        }

        int minKey = root->key;

        Node* left_subtree = root->left;
        Node* right_subtree = root->right;

        delete root;
        //sew it all back together, (I still don't get how that merge function works)
        root = merge(left_subtree, right_subtree);

        return minKey;
    }

    // Merge the current tree with another tree
    void mergeWith(LeftistTree& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    // Check if the tree is empty
    bool isEmpty() {
        return !root;
    }

    // Print the tree in leftist order (pre-order)
    void printLeftistOrder() {
        printLeftistOrder(root);
    }

    void menu() {
        int selection = 0;
        bool runmenu = true;
        while (runmenu) {
            cout << endl << "Welcome to Task Manager - Please select an option below" << endl
                << "1: Execute Highest Priority Task" << endl
                << "2: Add New Task" << endl
                << "3: View Current Task Order" << endl
                << "4: Exit Program" << endl;
            cout << endl << "Selection: ";
            cin >> selection;


            string tempname;
            int temppriority;
            int tempeta;
            switch (selection) {
                case 1:
                    cout << endl << "Executing Highest Priority Task";
                    deleteMin();
                    break;
                case 2:


                    cout << endl << "Please Enter The Name of your new Task: ";
                    cin >> tempname;
                    cout << endl << "Please Enter The priority of your new task: ";
                    cin >> temppriority;
                    cout << endl << "Please enter the estimated completion time of your new task: ";
                    cin >> tempeta;
                    insert(temppriority, tempname, tempeta);

                    break;
                case 3:
                    cout << endl << "Printing Current Task Order:";
                    cout << endl;
                    printLeftistOrder();
                    break;
                case 4:
                    runmenu = false;
                    break;
                default:
                    break;
            }
        }



    }
};
//looks like this works as is. GREAT. Just need to build something with the leftist queue then. 
int main() {
    LeftistTree tree1;
    LeftistTree tree2;

    tree1.insert(5, "Potato", 2000);
    tree1.insert(10, "Lower Priority Potato", 6000);
    tree1.insert(12, "Lowest Priority Potato", 90000000);

    tree2.insert(3);
    tree2.insert(7);
    tree2.insert(8);
    tree2.insert(14);

    cout << endl << "tree1" << endl;
    tree1.printLeftistOrder();

    cout << endl << "tree2" << endl;
    tree2.printLeftistOrder();

    tree2.mergeWith(tree1);

    cout << "\nMerged tree in leftist order:" << endl;
    tree2.printLeftistOrder();

    cout << "\nMerged tree after deleting the minimum key (" << tree2.deleteMin() << "):" << endl;
    tree2.printLeftistOrder();

    cout << "\nMerged tree after deleting the minimum key (" << tree2.deleteMin() << "):" << endl;
    tree2.printLeftistOrder();

    cout << "\nMerged tree after deleting the minimum key (" << tree2.deleteMin() << "):" << endl;
    tree2.printLeftistOrder();

    tree1.menu();


    return 0;
}
