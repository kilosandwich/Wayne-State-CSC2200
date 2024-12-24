//
//
// Lab_1.cpp : 
// 
// Start with the following program employee record simple database:
// 
// Assignment:
// Part 1: Implementation
// Add a main menu to manage the employees data, which will include a choice of: 
// 1) Access employee record based on employee ID only (can be the index of the array, you may not to perform asearch, this is called Hashing 
// 2) Add an employee to the database
// 3) Delete an employee (delete the index), if an ID is available use it for the new employee

// Part 2: Report
// Provide program run snapshots and data validation in a report
// Upload your full lab to CANVAS   
//

// The above items are only suggestions, you can come up with your own design, 
// At minimum you should be able to perform the above programming steps.
// Lab grade will be based on programming creativity also.
//




#include <iostream>
#include <string>
using namespace std;

// Employee Class Declaration
//seems annoying, let's also make this a node to simplify things
class Employee
{
private:
    string name;        // Employee's name
    int idNumber;       // ID number
    string department;  // Department name
    string position;    // Employee's position

    
public:
    // Constructors
    Employee(string, int, string, string);
    Employee();

    Employee* next = nullptr; //make it a node

    // update methods
    void setName(string n)
    {
        name = n;
    }

    void setIdNumber(int i)
    {
        idNumber = i;
    }

    void setDepartment(string d)
    {
        department = d;
    }

    void setPosition(string p)
    {
        position = p;
    }

    // Accessors
    string getName()
    {
        return name;
    }

    int getIdNumber()
    {
        return idNumber;
    }

    string getDepartment()
    {
        return department;
    }

    string getPosition()
    {
        return position;
    }

    // Function prototype
    void display() {
        cout << endl; //friendly spacing
        cout << endl << "Displaying Employee Record: ";
        cout << endl << "Name: " << name;
        cout << endl << "ID Number: " << idNumber;
        cout << endl << "Department: " << department;
        cout << endl << "Position: " << position;


    }
    //clear everything except the ID number so we can recyle it. 
    void clear() {
        name = "";        // Employee's name      // ID number
        department = "";  // Department name
        position = "";    // Employee's position
        idNumber = 0;
    }
};

// Constructor #1
Employee::Employee(string n, int i, string d, string p)
{
    name = n;
    idNumber = i;
    department = d;
    position = p;
}

// Constructor #3, default constructor
Employee::Employee()
{
    name = "";
    idNumber = 0;
    department = "";
    position = "";
}


class Database {
    public:
        Employee* head = nullptr; //initialize the LinkedList

        void AddEmployee(string n, int i, string d, string p) {
            Employee* new_node = new Employee(n, i, d, p);
            bool donealready = false;
            if (head == nullptr) {
                head = new_node;
               // cout << "debug: new employee added in head = nullptr scenario";
            }
            else {
                Employee* temp = head;
                
                while (temp->next != nullptr) {
                    if (temp->getIdNumber() == 0) {
                        cout << "Error: ID number already in use.";
                        temp->setName(n);
                        temp->setDepartment(d);
                        temp->setPosition(p);
                        donealready = true;
                        return;
                    }


                    temp = temp->next;
                    cout <<  "help I am stuck here";
                }
                
                if (donealready == false) {
                    Employee* temp = head;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = new_node;


                }
            


            }



        }
        

        void AccessRecord(int id) {
            Employee* temp = head;
            while (temp != nullptr) {
                if (temp->getIdNumber() == id) {
                    temp->display();
                    break;
                }
                temp = temp->next;
            }
        }

        void DeleteEmployee(int id) {
            Employee* temp = head;
            while (temp != nullptr) {
                if (temp->getIdNumber() == id) {
                    temp->clear();
                    break;
                }
                temp = temp->next;
            }
            
        }

        void DisplayAll() {
            Employee* temp = head;
            while (temp != nullptr) {
                temp->display();
                temp = temp->next;
            }
        }





};




// Driver program to demonstrate the class
int main()
{

    Database Database;
    Database.AddEmployee("Albert Smith", 1, "Executive", "President");
    Database.AddEmployee("Potato Jones", 2, "Banana", "Potato");
    //main Menu
    while(true){
        int choice = 0;
        int eid = 0;
        string en = "", ed = "", ep = "";
        cout << endl;
        cout << endl << "You are on the Main Menu, select an option:";
        cout << endl << "1 Access Employee Record";
        cout << endl << "2 Add an employee to the database";
        cout << endl << "3 Delete an employee";
        cout << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            cout << endl << "Input employee id: ";
            cin >> eid;
            Database.AccessRecord(eid);
            break;
        case 2:

            cout << endl << "Input employee name: ";
            cin >> en;
            cout << endl << "Input employee position: ";
            cin >> ep;
            cout << endl << "Input employee department: ";
            cin >> ed;
            cout << endl << "Input employee id: ";
            cin >> eid;
            //cout << "Debug: I am adding a new employee!";
            Database.AddEmployee(en, eid, ed, ep);
            //cout << "Debug: I have added a new employee";
            break;
        case 3:
            cout << endl << "Input employee id: ";
            cin >> eid;
            Database.DeleteEmployee(eid);
            break;
        default:
            cout << endl << "INVALID SELECTION.";
            break;
        }
        
    }

    // Display each employee's data.
    Database.DisplayAll();


    return 0;
}

