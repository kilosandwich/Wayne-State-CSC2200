
//
// Lab_3:
// The startup code builds a binary tree where elements can be stored.
// The nodes can be displayed with inorder, preorder, and postorder algorithms.
//
// 
// Assignment:
// Using this startup code as a starting point:
// Implement a database program such an address book similar to our phone address book, i.e.:
// 1 - Accept simple entries as name, and phone number
// 2 - Store the address book entries in a form of Binary tree by inserting the entries, 
// you will have to modify the current implementaion to accept strings
// 3 - Adjust the entries and save the new info in the table (and eventually in the file) (simillar to lab_1)
//     Upon exit: Save tree info (will be be already sorted) in the phonebook file  
// 4 - Upon startup, load the stored phone info from the phonebook file
// 5 - Display phone numbers info in a sorted order, limit the entries to few < 10 
// 6 - Verify that you can insert, display, delete and update entries
// 6 - Your implementaion should behave very simillar to your phonebook
// 7 - Upload code along with your run test cases (report) to CANVAS
//



#include <iostream>

#include <string>
using namespace std;
//TO DO LIST AND PLAN:
//As is tradition, I am going to completely ignore the solution set provided and instead build my own. 
//the solution provided is too clunky to be understandable by me. I will learn by building.
//The new simpler plan: define a data node, define a tree class, and I'll figure it out from there
//This implimentation needs the following features:
//Insert new entries CHECK
//search for existing entries CHECK
//replace existing entries (delete and insert lmao) CHECK
//resort the tree (heap sort I totally forget) Check?
//delete existing entries CHECK
//display existing entries
//save info to a file (extra credit)
//load existing trees from a file (extra credit)



class node {
public:
	string data = "";
	node* left = nullptr;
	node* right = nullptr;
	node* up = nullptr; //never know, might need it.
	string side = "left"; //look there's a better way than this but this is easier to write. 

	node(string value) {
		data = value;//I forgot how to do the thingy
		//with the arrows I did last time. 
	}
	
};

class tree {
public:
	node* root = nullptr; //this will be replaced later

	void insert(string val) {
		//cout << endl << "attempting insert";
		//The insert function places the new data to the right if it is larger than the existing node.
		//and to the left if it is smaller. It iterates through the tree until a nullptr is found to the
		//destination of left or right, then places the node there.
		node* newNode = new node(val);
		node* tempNode = root;
		if (root == nullptr) {
			root = newNode;//replace the root if none exists
			newNode->up = nullptr;
		}
		else {
			//figure out where the information goes in the tree;
			while (tempNode) {
				//cout << endl << "Debugger: Help I am stuck";
				if ((newNode->data) < (tempNode->data)) {
					//make sure our destination actually exists before going there.
					if (tempNode->left) {
						tempNode = tempNode->left; //smaller data goes to left
					}
					else {
						//the next destination is blank! assign our new node there.
						tempNode->left = newNode;
						newNode->up = tempNode; 
						newNode->side = "left";
						break;
					}
				}
				else {
					if (tempNode->right) {
						tempNode = tempNode->right; //larger or equals goes to the right.
					}
					else {
						//the next destination is blank! assign our new node there.
						tempNode->right = newNode;
						newNode->up = tempNode;
						newNode->side = "right";
						break;
					}
				}
			}
		}
	}
	node* search(string val, node* searchHere = nullptr) {
		//the search function searches for a designated value. This is done by recursively searching the left and right sides of the tree
		//the memory address of the node with the value is then returned. The search does not occur to a side if that side is a nullptr
		//thus ensuring that the recursion terminates.
		node* tempNode;
		tempNode = searchHere;
		if (tempNode == nullptr) {
			//I forgot how to make data within the class a default value in the method. 
			tempNode = root;
		}
		if(tempNode){
			if ((tempNode->data) != val) {
				//check to make sure the destination exists before searching there. Otherwise will loop forever.
				if (tempNode->left) {
					tempNode = search(val, tempNode->left);
				}
				//value not found recursively that way? keep going to the right. This avoids the awkward situation
				//of the value being on the left, but being overwritten by the search on the right.
				if (tempNode->data != val) {
					if (tempNode->right) {
						tempNode = search(val, tempNode->right);
					}
				}
			}
		}
		return tempNode;
	}
	void swapper(node* node1, node* node2) {
		//The purpose of this internal use function is to swap the pointers of two nodess, while keeping the up pointer of the node above in place.
		node* upprime = node1->up;
		node* rightprime = node1->right;
		node* leftprime = node1->left;
		string sideprime = node1->side;

		//change the desinations of the node above.
		if (node1->side == "left") {
			//check what the node above it is, so we know which destination to change. 
			upprime->left = node2;
		}
		else {
			upprime->right = node2;
		}

		//swap the left and left
		node1->left = node2->left;
		node2->left = leftprime;

		//swap the right and right
		node1->right = node2->right;
		node2->right = rightprime;

		//swap the side designations;
		node1->side = node2->side;
		node2->side = sideprime;

		//swap the up designations
		node1->up = node2; //node 2 is now above node1
		node2->up = upprime; //node 2's up is now node1's previous up.


	}
	/* This was causing some sort of error. I don't know why. Weird. 
	void sortTree(node* sortHere = nullptr) {
		//This function will sort the tree, somehow, I'll figure it out one sec.
		node* tempNode = nullptr;
		if (sortHere == nullptr) {
			//If no value is given, start at the beginning.
			tempNode = root;
		}
		//if the left node is larger than the node above it, they need to swap places. 
		if (tempNode) {
			if (tempNode->left) {
				if (tempNode->left->data > tempNode->data) {
					swapper(tempNode, tempNode->left);
					tempNode->side = "left"; //because the node has swapped place with the left side, it is now a 'left' node. 

				}
			}
			if (tempNode->right) {
				if (tempNode->right->data < tempNode->data) {
					swapper(tempNode, tempNode->right);
					tempNode->side = "right";
				}
			}
		}
	}

	*/

		//OK, now the stuff is pointing to the right place, time to do it recursively.
	
	void deleteandinsert(node* deletehere) {
		//copy all the data from the node, then reinsert it as part of a new node
		string temp = deletehere->data;
		//check to make sure that the recursion can continue.
		if (deletehere->left) {
			deleteandinsert(deletehere->left);
		}
		if (deletehere->right) {
			deleteandinsert(deletehere->right);
		}

		//change the desinations of the node above.
		if (deletehere->side == "left") {
			//check what the node above it is, so we know which destination to change. 
			deletehere->up->left = nullptr;
		}
		else {
			deletehere->up->right = nullptr;
		}

		delete deletehere;
		insert(temp); //shove it back in.


	}
	void remove(string val) {
		//Note: the convention is to promote the right child. 
		//NOTE: this requires the child to have less than 2 children. That sounds annoying to look for. 
		//Solution: delete every child then stick it back into the tree and it sorts itself out. GENIUS
		node* target = search(val, root); //find the target
		//change the desinations of the node above.
		if (target->side == "left") {
			//check what the node above it is, so we know which destination to change. 
			target->up->left = nullptr;
		}
		else {
			target->up->right = nullptr;
		}

		if (target->left) {
			deleteandinsert(target->left);
		}
		if (target->right) {
			deleteandinsert(target->right);
		}

		delete target;
	}

	void replace(string target, string replacement) {
		//You don't have to replace values if you simply delete it and put something new in.
		//Look, theoretically if each piece of data held more than a string, this could be done for each piece of 
		//data here. 
		remove(target);
		insert(replacement);
	}

	void display(node* currentNode = nullptr) {
		//cout << "Debugger: Attempting display";
		if (currentNode == nullptr) {
			currentNode = root;
		}

		//display all smaller values first
		//check to make sure they exist first to ensure recursion. 
		if (currentNode->left) {
			display(currentNode->left);
		}
		//display the current node
		cout << endl<< currentNode->data << ", ";

		//display all larger values
		if (currentNode->right) {
			display(currentNode->right);
		}
	}





};

int main()
{
	cout << "Displaying:" << endl;
	tree tree1;
	tree1.insert("Alphabet, Alphonse, 111-111-1111");
	tree1.insert("Braverman, Bradley, 222-222-2222");
	tree1.insert("Capricorn, Cole, 333-333-3333");
	tree1.insert("Dangerous, Dudley, 444-444-4444");
	tree1.insert("Elephant, Edward, 555-555-5555");
	tree1.insert("Flamingo, Florence, 666-666-6666");
	tree1.insert("Gem, Greg, 777-777-7777");
	tree1.insert("Alphabet2, Alphonse2, 111-111-1111");
	tree1.display();

	cout << endl << endl<< "Removing Braverman:";
	tree1.remove("Braverman, Bradley, 222-222-2222");
	tree1.display();

	cout << endl << endl << "Replacing Cole Capricorn";
	tree1.replace("Capricorn, Cole, 333 - 333 - 3333", "Continental, Calvin, 313-313-3133");
	tree1.display();




	return 0;

}