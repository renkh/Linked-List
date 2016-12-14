/*****************************************************************************
  Title          : contactlist.h
  Author         : Renat Khalikov
  Created on     : November 17, 2016
  Description    : implementation of header file contactlist.h
  Purpose        : 
  Usage          : 
  Build with     : g++ -c -Wall contactlist.cpp
*/

#include "contactlist.h"
#include <string>
#include <iostream>
#include <cstdlib> // exit() call
#include <fstream>
using namespace std;

Name::Name()
{

}

string Name::first()
{
    return fname;
}

string Name::last()
{
    return lname;
}

void Name::set_first(string f_name)
{
    fname = f_name;
}

void Name::set_last(string l_name)
{
    lname = l_name;
}

//  The Contact class defined below is needed by the ContactList ADT. This class is not documented either because the methods are simple accessors and mutators.
Contact::Contact ()
{
    
}

Contact::Contact (Name person, string tel_num, string email_addr)
{
    name = person;
    telephone = tel_num;
    email = email_addr;
}

void Contact::set (string fname, string lname, string tel_num, string email_addr)
{

}
void Contact::get_name  (Name& fullname)
{
    fullname = name;
}
void Contact::get_tel   (string& tel_num)
{
    tel_num = telephone;
}

void Contact::get_email (string& email_addr)
{
    email_addr = email;
}

void Contact::set_name  (string fullname)
{


}
void Contact::set_tel   (string tel_num)
{

}
void Contact::set_email (string email_addr)
{

}


//  CONTACTLIST CLASS PUBLIC MEMBERS
/** Constructor: 
 * Creates an empty contact list.
 * @pre  None
 * @post The object is empty.
*/
ContactList::ContactList()
{
    head = NULL; 
    listSize = 0;
}


/** Destructor 
 * Deletes all memory used by the contact list.
 * @pre None
 * @post The list is empty
 * Note that this is not called by any code.
 */
ContactList::~ContactList()
{

}



/** display(output)
 * Outputs the contact list in sorted order by last name, with the first 
 * name as the secondary key. The data is spaced on the line so that each 
 * data field is  aligned with the one above. The implementation is free 
 * to choose the specific field widths.
 *
 * @pre      The ostream has been opened.
 * @post     The contacts in the contact list are appended to the ostream 
 *           in sorted order, by last name, and then by first name in case 
 *           last names are identical. If there are two records with 
 *           identical primary and secondary key, the telephone number is 
 *           used as a tertiary key, and if need be the email address is 
 *           the quaternary key.
 * @param [inout] ostream output The stream for outputting the contact 
 *          list.
 * @returns  int The number of records written
 */
void ContactList::display(ostream& output)
{
    link current = head;

    Name fullname_in_record;
    
    string lastnameInRecord, firstnameInRecord, telephone, email;

    while ( NULL != current){
        current->record.get_name(fullname_in_record);
        lastnameInRecord = fullname_in_record.last();
        firstnameInRecord = fullname_in_record.first();
        current->record.get_tel(telephone);
        current->record.get_email(email);
        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
        current = current->next;
    }
}



/** insert(record_to_insert)
 * Inserts a given record into the contact list. If the record is an exact
 * duplicate of an existing record, it will not be added.
 * 
 * @pre     record_to_insert is a valid Contact. If there is not an exact 
 *          copy of record_to_insert already in contact list, then 
 *          record_to_insert is inserted into the list at an unspecified 
 *          position.
 * @returns int The total number of contacts successfully inserted into 
 *          the list.
 */
int ContactList::insert(Contact record_to_insert)
{

    // pointers
    link current , previous ; 

    Name fullname_to_insert;
    record_to_insert.get_name(fullname_to_insert);
    string lastnameToInsert;
    lastnameToInsert = fullname_to_insert.last();

    // If list is empty, insert record at the front
    if ( NULL == head ) {
        link temp_ptr = new node;
        if ( NULL == temp_ptr ){
            return false;
        }
        temp_ptr->record = record_to_insert;
        temp_ptr->next = head;
        head           = temp_ptr; 
        listSize++;

        return 1 ;
    }

    Name fullname_in_record;
    head->record.get_name(fullname_in_record);
    string lastnameInRecord;
    lastnameInRecord = fullname_in_record.last();

    // if the record to insert is smaller than the record in the list, needs
    // to be inserted in the front of the list as well
    if (lastnameToInsert < lastnameInRecord ){
        link temp_ptr = new node;
        if ( NULL == temp_ptr ){
            return false;
        }
        temp_ptr->record = record_to_insert;
        temp_ptr->next = head;
        head           = temp_ptr; 
        listSize++;

        return 1 ;

    }

    // if the last names match, we need to sort by first name 
    if (lastnameToInsert == lastnameInRecord){
        string firstnameInRecord, firstnameToInsert;
        firstnameInRecord = fullname_in_record.first();
        firstnameToInsert = fullname_to_insert.first();

        // if the first name is less than the one in the record,
        // insert before the record
        if ( firstnameToInsert < firstnameInRecord ) {
            link temp_ptr = new node;
            if ( NULL == temp_ptr ){
                return false;
            }
            temp_ptr->record = record_to_insert;
            temp_ptr->next = head;
            head = temp_ptr; 
            listSize++;
            return 1 ;
        }

        // first name also matches, need to sort by telephone number
        else if (firstnameToInsert == firstnameInRecord){
            string telephoneInRecord;
            head->record.get_tel(telephoneInRecord);
            string telephoneToInsert;
            record_to_insert.get_tel(telephoneToInsert);

            // if telephone number is less than the one in record, insert
            // before the record
            if ( telephoneToInsert < telephoneInRecord) { 
                link temp_ptr = new node;
                if ( NULL == temp_ptr ){
                    return false;
                }
                temp_ptr->record = record_to_insert;
                temp_ptr->next = head;
                head = temp_ptr; 
                listSize++;
                return 1 ;
            }

            // if telephone number is greater than the one in record, insert
            // after the record
            else if ( telephoneToInsert > telephoneInRecord ) {
                // advance current
                link temp_ptr = new node;
                if ( NULL == temp_ptr ){
                    return false;
                }
                temp_ptr->record = record_to_insert;
                temp_ptr->next = head->next;
                head->next = temp_ptr; 
                listSize++;
                return 1 ;
            }

            // telephone numbers match, need to sort by email address
            else{
                string emailInRecord;
                head->record.get_email(emailInRecord);
                string emailToInsert;
                record_to_insert.get_email(emailToInsert);

                // if email address is less than the one in record, insert
                // before the record
                if ( emailToInsert < emailInRecord ) { 
                    link temp_ptr = new node;
                    if ( NULL == temp_ptr ){
                        return false;
                    }
                    temp_ptr->record = record_to_insert;
                    temp_ptr->next = head;
                    head = temp_ptr; 
                    listSize++;
                    return 1 ;
                }

                // if email address is greater than the one in record, insert
                // after the record
                else {
                    link temp_ptr = new node;
                    if ( NULL == temp_ptr ){
                        return false;
                    }
                    temp_ptr->record = record_to_insert;
                    temp_ptr->next = head->next;
                    head->next = temp_ptr; 
                    listSize++;
                    return 1 ;
                }
            }
        }

        // the first name is greater than the one in record, need to look
        // at the second node to see if it's less, greater, or equal to
        else {
            previous = head;
            current = head->next ;

            // if 2nd node exists, need to look at the list until reach end
            while ( current != NULL ) {
                current->record.get_name(fullname_in_record);
                lastnameInRecord = fullname_in_record.last();

                // if last name is less than the one in the record
                if ( lastnameToInsert < lastnameInRecord ) { 
                    // insert before the record, in this case, it will be
                    // the 2nd node
                    link temp_ptr = new node;
                    if ( NULL == temp_ptr ){
                        return false;
                    }
                    temp_ptr->record = record_to_insert;
                    temp_ptr->next = previous->next;
                    previous->next = temp_ptr; 
                    listSize++;
                    return 1 ;
                }

                // if last name is greater than the one in the record
                else if ( lastnameToInsert > lastnameInRecord ) {
                    // if we reached the end of the list
                    if (NULL == current->next){
                        // insert after the record, in this case it will
                        // be the 3rd node
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = current->next;
                        current->next = temp_ptr; 
                        listSize++;
                        return 1 ;
                    }

                    // we didn't reach the end of the list, advance to the next record
                    previous = current;
                    current = current->next;
                }

                // if last names match
                else {
                    // sort by the first name
                    string firstnameInRecord, firstnameToInsert;
                    firstnameInRecord = fullname_in_record.first();
                    firstnameToInsert = fullname_to_insert.first();

                    // if the first name is less than the one in the record
                    if ( firstnameToInsert < firstnameInRecord ) { 
                        // insert it before the record
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = previous->next;
                        previous->next = temp_ptr; 
                        listSize++;
                        return 1 ;
                    }

                    // if the first name is greater than the record
                    else if ( firstnameToInsert > firstnameInRecord) {
                        // needs to be inserted after the record
                        // check to see if the next record has a different 
                        // last name
                        string peekLastName;
                        if (NULL != current->next)
                        {
                            link peekNext = current->next;
                            peekNext->record.get_name(fullname_in_record);
                            peekLastName = fullname_in_record.last();

                            // if the next record has a different last name
                            // insert new record after current one
                            if (peekLastName != lastnameToInsert){
                                link temp_ptr = new node;
                                if ( NULL == temp_ptr ){
                                    return false;
                                }
                                temp_ptr->record = record_to_insert;
                                temp_ptr->next = current->next;
                                current->next = temp_ptr; 
                                listSize++;
                                
                                return 1 ;
                            }

                            // else the next record contains the same last name
                            // need to advance to the next record
                            else{
                                previous = current;
                                current = current->next;
                            }
                        }
                        
                        // else we reached the end of the list,
                        // insert at the end
                        else{
                            link temp_ptr = new node;
                            if ( NULL == temp_ptr ){
                                return false;
                            }
                            temp_ptr->record = record_to_insert;
                            temp_ptr->next = current->next;
                            current->next = temp_ptr; 
                            listSize++;
                            return 1 ;
                        }
                        
                    }
                    // both last names and first names match
                    else{
                        // sort by telephone number
                        string telephoneInRecord;
                        current->record.get_tel(telephoneInRecord);
                        string telephoneToInsert;
                        record_to_insert.get_tel(telephoneToInsert);

                        // telephone number is less than in record
                        if ( telephoneToInsert < telephoneInRecord) { 
                            link temp_ptr = new node;
                            if ( NULL == temp_ptr ){
                                return false;
                            }
                            temp_ptr->record = record_to_insert;
                            temp_ptr->next = previous->next;
                            previous->next = temp_ptr; 
                            listSize++;
                            return 1 ;
                        }

                        // telephone number is greater than in record
                        else if ( telephoneToInsert > telephoneInRecord) {
                            // needs to be inserted after the record
                            // check to see if the next record has a different 
                            // telephone number
                            string peekTelephone;
                            if (NULL != current->next)
                            {
                                link peekNext = current->next;
                                peekNext->record.get_tel(peekTelephone);

                                // if the next record has a different telephone
                                // number, insert new record after current one
                                if (peekTelephone != telephoneInRecord){
                                    link temp_ptr = new node;
                                    if ( NULL == temp_ptr ){
                                        return false;
                                    }
                                    temp_ptr->record = record_to_insert;
                                    temp_ptr->next = current->next;
                                    current->next = temp_ptr; 
                                    listSize++;
                                    
                                    return 1 ;
                                }

                                // else the next record contains the same
                                // telephone number, need to advance to the
                                // next record
                                else{
                                    previous = current;
                                    current = current->next;
                                }
                            }
                        }

                        // telephone numbers match
                        else{
                            // sort by email address
                            string emailInRecord;
                            current->record.get_email(emailInRecord);
                            string emailToInsert;
                            record_to_insert.get_email(emailToInsert);

                            // if email address is less than in record
                            if ( emailToInsert < emailInRecord) { 
                                // input the record before the current one
                                link temp_ptr = new node;
                                if ( NULL == temp_ptr ){
                                    return false;
                                }
                                temp_ptr->record = record_to_insert;
                                temp_ptr->next = previous->next;
                                previous->next = temp_ptr; 
                                listSize++;
                                return 1 ;
                            }

                            // email address is equal to or greater than the record
                            else {
                                // input the record after the current record
                                link temp_ptr = new node;
                                if ( NULL == temp_ptr ){
                                    return false;
                                }
                                temp_ptr->record = record_to_insert;
                                temp_ptr->next = current->next;
                                current->next = temp_ptr; 
                                listSize++;
                                
                                return 1 ;
                            }
                        }
                    }
                }
            } //end while

            // otherwise this is the end of the list so insert at the end
            link temp_ptr = new node;
            if ( NULL == temp_ptr ){
                return false;
            }
            temp_ptr->record = record_to_insert;
            temp_ptr->next = head->next;
            head->next = temp_ptr; 
            listSize++;
            return 1 ;
        }
    }

    // last name is greater than the first node, we start at 2nd node 
    // if it exists
    previous = head;
    current = head->next ;
    while ( current != NULL ) {
        current->record.get_name(fullname_in_record);
        lastnameInRecord = fullname_in_record.last();

        // if last name is less than the one in the record
        if ( lastnameToInsert < lastnameInRecord ) { 
            // insert before the record
            link temp_ptr = new node;
            if ( NULL == temp_ptr ){
                return false;
            }
            temp_ptr->record = record_to_insert;
            temp_ptr->next = previous->next;
            previous->next = temp_ptr; 
            listSize++;
            return 1 ;
        }

        // if last name is greater than the one in the record
        else if ( lastnameToInsert > lastnameInRecord ) {
            // if we reached the end of the list
            if (NULL == current->next){
                // insert after the record
                link temp_ptr = new node;
                if ( NULL == temp_ptr ){
                    return false;
                }
                temp_ptr->record = record_to_insert;
                temp_ptr->next = current->next;
                current->next = temp_ptr; 
                listSize++;
                
                return 1 ;
            }

            // we didn't reach the end of the list, advance to the next record
            previous = current;
            current = current->next;
        }
        // last names match
        else {
            string firstnameInRecord, firstnameToInsert;
            firstnameInRecord = fullname_in_record.first();
            firstnameToInsert = fullname_to_insert.first();

            // if the first name is less than the one in the record
            if ( firstnameToInsert < firstnameInRecord ) { 
                // insert it before the record
                link temp_ptr = new node;
                if ( NULL == temp_ptr ){
                    return false;
                }
                temp_ptr->record = record_to_insert;
                temp_ptr->next = previous->next;
                previous->next = temp_ptr; 
                listSize++;
                return 1 ;
            }

            // if the first name is greater than the record
            else if ( firstnameToInsert > firstnameInRecord) {
                // needs to be inserted after the record
                // check to see if we reached the end of the list, or
                // if the next record is different
                string peekLastName;
                if (NULL != current->next)
                {
                    link peekNext = current->next;
                    peekNext->record.get_name(fullname_in_record);
                    peekLastName = fullname_in_record.last();

                    if (peekLastName != lastnameToInsert){
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = current->next;
                        current->next = temp_ptr; 
                        listSize++;
                        
                        return 1 ;
                    }
                    else{
                        previous = current;
                        current = current->next;
                    }
                }
                
                
                else{
                    link temp_ptr = new node;
                    if ( NULL == temp_ptr ){
                        return false;
                    }
                    temp_ptr->record = record_to_insert;
                    temp_ptr->next = current->next;
                    current->next = temp_ptr; 
                    listSize++;
                    
                    return 1 ;
                }
                
            }
            // both last names and first names match
            else{
                // sort by telephone number
                string telephoneInRecord;
                current->record.get_tel(telephoneInRecord);
                string telephoneToInsert;
                record_to_insert.get_tel(telephoneToInsert);

                // telephone number is less than in record
                if ( telephoneToInsert < telephoneInRecord) { 
                    link temp_ptr = new node;
                    if ( NULL == temp_ptr ){
                        return false;
                    }
                    temp_ptr->record = record_to_insert;
                    temp_ptr->next = previous->next;
                    previous->next = temp_ptr; 
                    listSize++;
                    return 1 ;
                }

                // telephone number is greater than in record
                else if ( telephoneToInsert > telephoneInRecord) {
                    // previous points to an item that was smaller and current* 
                    // is bigger so record_to_insert should be inserted after previous
                    if (NULL == current->next)
                    {
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = current->next;
                        current->next = temp_ptr; 
                        listSize++;
                        
                        return 1 ;
                    }
                    
                    previous = current;
                    current = current->next;
                }

                // telephone numbers match
                else{
                    // sort by email address
                    string emailInRecord;
                    current->record.get_email(emailInRecord);
                    string emailToInsert;
                    record_to_insert.get_email(emailToInsert);

                    // if email address is less than in record
                    if ( emailToInsert < emailInRecord) { 
                        // input the record before the current one
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = previous->next;
                        previous->next = temp_ptr; 
                        listSize++;
                        return 1 ;
                    }

                    // email address is equal to or greater than the record
                    else {
                        // input the record after the current record
                        link temp_ptr = new node;
                        if ( NULL == temp_ptr ){
                            return false;
                        }
                        temp_ptr->record = record_to_insert;
                        temp_ptr->next = current->next;
                        current->next = temp_ptr; 
                        listSize++;
                        
                        return 1 ;
                    }
                }
            }
        }
    } //end while

    // if we reach here , the item is bigger than everything in list 
    // and previous points to last node, so insert at the end
    link temp_ptr = new node;
    if ( NULL == temp_ptr ){
        return false;
    }
    temp_ptr->record = record_to_insert;
    temp_ptr->next = current;
    previous->next = temp_ptr; 
    listSize++;
    
    return 1 ;              
} // end insert




/** insert( contact_list)
 * Inserts all contacts in contact_list into the current contact list.
 * If any of the contacts in contact_list are duplicates of an existing 
 * contact, they will not be inserted. The contacts are inserted at 
 * unspecified positions.
 * 
 * @pre      A contact list consisting of only valid Contacts. 
 * @post     The contact list contains all previously existing contacts 
 *           plus all contacts from contact_list that are not exact copies 
 *           of records already in the existing contact list.
 * @returns int The total number of contacts sucessfully inserted into the 
 *          list.
 */
//int ContactList::insert(ContactList contact_list)





/** remove(record_to_delete)
 * Removes all contacts which match the non-null fields of 
 * record_to_delete. 
 * Every contact in the contact list whose members match every non-null 
 * member of record_to_delete is removed from the list.
 * 
 * @pre     record_to_delete is a contact containing at least a non-null 
 *          last name and a non-null first name. 
 * @post    The contact list will contain no contacts which match the 
 *          non-null fields of record_to_delete.
 * @returns int The total number of contacts successfully removed from the 
 *          list.
 */
int ContactList::remove(Contact record_to_delete)
{
    link current, prev;
    int  count = 0;
    // If the list is empty, there is nothing to do
    if ( NULL != head ) 
    {
        current = head;
        prev = NULL;

        // access the last name to be deleted from the contact object
        Name fullname_to_delete;
        record_to_delete.get_name(fullname_to_delete);
        string lastnameToDelete;
        lastnameToDelete = fullname_to_delete.last();
        // iterate through the whole list
        while ( current != NULL ) 
        {
            // access the last name form the linked list that current points
            // to
            Name fullname_in_record;
            current->record.get_name(fullname_in_record);
            string lastnameInRecord;
            lastnameInRecord = fullname_in_record.last();

            // compare last name to be deleted with last name in record
            if ( lastnameToDelete < lastnameInRecord) {
                // item is bigger than current item so advance pointers
                break;
            }
            else if ( lastnameToDelete > lastnameInRecord) {
                // item is smaller than current item, so item cannot be in
                // remainder of the list and we can stop searching
                prev = current;
                current = current->next;
            }
            else { // lastnameInRecord == lastnameToDelete
                // access the first name to be deleted from the contact object
                string firstnameToDelete, firstnameInRecord;
                firstnameToDelete = fullname_to_delete.first();
                current->record.get_name(fullname_in_record);
                firstnameInRecord = fullname_in_record.first();

                // compare first name to be deleted with first name in record
                if (firstnameToDelete < firstnameInRecord){
                    // item is bigger than current item so advance pointers
                    break;
                }

                else if (firstnameToDelete > firstnameInRecord) 
                {
                    // item is smaller than current item, so item cannot be in
                    // remainder of the list and we can stop searching
                    prev = current;
                    current = current->next;
                }

                else{ // firstnameInRecord == firstnameToDelete
                    // check if telephone is provided
                    string telephoneToDelete, telephoneInRecord;
                    record_to_delete.get_tel(telephoneToDelete);
                    current->record.get_tel(telephoneInRecord);

                    // if telephone is provided, it needs to be deleted too
                    if (!telephoneToDelete.empty()){
                        // compare telephone number to be deleted with 
                        // telephone number in record
                        if (telephoneToDelete < telephoneInRecord){
                            // item is bigger than current item so advance pointers
                            break;
                        }

                        else if ( telephoneToDelete > telephoneInRecord) 
                        {
                            // item is smaller than current item, so item cannot be in
                            // remainder of the list and we can stop searching
                            prev = current;
                            current = current->next;
                        }
                        else{ // telephoneInRecord == telephoneToDelete
                            // check if email address is provided
                            string emailToDelete, emailInRecord;
                            record_to_delete.get_tel(emailToDelete);
                            current->record.get_tel(emailInRecord);

                            // if it is provided, it must be deleted too
                            if (!emailToDelete.empty()){
                                // compare email address to be deleted with 
                                // email address in record
                                if (emailToDelete < emailInRecord){
                                    // item is bigger than current item so advance pointers
                                    break;
                                }

                                else if ( emailToDelete > emailInRecord) 
                                {
                                    // item is smaller than current item, so item cannot be in
                                    // remainder of the list and we can stop searching
                                    prev = current;
                                    current = current->next;
                                }
                                else{ // emailToDelete == emailInRecord
                                    // found emailToDelete
                                    // we can delete the first, last, telephone, and 
                                    // email address of the contact
                                    // if we need to delete the first node
                                    if ( NULL == prev ) 
                                    {
                                        // first node: handle separately
                                        head          = current->next; // detach from list
                                        current->next = NULL;          // clear next link
                                        delete current;                // free node
                                        current = head;
                                        count++;
                                    }
                                    else 
                                    { // not first node, so prev can be dereferenced
                                        prev->next = current->next;
                                        current->next = NULL;
                                        delete current->next;
                                        prev->next = current;
                                        count++;
                                    }
                                }
                            } // end if email address is provided
                            else{ // email address is not provided
                                // we can delete specified first, last, and 
                                // telephone record
                                // if the node to be deleted is first in the
                                // list
                                if ( NULL == prev ) 
                                {
                                    // first node: handle separately
                                    head          = current->next; // detach from list
                                    current->next = NULL;          // clear next link
                                    delete current;                // free node
                                    current = head;
                                    count++;
                                }
                                else 
                                { // not first node, so prev can be dereferenced
                                    prev->next = current->next;
                                    current->next = NULL;
                                    delete current->next;
                                    prev->next = current;
                                    count++;
                                }
                            } // end if email address is not provided
                        }
                    } // end if telephone number is provided

                    else{ // telephone is not provided
                        // check if email address is provided
                        string emailToDelete, emailInRecord;
                        record_to_delete.get_email(emailToDelete);
                        current->record.get_email(emailInRecord);

                        // if it is provided, it must be deleted too
                        if (!emailToDelete.empty()){
                            // compare email address to be deleted with 
                            // email address in record
                            if (emailToDelete < emailInRecord){
                                // item is bigger than current item so advance pointers
                                break;
                            }

                            else if ( emailToDelete > emailInRecord ) 
                            {
                                // item is smaller than current item, so item cannot be in
                                // remainder of the list and we can stop searching
                                prev = current;
                                current = current->next;
                            }
                            else{ // emailToDelete == emailInRecord

                                cout << "Here\n";
                                // found emailToDelete
                                // we can delete the first, last, and 
                                // email address of the contact
                                // if we need to delete the first node
                                if ( NULL == prev ) 
                                {
                                    // first node: handle separately
                                    head          = current->next; // detach from list
                                    current->next = NULL;          // clear next link
                                    delete current;                // free node
                                    current = head;
                                    count++;
                                }
                                else 
                                { // not first node, so prev can be dereferenced
                                    prev->next = current->next;
                                    current->next = NULL;
                                    delete current;
                                    current = prev->next;
                                    count++;
                                }
                            }
                        } // end if email address is provided

                        // email is not provided
                        // we can delete all first and last names that are
                        // specified
                        if ( NULL == prev ) 
                        {
                            // first node: handle separately
                            head          = current->next; // detach from list
                            current->next = NULL;          // clear next link
                            delete current;                // free node
                            current = head;
                            count++;
                        }

                        else 
                        { // not first node, so prev can be dereferenced
                            prev->next = current->next;
                            current->next = NULL;
                            delete current;
                            current = prev->next;
                            count++;
                        }
                    } // end if telephone is not provided
                }
            } // end else
        } // end while
    } // end if head != NULL
    listSize -= count;
    return count;
}



/** size()
 * Returns the total number of contacts in the contact list.
 *
 * @pre         None.
 * @post        None.
 * @returns int The total number of contacts in the contact list.
 */
int ContactList::size()
{
    return listSize;
}






/** save()
 * This saves a copy of the current contactlist by writing it to a file 
 * named contactlist.bkp in the current working directory, overwriting any 
 * such file if it already exists. It must have write permission in the 
 * working directory.
 *
 * @pre     None. 
 * @post    The contactlist.bkp file in the current working directory 
 *          contains the contents of the current copy of the in-memory 
 *          contact list. If the file existed before, it is replaced. 
 * @returns int The number of contacts written to the file, or -1 if the 
 *          write was not allowed.
 */
int ContactList::save()
{
    // open the outout file
    ofstream outputFile;
    outputFile.open("contactlist.bkp");
    if (outputFile.fail()){
        cerr << "Could not open file to save" << endl;
        exit(1); // 1 indicates an error occurred
    }

    // begin at the start of the list
    link current = head;
    Name fullname_in_record;
    string lastnameInRecord, firstnameInRecord, telephone, email;
    int count = 0;

    // iterate through the whole list, and output the contents of each record
    while ( NULL != current){
        // collect the first and last name of the record
        current->record.get_name(fullname_in_record);
        lastnameInRecord = fullname_in_record.last();
        firstnameInRecord = fullname_in_record.first();

        // collect the telephone number and email address
        current->record.get_tel(telephone);
        current->record.get_email(email);

        // output the record into output file one record per line
        outputFile << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;

        // advance to the next record and update the counter
        // the counter prints how many records are written to file
        current = current->next;
        count+=1;
    }
    return count;
}



/** find(output, lastname, firstname)
 * Writes onto the output stream all contacts whose last and first names 
 * match the given names.
 *
 * @pre      lastname is a valid name and firstname is a valid name and 
 *           output is an open iostream.
 * @post     Any contacts whose first and last names match the given first 
 *           and last names are appended to the ostream.
 * @returns int The number of records written to the stream.
 */
int ContactList::find(ostream& output, string lname, string fname)
{
    link current;
    int count = 0;
    // list is empty
    if (NULL == head){
        return -1;
    }

    //list is not empty
    current = head;

    // iterate through the whole list
    while(NULL != current){
        // collect the first and last name in the record
        Name fullname_in_record;
        current->record.get_name(fullname_in_record);
        string lastnameInRecord, firstnameInRecord;
        lastnameInRecord = fullname_in_record.last();
        firstnameInRecord = fullname_in_record.first();

        // if only the last name is provided
        if (!lname.empty() && fname.empty()){
            // compare the last name in record to last name given
            if (lastnameInRecord < lname){
                current = current->next;
            }
            else if (lastnameInRecord > lname){
                // item is not in the list
                return count;
            }
            else if(lastnameInRecord == lname){
                //found the item
                string telephone;
                current->record.get_tel(telephone);
                string email;
                current->record.get_email(email);
                output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                current = current->next;
                count+=1;
            }
        } // end if only the last name is given

        // if only the first name is provided
        else if (lname.empty() && !fname.empty()){
            // compare the first name in record to first name given
            if (firstnameInRecord < fname){
                current = current->next;
            }
            else if (firstnameInRecord > fname){
                // item is not in the list
                return count;
            }
            else if (firstnameInRecord == fname){
                //found the item
                string telephone;
                current->record.get_tel(telephone);
                string email;
                current->record.get_email(email);
                output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                current = current->next;
                count+=1;
            }
        } // end if only the first name is given

        // first and last names are both given
        else if (!lname.empty() && !fname.empty()){
            // if record is less than the given last name
            if (lastnameInRecord < lname){
                // advance to the next record
                current = current->next;
            }

            // if record is greater than the given last name
            else if (lastnameInRecord > lname){
                // item is not in the list
                return count;
            }

            // otherwise record matches the last name
            else{
                // if record is less than the given first name
                if (firstnameInRecord < fname){
                    // advance to the next record
                    current = current->next;
                }

                // if record is greater than the given first name
                else if (firstnameInRecord > fname){
                    // item is not in the list
                    return count;
                }

                else{
                    //found the item
                    string telephone;
                    current->record.get_tel(telephone);
                    string email;
                    current->record.get_email(email);
                    output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                    current = current->next;
                    count+=1;
                }
            }
        } // end of first and last names are both given
        // given name is not in the list
        else{
            return count;
        }
    }
    return count;
}



/** find(output, record_to_find)
 * Writes onto the output stream all contacts that match the non-null 
 * fields of record_to_find. 
 *
 * @pre     record_to_find is a valid contact and output is an open 
 *          ostream.
 * @post    Any contacts whose non-null members match the non-null members 
 *          of the record_to_find are appended to the ostream, sorted by 
 *          last name, and then first name in case of ties.
 * @returns  int The number of records written to the stream.
 */
int ContactList::find(ostream& output, Contact record_to_find)
{

    link current;
    int count = 0;
    // list is empty
    if (NULL == head){
        return -1;
    }
    //list is not empty
    current = head;

    // iterate through the whole list
    while(NULL != current){
        // split fullname into first and last names
        Name fullnameInRecord, fullname;
        current->record.get_name(fullnameInRecord);
        string lastnameInRecord, firstnameInRecord, firstnameToFind, lastnameToFind, telephoneToFind, emailToFind;
        lastnameInRecord = fullnameInRecord.last();
        firstnameInRecord = fullnameInRecord.first();

        // get the contacts from the record
        record_to_find.get_name(fullname);
        firstnameToFind = fullname.first();
        lastnameToFind = fullname.last();
        record_to_find.get_tel(telephoneToFind);
        record_to_find.get_email(emailToFind);

        // last name is provided, but not the first name
        if (!lastnameToFind.empty() && firstnameToFind.empty()){
            // compare the last name of the record with the given
            if (lastnameInRecord < lastnameToFind){
                current = current->next;
            }
            else if (lastnameInRecord > lastnameToFind){
                // item is not in the list
                return count;
            }

            // found last name in record
            else if(lastnameInRecord == lastnameToFind){
                // if only the last name needs to be found
                if (telephoneToFind.empty() && emailToFind.empty()){
                    // output record that matches the last name
                    string telephone;
                    current->record.get_tel(telephone);
                    string email;
                    current->record.get_email(email);
                    output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                    current = current->next;
                    count+=1;
                }

                // if the telephone number also needs to be found
                else if (!telephoneToFind.empty()){
                    // get the telephone number from the record
                    string telephoneInRecord;
                    current->record.get_tel(telephoneInRecord);

                    // if the telephone number is less than the one in record
                    if (telephoneToFind < telephoneInRecord){
                        // advance to the next record
                        current = current->next;
                    }

                    // if the telephone number is larger than the one in the
                    // record
                    else if (telephoneToFind > telephoneInRecord){
                        // item is not in the list
                        return count;
                    }

                    // if we reach here we found the telephone number but
                    // if the email address is provided we need to find it too
                    else if (!emailToFind.empty()){
                        // get the email address from record
                        string emailInRecord;
                        current->record.get_email(emailInRecord);

                        // if the email address is less than the record
                        if (emailToFind < emailInRecord)
                        {
                            // advance to the next record
                            current = current->next;
                        }

                        // if the email address is larger than the record
                        else if (emailToFind > emailInRecord){
                            // item is not in the list
                            return count;
                        }

                        // found the last name, telephone number, and email
                        else{
                            // output the items
                            string telephone;
                            current->record.get_tel(telephone);
                            string email;
                            current->record.get_email(email);
                            output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                            current = current->next;
                            count+=1;
                        }
                    }

                    // found last name, and telephone number, we don't
                    // need to find the email address because its NULL
                    else
                    {
                        //output the items
                        string telephone;
                        current->record.get_tel(telephone);
                        string email;
                        current->record.get_email(email);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                        current = current->next;
                        count+=1;
                    }
                } // end if telephone number needs to be found

                // if the email address needs to be found
                else if(!emailToFind.empty()){
                    // get the email address
                    string emailInRecord;
                    current->record.get_email(emailInRecord);

                    // if email is less than the email in record
                    if (emailToFind < emailInRecord)
                    {
                        // advance to the next record
                        current = current->next;
                    }

                    // if the email is larger than the one in the
                    // record
                    else if (emailToFind > emailInRecord){
                        // item is not in the list
                        return count;
                    }

                    // found the first, last, and email address of the contacts
                    else{
                        // output the items
                        string telephone;
                        current->record.get_tel(telephone);
                        string email;
                        current->record.get_email(email);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                        current = current->next;
                        count+=1;
                    }
                } // end if email address needs to be found
            } // end found last name in record
        } // end last name is provided

        // first name is provided, but not the last name
        else if (lastnameToFind.empty() && !firstnameToFind.empty())
        {
            // if first name is or greater than less than the one in record
            if (firstnameInRecord < firstnameToFind || firstnameInRecord > firstnameToFind){
                current = current->next;
            }

            // if we found the first name
            else if (firstnameInRecord == firstnameToFind){
                // we need to check if telephone number and email address are 
                // provided
                // if only the first name needs to be found
                if (telephoneToFind.empty() && emailToFind.empty())
                {
                    // output record that matches the first name
                    string telephone;
                    current->record.get_tel(telephone);
                    string email;
                    current->record.get_email(email);
                    output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                    current = current->next;
                    count+=1;
                }

                // if telephone number needs to be found
                else if (!telephoneToFind.empty()){
                    string telephoneInRecord;
                    current->record.get_tel(telephoneInRecord);

                    // if the telephone number doesn't match
                    if (telephoneToFind < telephoneInRecord)
                    {
                        // advance to the next record
                        current = current->next;
                    }

                    // if the telephone number is larger than the one in the
                    // record
                    else if (telephoneToFind > telephoneInRecord){
                        // item is not in the list
                        return count;
                    }

                    // if we need to find the email address
                    else if (!emailToFind.empty())
                    {
                        string emailInRecord;
                        current->record.get_email(emailInRecord);

                        // if the first name and telephone number match, but 
                        // the email address is less than the record
                        if (emailToFind < emailInRecord)
                        {
                            // advance to the next record
                            current = current->next;
                        }

                        // if the email address is larger than the record
                        else if (emailToFind > emailInRecord){
                            // item is not in the list
                            return count;
                        }

                        // found the first name, telephone number, and email
                        // address
                        else{
                            // output the items
                            string telephone;
                            current->record.get_tel(telephone);
                            string email;
                            current->record.get_email(email);
                            output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                            current = current->next;
                            count+=1;
                        }
                    }

                    // found first name, and telephone number, we don't
                    // need to find the email address because its NULL
                    else
                    {
                        //output the items
                        string telephone;
                        current->record.get_tel(telephone);
                        string email;
                        current->record.get_email(email);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                        current = current->next;
                        count+=1;
                    }
                }

                // if the email address needs to be found
                else if(!emailToFind.empty()){
                    string emailInRecord;
                    current->record.get_email(emailInRecord);

                    // if the email address doesn't match
                    if (emailToFind < emailInRecord)
                    {
                        // advance to the next record
                        current = current->next;
                    }

                    // if the email is larger than the one in the
                    // record
                    else if (emailToFind > emailInRecord){
                        // item is not in the list
                        return count;
                    }

                    // found the first name and it's email address
                    else{
                        // output the items
                        string telephone;
                        current->record.get_tel(telephone);
                        string email;
                        current->record.get_email(email);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                        current = current->next;
                        count+=1;
                    }
                }
            }
        }

        // first and last names are both provided
        else if (!lastnameToFind.empty() && !firstnameToFind.empty())
        {
            // if record is less than the given last name
            if (lastnameInRecord < lastnameToFind){
                // advance to the next record
                current = current->next;
            }

            // if record is greater than the given last name
            else if (lastnameInRecord > lastnameToFind){
                // item is not in the list
                return count;
            }

            // otherwise record matches the last name
            // now need to look at the first name
            else{
                // if record is less than the given first name
                if (firstnameInRecord < firstnameToFind){
                    // advance to the next record
                    current = current->next;
                }

                // if record is greater than the given first name
                else if (firstnameInRecord > firstnameToFind){
                    // item is not in the list
                    return count;
                }

                // found the record with the last name and first name
                else{
                    // if only the first and last name needs to be found
                    if (telephoneToFind.empty() && emailToFind.empty())
                    {
                        // output only the records for first and last name
                        string telephone;
                        current->record.get_tel(telephone);
                        string email;
                        current->record.get_email(email);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                        current = current->next;
                        count+=1;
                    }

                    // if telephone number needs to be found
                    else if (!telephoneToFind.empty()){
                        string telephoneInRecord;
                        current->record.get_tel(telephoneInRecord);

                        // if the last names match but telephone number doesn't
                        if (telephoneToFind < telephoneInRecord)
                        {
                            // advance to the next record
                            current = current->next;
                        }

                        // if the telephone number is larger than the one in the
                        // record
                        else if (telephoneToFind > telephoneInRecord){
                            // item is not in the list
                            return count;
                        }

                        // if we need to find the email address
                        else if (!emailToFind.empty())
                        {
                            string emailInRecord;
                            current->record.get_email(emailInRecord);

                            // if the first name and telephone number match, but 
                            // the email address is less than the record
                            if (emailToFind < emailInRecord)
                            {
                                // advance to the next record
                                current = current->next;
                            }

                            // if the email address is larger than the record
                            else if (emailToFind > emailInRecord){
                                // item is not in the list
                                return count;
                            }

                            // found the first name, telephone number, and email
                            // address
                            else{
                                // output the items
                                string telephone;
                                current->record.get_tel(telephone);
                                string email;
                                current->record.get_email(email);
                                output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                                current = current->next;
                                count+=1;
                            }
                        }

                        // found first name, and telephone number, we don't
                        // need to find the email address because its NULL
                        else
                        {
                            //output the items
                            string telephone;
                            current->record.get_tel(telephone);
                            string email;
                            current->record.get_email(email);
                            output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                            current = current->next;
                            count+=1;
                        }
                    }

                    // if the email address needs to be found
                    else if(!emailToFind.empty()){
                        string emailInRecord;
                        current->record.get_email(emailInRecord);

                        // if the first names match but email doesn't
                        if (emailToFind < emailInRecord)
                        {
                            // advance to the next record
                            current = current->next;
                        }

                        // if the email is larger than the one in the
                        // record
                        else if (emailToFind > emailInRecord){
                            // item is not in the list
                            return count;
                        }

                        // found the first name and it's email address
                        else{
                            // output the items
                            string telephone;
                            current->record.get_tel(telephone);
                            string email;
                            current->record.get_email(email);
                            output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                            current = current->next;
                            count+=1;
                        }
                    }
                }
            }
        }

        // neither the first nor last names are provided
        else if (lastnameToFind.empty() && firstnameToFind.empty())
        {
            // if telephone and email are not provided
            if (telephoneToFind.empty() && emailToFind.empty())
            {
                // nothing is provided;
                return count;
            }

            // if telephone number needs to be found
            else if (!telephoneToFind.empty() && emailToFind.empty()){
                string telephoneInRecord;
                current->record.get_tel(telephoneInRecord);

                // if the last names match but telephone number doesn't
                if (telephoneToFind == telephoneInRecord)
                {
                    //output the items
                    string telephone;
                    current->record.get_tel(telephone);
                    string email;
                    current->record.get_email(email);
                    output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                    current = current->next;
                    count+=1;
                }

                // if we need to find the email address
                else if (!emailToFind.empty())
                {
                    string emailInRecord;
                    current->record.get_email(emailInRecord);

                    // if the last name and telephone number match, but 
                    // the email address is less than the record
                    if (emailToFind < emailInRecord)
                    {
                        // advance to the next record
                        current = current->next;
                    }

                    // if the email address is larger than the record
                    else if (emailToFind > emailInRecord){
                        // item is not in the list
                        return count;
                    }

                    // found the telephone number, and email address
                    else{
                        // output the items
                        string telephone;
                        current->record.get_tel(telephone);
                        output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << emailInRecord << endl;
                        current = current->next;
                        count+=1;
                    }
                }

                // we don't need to find the email address because its NULL
                else
                {
                    // advance to the next record
                    current = current->next;
                }
            }

            // if only the email address needs to be found
            else if(!emailToFind.empty() && telephoneToFind.empty()){

                

                string emailInRecord;
                current->record.get_email(emailInRecord);

                // found the last name and it's email address
                if(emailToFind == emailInRecord){
                    // output the items
                    string telephone;
                    current->record.get_tel(telephone);
                    string email;
                    current->record.get_email(email);
                    output << lastnameInRecord << ", " << firstnameInRecord << ", " << telephone << ", " << email << endl;
                    current = current->next;
                    count+=1;
                }

                // if the last names match but email doesn't
                else
                {
                    // advance to the next record
                    current = current->next;
                }                
            }
        }
    }
    return count;
}



/** make_empty()
 * Deletes all of the contacts in the contact list. 
 * 
 * @pre     None. 
 * @post    The contact list becomes an empty list.
 * @returns int The number of records deleted.
 */
int ContactList::make_empty()
{
    link node_to_delete;
    int count = 0;
    while ( listSize > 0 ) { 
        node_to_delete = head; // save pointer to first node 
        head = head->next; // detach first node from list 
        node_to_delete->next = NULL; // clear its next link 
        delete node_to_delete; // release its storage 
        listSize--; // decrement size
        count+=1;
    }
    return count;
}
