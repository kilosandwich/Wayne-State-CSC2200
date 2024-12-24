
//
// Lab 6: 
// In this lab, we utilize the hashing methods with probing: Linear, Quadratic, double and open chaining probing.
// Simple hash function will be used: hashCode = x % SIZE

// Assignment:
// 1- Run the supplied code in your visual studio IDE
// 2- Add few more probing methods similar to the linear probing as described below 


// Already implemented:
// Linearhashing Probing and open chaining
//
// Implement the following probing methods:
// 1-Quadrating Hashing
// 2-Double Hashing
// 3-Cubic Hashing

// Each hashing method should have the following features (at least)
// 1- Insert
// 2- Remove
// 3- Find
// 4- Display

// Extra credit:
// 1-Add the load factor
// 
// Extra extra credit:
// Use the load factor to perform a re-hashing
// -Is cubic probing any better than quadratic?
// -Study of clustering induced by each method
// 
// Create a report highlighting the above topics featuring your run data.
//

//could you commment your code more? I spend more time understanding your code instead of building my own
//I built the load factor into the display function
#include <iostream>
#include <list>
using namespace std;


const int TABLE_SIZE = 19;  // The size of the hash table

// Hash functions (simple modulo-based hash) ALREADY DONE
int linearHash(int key) {
    return key % TABLE_SIZE;
}

int quadraticHash(int key) {
    return (key * key) % TABLE_SIZE;
}

// doubleHash functions (simple modulo-based hash)
int doubleHash(int key) {
    return (key * 2) % TABLE_SIZE;
}

//cubic hash functions
//In the future please let it be clear that this is missing. 
int cubicHash(int key) {
    return (key * key * key) % TABLE_SIZE;
}
    



class LinearProbingHashTable {
private:
    int table[TABLE_SIZE];

public:
    LinearProbingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    void insert(int key) {
        int index = linearHash(key);
        //while the table is NOT empty (i.e. collision) 
        //perform a linear probe
        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;  // Linear probing
        }
        table[index] = key; //unoccupied location found, insert the key
    }

    bool find(int key) {
        //check the starting location for this particular hash
        int index = linearHash(key);
        //while the space is occupied, continue to check
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % TABLE_SIZE;  // Linear probing THIS MEANS IT CONTINUES TO CHECK LINEARLY.
        }

        return false;
    }

    bool remove(int key) {
        //check the starting location for this particular hash
        int index = linearHash(key);
        //while the space is not unoccupied, continue to check
        while (table[index] != -1) {
            //the key has been found, replace it with a blank
            if (table[index] == key) {
                table[index] = -1;
                return true; //object removed, return your success
            }
            //location was occupied, use probing to get to the next one. 
            index = (index + 1) % TABLE_SIZE;  // Linear probing
        }
        //object not found because an unoccupied spot was identified.
        //object not found because an unoccupied spot was identified.
        return false;
    }


    void display() {
        //Make sure to change the name for table being displayed
        cout << "\nLinear Probing Hash Table:" << endl;
        double count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                count++;
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                //state that it is empty
                cout << "[" << i << "] Empty" << endl;
            }
        }
        double load = count / TABLE_SIZE;
        cout << "\n LOAD FACTOR: " << load;

    }

};




class OpenChainingHashTable {
private:
    list<int> table[TABLE_SIZE];

public:
    void insert(int key) {
        int index = linearHash(key);    // We can use any hash function, we are using the linear one to test
        table[index].push_back(key);    // Open chaining with linked lists
    }

    bool find(int key) {
        int index = linearHash(key); // You can use the same hash function here
        for (const int& value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = linearHash(key); // We can use the same hash function here
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\nOpen Chaining Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] ";
            for (const int& value : table[i]) {
                cout << value << " -> ";
            }
            cout << "nullptr" << endl;
        }
    }
};

//make quadratic, cubic, double hash table classes

class QuadraticProbingHashTable {
private:
    int table[TABLE_SIZE];

public:
    QuadraticProbingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    void insert(int key) {
        int index = quadraticHash(key);
        //while the table is NOT empty (i.e. collision) 
        //perform a QUADRATIC probe
        int i = 0;
        while (table[index] != -1) {
            i++;
            index = (index + i*i) % TABLE_SIZE;  // Linear probing
        }
        table[index] = key; //unoccupied location found, insert the key
    }

    bool find(int key) {
        //check the starting location for this particular hash
        int index = quadraticHash(key);
        //while the space is occupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            if (table[index] == key) {
                return true;
            }
            index = (index + i*i) % TABLE_SIZE;  // Linear probing THIS MEANS IT CONTINUES TO CHECK LINEARLY.
        }

        return false;
    }

    bool remove(int key) {
        //check the starting location for this particular hash
        int index = quadraticHash(key);
        //while the space is not unoccupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            //the key has been found, replace it with a blank
            if (table[index] == key) {
                table[index] = -1;
                return true; //object removed, return your success
            }
            //location was occupied, use probing to get to the next one. 
            index = (index + i*i) % TABLE_SIZE;  // QUADRATIC probing
        }
        //object not found because an unoccupied spot was identified.
        //object not found because an unoccupied spot was identified.
        return false;
    }


    void display() {
        //Make sure to change the name for table being displayed
        cout << "\nQuadratic Probing Hash Table:" << endl;
        double count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                count++;
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                //state that it is empty
                cout << "[" << i << "] Empty" << endl;
            }
        }
        double load = count / TABLE_SIZE;
        cout << "\n LOAD FACTOR: " << load;
    }
};

//cubic hashing table
class CubicProbingHashTable {
private:
    int table[TABLE_SIZE];

public:
    CubicProbingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    void insert(int key) {
        int index = cubicHash(key);
        //while the table is NOT empty (i.e. collision) 
        //perform a CUBIC probe
        int i = 0;
        while (table[index] != -1) {
            i++;
            index = (index + i * i* i) % TABLE_SIZE;  // CUBIC probing
        }
        table[index] = key; //unoccupied location found, insert the key
    }

    bool find(int key) {
        //check the starting location for this particular hash
        int index = cubicHash(key);
        //while the space is occupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            if (table[index] == key) {
                return true;
            }
            index = (index + i * i*i) % TABLE_SIZE;  // CUBIC probing THIS MEANS IT CONTINUES TO CHECK LINEARLY.
        }

        return false;
    }

    bool remove(int key) {
        //check the starting location for this particular hash
        int index = cubicHash(key);
        //while the space is not unoccupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            //the key has been found, replace it with a blank
            if (table[index] == key) {
                table[index] = -1;
                return true; //object removed, return your success
            }
            //location was occupied, use probing to get to the next one. 
            index = (index + i * i*i) % TABLE_SIZE;  // CUBIC probing
        }
        //object not found because an unoccupied spot was identified.
        //object not found because an unoccupied spot was identified.
        return false;
    }


    void display() {
        //Make sure to change the name for table being displayed
        cout << "\nCubic Probing Hash Table:" << endl;
        double count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                count++;
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                //state that it is empty
                cout << "[" << i << "] Empty" << endl;
            }
        }
        double load = count / TABLE_SIZE;
        cout << "\n LOAD FACTOR: " << load;
    }
};

//doublehasing 
class DoubleHashingHashTable {
private:
    int table[TABLE_SIZE];

public:
    DoubleHashingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    void insert(int key) {
        int index = doubleHash(key);
        //while the table is NOT empty (i.e. collision) 
        //perform a DOUBLE HASH probe
        int i = 0;
        while (table[index] != -1) {
            i++;
            index = (index + i * 2) % TABLE_SIZE;  // double hash probing
        }
        table[index] = key; //unoccupied location found, insert the key
    }

    bool find(int key) {
        //check the starting location for this particular hash
        int index = doubleHash(key);
        //while the space is occupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            if (table[index] == key) {
                return true;
            }
            index = (index + i * 2) % TABLE_SIZE;  // DOUBLE HASHING probing THIS MEANS IT CONTINUES TO CHECK LINEARLY.
        }

        return false;
    }

    bool remove(int key) {
        //check the starting location for this particular hash
        int index = doubleHash(key);
        //while the space is not unoccupied, continue to check
        int i = 0;
        while (table[index] != -1) {
            i++;
            //the key has been found, replace it with a blank
            if (table[index] == key) {
                table[index] = -1;
                return true; //object removed, return your success
            }
            //location was occupied, use probing to get to the next one. 
            index = (index + i * 2) % TABLE_SIZE;  // DOUBLE HASH probing
        }
        //object not found because an unoccupied spot was identified.
        //object not found because an unoccupied spot was identified.
        return false;
    }


    void display() {
        //Make sure to change the name for table being displayed
        cout << "\nDouble Hash Probing Hash Table:" << endl;
        double count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                count++;
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                //state that it is empty
                cout << "[" << i << "] Empty" << endl;
            }
        }
        double load = count / TABLE_SIZE;
        cout << "\n LOAD FACTOR: " << load;
    }
};

/* WHY DO YOU HAVE THIS JUST LAYING AROUND?????
    void display() {
        cout << "\nLinear Probing Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                cout << "[" << i << "] Empty" << endl;
            }
        }
    }
};
*/

int main() 
{
    int keys[] = { 7, 17, 18, 27, 37, 47, 57, 67, 77, 87, 97 };

    LinearProbingHashTable      linearProbingTable;
    OpenChainingHashTable       openChainingTable;
    QuadraticProbingHashTable   quadraticProbingTable;
    CubicProbingHashTable       cubicProbingTable;
    DoubleHashingHashTable      doubleHashingTable;


    cout << "Inserting keys into hash tables..." << endl;

    for (int key : keys) 
    {
        linearProbingTable.insert(key);
        openChainingTable.insert(key);

        quadraticProbingTable.insert(key);
        doubleHashingTable.insert(key);
        cubicProbingTable.insert(key);
    }

    cout << "Displaying hash tables..." << endl;

    linearProbingTable.display();
    openChainingTable.display();

    quadraticProbingTable.display();
    doubleHashingTable.display();
    cubicProbingTable.display();

    // Find and remove keys in the hash tables
    int keyToFind = 47;
    cout << "Searching for key " << keyToFind << " in hash tables:" << endl;
    cout << "Linear Probing: " << (linearProbingTable.find(keyToFind) ? "Found" : "Not Found") << endl;
    cout << "Open Chaining: " << (openChainingTable.find(keyToFind) ? "Found" : "Not Found") << endl;

    cout << "Cubic Hashing: " << (cubicProbingTable.find(keyToFind) ? "Found" : "Not Found") << endl;
    cout << "Quadratic Probing: " << (quadraticProbingTable.find(keyToFind) ? "Found" : "Not Found") << endl;
    cout << "Double Hashing: " << (doubleHashingTable.find(keyToFind) ? "Found" : "Not Found") << endl;

    int keyToDelete = 37;
    cout << "Removing key " << keyToDelete << " from hash tables:" << endl;
    cout << "Linear Probing: " << (linearProbingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;
    cout << "Open Chaining: " << (openChainingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;

    cout << "Cubic Probing: " << (cubicProbingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;
    cout << "Quadratic Probing: " << (quadraticProbingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;
    cout << "Double Hashing: " << (doubleHashingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;

    cout << "Displaying updated hash tables..." << endl;

    linearProbingTable.display();
    openChainingTable.display();

    cubicProbingTable.display();
    quadraticProbingTable.display();
    doubleHashingTable.display();

    return 0;
}
