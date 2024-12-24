

//
// Lab_3:
//
// Objective: Experiment with Lists, Stacks, and Queues:
//            Simulate an OS task manager
//
// Assignment:
// Using the startup code, implement the following:
// 1-Create List L1 of 10 elements (task IDs), e.g. L1 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10; 
// 
// 2-Insert a new list element in between (at every other element), such as:  1,100, 2,200, 3,300, 4,400, ... 10,1000;
// Simulate a new CPU core assignment:
// 
// 3-Create another List L2, and extract the newly inserted elements into this new list L2 
// i.e. L1 should go back to the original list: L1 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 
// L2 should be: 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000
// 
// // Start executing:
// 4-Create a Queue Q1 by extracting L1, and inserting L2 elements: i.e. Q should start with: 1,2,3, ... 10, and (10, 20 ... 100) will be inserted 
// Q1=1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000
// 
// Label tasks as finished with the possibility of revisiting a task, such as:
// 5-Create a Stack S1 which by deleting the elements of Q1 and inserting them in L1 
// 
// 6-Pop out all elements of the Stack, i.e. should end up with an empty stack
// 
// Extra credit: Simulate a re-executed task, i.e. Pop out a task out of the Stack and reinsert, this simulate a failed task.
//
// 7-Verify the functionality and capture the results in a report form.
//




#include "List.h"
#include <stdlib.h>
#include <iostream>
#include <string>


using namespace std;

//Why deal with lists, queues, and stacks? Why not just have a massive single class handle everything
class Node {
    public:
        //put my data here instead
        int data;
        //address variable of the next node
        Node* next;
        Node* prev;
        //this is from a template, realistically we could have left next as a nullptr by default.
        Node(int data) {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

//this single monstrosity will handle everything, lists stacks and queues, just functionality.
class Chimera {
    public:
        Node* head;
        string functionality = "queue"; 
        string name = "";
        Chimera() {
            head = nullptr;
        }
        Chimera(string name) {
            head = nullptr;
            this->name = name;
        }

        void insert(int data) {
            //create a new node based on what is plugged into the insert function.
            //if you want to insert additional data into the node, do it here.
            Node* newNode = new Node(data);
            if(head == nullptr){
                head = newNode;
            }
            else if(functionality == "queue"){
                //because this is a queue, new information is attached to the END
                Node* NodeIterator = head;
                //iterate to the end. (where the next is nullptr
                while ((NodeIterator->next) != nullptr) {
                    NodeIterator = NodeIterator->next;
                }
                //assign the new node to the end
                NodeIterator->next = newNode;
                newNode->prev = NodeIterator; //now it's doubly linked!

            }
            else if (functionality == "stack") {
                //because this is a stack, new information is inserted at the top
                //this means that the head needs to be replaced,
                Node* temphead = head; //store the old head's location
                head = newNode; //put the new node at the top
                newNode->next = temphead; //assign the old head to just below the newNode.
                temphead->prev = newNode; //the old head's previous value is the previous. 
            }
        }
        //this determines the functionality of the chimera.
        void setMode(string functionality) {
            this->functionality = functionality; //the functionality is set by user input. 
            //don't mess it up
        }

        void display() {
            Node* NodeIterator = head;
            //while NodeIterator exists, display its data, then iterate to the next Node
            cout << endl;
            cout << "Displaying Chimera: " << name << " type: " << functionality << endl;
            while (NodeIterator) {
                cout << NodeIterator->data << " ";
                NodeIterator = NodeIterator->next;
            }
        }

        //this function is for filling up the list with elements because I am way too lazy to do it
        //manually - and I HATE including the sizeof in function inputs.
        void insertLinear(int num) {
            for (int i = 1; i < (num + 1); i++) {
                insert(i);
            }
        }

        void insertEveryOther() {
            //2-Insert a new list element in between
            // (at every other element), such as:  1,100, 2,200, 3,300, 4,400, ... 10,1000;
            //This is stupid, so I created a dedicated function for it.
            cout << endl;
            Node* NodeIterator = head;

            //while NodeIterator exists, display its data, then iterate to the next Node
            while (NodeIterator) {
                Node* currentNode = NodeIterator;
                Node* newNode = new Node((NodeIterator->data) * 100); //new information to be inserted. 

                newNode->next = currentNode->next; //the new node is assigned the next of the old node
                currentNode->next = newNode; //the original node is assigned the new node

                NodeIterator = newNode->next; //nodeIterator remains unchanged, and advances onwards
            }

        }

        //this function just inserts an entire list. 
        void insertList(Chimera copyThisList) {
            //yes I am aware my capitalization sucks and doesn't follow format, but
            //this is a temporary variable and it works. 
            Node* NodeIterator = copyThisList.head;
            while (NodeIterator) {
                insert(NodeIterator->data);
                NodeIterator = NodeIterator->next;
            }
        }

        void extract(Chimera& copyThisList) {
            //this contraption copies a list, while simultaneously deleting it. 
            Node* nodeIterator = copyThisList.head;
            while (nodeIterator) {
                insert(nodeIterator->data);
                if (nodeIterator->prev && nodeIterator->next) {
                    nodeIterator->next->prev = nodeIterator->prev->next;
                    //gotta admit I'm not sure how this works, I drew a diagram then forgot it. 
                    //seems like it works though!
                }
                else {
                    copyThisList.head = nodeIterator->next;
                }

                nodeIterator = nodeIterator->next;
            }
        }


        void extractEveryOther(Chimera& copyThisList) {
            //whoops forgot to passs by reference
            Node* NodeIterator = copyThisList.head;
            string progress = "every"; //yeah I'm using a string as a janky enum.
            Node* previousNode = nullptr; //we need this because my target functions aren't working 
            while (NodeIterator) {
                if (progress == "other") {
                    insert(NodeIterator->data);
                    if (previousNode) {
                        previousNode->next = NodeIterator->next;
                    }
                    else {
                        //have to update the head as well
                        copyThisList.head = NodeIterator->next;
                    }
                }

                previousNode = NodeIterator;
                NodeIterator = NodeIterator->next;

                if (progress == "every") {
                    progress = "other";
                }
                else {
                    progress = "every";
                }
                /*
                if (progress == "other") {
                    //it literally is defined
                    copyThisList.deleteTarget(nodeIteratorCopy->data);
                }
                */
            }

        }
        void pop() {
            //this removes the head of the stack and replaces the head with
            //the next in line at the top of the stack
            head = head->next;
            //yeah I don't know how to delete objects, but this simulates a pop.
        }

        void popUntilEmpty() {
            while (head) {
                pop();
            }
        }




};
int main(){
    Chimera L1("L1");
    //1- Create L1 List of 10 elements 1-10.
    L1.insertLinear(10);
    L1.display();
    // 2-Insert a new list element in between (at every other element),
    //  such as:  1,100, 2,200, 3,300, 4,400, ... 10,1000;
    L1.insertEveryOther();
    L1.display();
    // 3-Create another List L2, and extract the newly inserted elements into this new list L2 
    // i.e. L1 should go back to the original list: L1 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 
    // L2 should be: 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000
    Chimera L2("L2");
    L2.extractEveryOther(L1);
    L1.display();
    L2.display();
    // 4 - Create a Queue Q1 by extracting L1, and inserting L2 elements 
    // : i.e.Q should start with : 1, 2, 3, ... 10, and (10, 20 ... 100)
    //  will be inserted
    // Q1=1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000
    Chimera Q1("Q1");//this is a queue
    Q1.extract(L1);
    Q1.insertList(L2);
    Q1.display();
    L1.display();

    // 5-Create a Stack S1 which by deleting the
    //  elements of Q1 and inserting them in L1 
    //I am going to assume you meant S1, as inserting them into L1 makes no sense. 
    Chimera S1("S1");
    S1.setMode("stack");
    S1.extract(Q1);
    S1.display();

    // 6-Pop out all elements of the Stack,
    //  i.e. should end up with an empty stack
    S1.popUntilEmpty();
    S1.display();

    // Extra credit: Simulate a re-executed task, i.e. 
// Pop out a task out of the Stack and reinsert,
//  this simulate a failed task.
    int failedTask = 1337;
    S1.insert(failedTask);
    S1.display();
    S1.pop();
    S1.display();
    S1.insert(failedTask);
    S1.display();
    return 0;
}


/*
* template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& top() const
    {
        return theList.front();
    }
    void push(const Object& x)
    {
        theList.push_front(x);
    }
    void pop(Object& x)
    {
        x = theList.front(); theList.pop_front();
    }
private:
    List<Object> theList;
};


template <typename Object>
class Queue
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& getFront() const
    {
        return theList.front();
    }
    void enqueue(const Object& x)
    {
        theList.push_back(x);
    }
    void dequeue(Object& x)
    {
        x = theList.front(); theList.pop_front();
    }
private:
    List<Object> theList;
};





int main()
{

    int i;
 
    const int N = 10;

    List<int>  L1;
    Stack<int> S1;
    Queue<int> Q1;

    List<int>::iterator node; //Variable to keep track of the position as we traverse

    // List Section example:
    //Q1: Create List L1 of 10 elements, e.g. L1 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    // create the list array as a starting point:
    for (i = N; i > 0; --i)
    {
        L1.push_front(i);
    }

  
    // show L1 with an iterator
    cout << "List L1 is:" << endl;
    for (auto it = L1.begin(); it != L1.end(); ++it)
    {
        cout << *it << ' ';
    }


	// Stack Section example:
    // 
    // Stack to be created per the above assignment requirment
    cout << "\nStack S1 is:" << endl;;
    for (i = N - 1; i >= 0; --i)
    {
        S1.push(i);
        cout << S1.top() << " " << endl;
    }

 
    while (!S1.isEmpty())
    {
        cout << S1.top() << endl;
        S1.pop(i);
    }




    // Queue section, to be created per the above assignment requirment
    //
    //
     

    return 0;
}
*/