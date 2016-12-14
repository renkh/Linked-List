/******************************************************************************
  Title          : main.cpp
  Author         : Renat Khalikov
  Created on     : November 17, 2016
  Description    : The program implements a contact list, it enters an 
  					interactive mode,  repeatedly displays a prompt (list, 
                    insert, delete, find, save, quit) and waits for the user 
                    to enter a command. After a command is entered and the 
                    program responds to it, the prompt is displayed again, 
                    unless the command was quit.
  Purpose        : Use linked lists to create a simple contact list.
  Usage          : g++ -o proj3 main.o contactlist.o
  Build with     : g++ -c -Wall main.cpp
*/
#include <iostream>
#include <fstream> // file io
#include <cstdlib> // exit() call
#include <string>
#include "contactlist.h"
using namespace std;

int main(int argc, char const *argv[])
{
	ifstream inputFile("contactlist.csv");
    if (inputFile.fail()){
        cerr << "Could not open contactlist file" << endl;
        exit(1); // 1 indicates an error occurred
    }

    // create class objects
    ContactList linkedList;
    Contact record;
    Name fullname;
    string first, last, telephone, email;
    int numberOfInsertions = 0;

    // load input file into memory
    while( inputFile.good() ){
        // input file is a csv file so I get each word that ends with a ','
        // unless its the last word which ends with a new line
        getline( inputFile, first, ',' );
        getline( inputFile, last, ',' );
        getline( inputFile, telephone, ',' );
        getline( inputFile, email, '\n');

        // set the first and last names into Name class, and set the fullname,
        // telephone number, and email address into Contact class
        fullname.set_first(first);
        fullname.set_last(last);
        Contact record(fullname, telephone, email);

        // load the Contact object, record, into a linked list returning
        // number of insertions done
        numberOfInsertions += linkedList.insert(record);
    }

    // interactive mode, repeatedly displaying a prompt and waiting for the 
    // user to enter a command
    string c;
    bool done = false;
    while(!done){
        cout << "Enter a command: list, insert, delete, find, save, or quit" << endl;
        cout << "Command: ";
        cin >> c;

        // outputs the linked list onto the terminal
        if("list" == c){
            linkedList.display(cout);
        }

        // inserts user specified contact record
        else if ("insert" == c){
            string lastname, firstname, telNum, emailAddr;
            cout << "last name: ";
            cin >> lastname;
            cout << "first name: ";
            cin >> firstname;
            cout << "telephone number (optional): ";
            cin.ignore();
            getline(cin, telNum);
            cout << "email address (optional): ";
            cin.sync();
            getline(cin, emailAddr);

            fullname.set_first(firstname);
            fullname.set_last(lastname);
            Contact record(fullname, telNum, emailAddr);
            int count = 0;
            count = linkedList.insert(record);
            if ( 1 == count){
                cout << "record inserted successfully" << endl;
            }
        }

        // deletes user specified contact
        else if ("delete" == c){
            string lastname, firstname, telNum, emailAddr;
            cout << "last name: ";
            cin >> lastname;
            cout << "first name: ";
            cin >> firstname;
            cout << "telephone number (optional): ";
            cin.ignore();
            getline(cin, telNum);
            cout << "email address (optional): ";
            cin.sync();
            getline(cin, emailAddr);
            fullname.set_first(firstname);
            fullname.set_last(lastname);
            Contact record(fullname, telNum, emailAddr);
            int count = 0;
            count = linkedList.remove(record);
            cout << "deleted " << count << " records\n";
        }

        // finds user specified contact
        else if ("find" == c){
            string lastname, firstname, telNum, emailAddr;
            cout << "last name (optional): ";
            cin.ignore();
            getline(cin, lastname);
            cout << "first name (optional): ";
            cin.sync();
            getline(cin, firstname);
            cout << "telephone number (optional): ";
            cin.sync();
            getline(cin, telNum);
            cout << "email address (optional): ";
            cin.sync();
            getline(cin, emailAddr);

            Name find_fullname;
            find_fullname.set_first(firstname);
            find_fullname.set_last(lastname);
            Contact find_record(find_fullname, telNum, emailAddr);

            int count = 0;
            count = linkedList.find(cout, find_record);
            if (-1==count){
                cout << "the list is empty, nothing to find\n";
            }
            cout << "found " << count << " records\n";
        }

        // saves the current linked list to an output file
        else if ("save" == c){
            int count = 0;
            count = linkedList.save();
            cout << "saved " << count << " records to contactlist.bkp\n";
        }

        // quits
        else if("quit" == c){
            done = true;
        }

        // if user enters something other than a valid command
        else{
            cout << "invalid command..." << endl;
        }
    }
	return 0;
}

