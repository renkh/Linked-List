/*****************************************************************************
  Title          : contactlist.h
  Author         : Renat Khalikov
  Created on     : November 17, 2016
  Description    : header file for contactlist.cpp
  Purpose        : 
  Usage          : 
  Build with     : 
*/
#ifndef __CONTACTLIST_H__ 
#define __CONTACTLIST_H__

#include <string>
#include <iostream>

using namespace std ;
/*
This is the Contact List ADT for Project 3.
 *  In order to specify a Contact List ADT definitively, the underlying type 
 *  must be defined precisely. The first part of this file contains the 
 *  definition of the Contact class, which depends upon a structure called Name
 */
//  The following class is used by the Contact ADT. It is not documented 
//  because it is self-explanatory.
/*****************************************************************************/
class Name
{
public:
    Name();
    string first();
    string last();
    void set_first  (string fname);
    void set_last   (string lname);
/* Data members: */
private:
    string fname;
    string lname;
};
/*****************************************************************************/

// ListItemType
//  The Contact class defined below is needed by the ContactList ADT. This 
// class is not documented either because the methods are simple accessors and 
// mutators.

class Contact
{
public:
    Contact ();
    Contact (Name person, string tel_num, string email_addr);
    void set (string fname, string lname, string tel_num, string email_addr);
    void get_name  (Name& fullname);
    void get_tel   (string& tel_num);
    void get_email (string& email_addr);
    void set_name  (string fullname);
    void set_tel   (string tel_num);
    void set_email (string email_addr);

private:
    Name name;
    string telephone;
    string email;
};
/*****************************************************************************/
typedef struct node* link;
struct node{
    Contact record;
    link next;
};

// LINKEDLIST
//  CONTACTLIST CLASS PUBLIC MEMBERS
class ContactList
{
public:
    /*************************************************************************/
    /** Constructor: 
     * Creates an empty contact list.
     * @pre  None
     * @post The object is empty.
    */
    ContactList();

    /*************************************************************************/
    /** Destructor 
     * Deletes all memory used by the contact list.
     * @pre None
     * @post The list is empty
     * Note that this is not called by any code.
     */
    ~ContactList();
    /*************************************************************************/

    /*************************************************************************/
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
    void display(ostream& output);

    /*************************************************************************/

    /*************************************************************************/
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
    int insert(Contact record_to_insert);
    /*************************************************************************/

    /*************************************************************************/
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
    int insert(ContactList contact_list);
    /*************************************************************************/

    /*************************************************************************/
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
    int remove(Contact record_to_delete);
    /*************************************************************************/

    /*************************************************************************/
    /** size()
     * Returns the total number of contacts in the contact list.
     *
     * @pre         None.
     * @post        None.
     * @returns int The total number of contacts in the contact list.
     */
    int size();
    /*************************************************************************/

    /*************************************************************************/
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
    int save();
    /*************************************************************************/

    /*************************************************************************/
    /** find(output, lastname, firstname)
     * Writes onto the output stream all contacts whose last and first names 
     * match the given names.
     *
     * @pre      lastname is a valid name and firstname is a valid name and 
     * output is an open iostream.
     * @post     Any contacts whose first and last names match the given first 
     *           and last names are appended to the ostream.
     * @returns int The number of records written to the stream.
     */
    int find(ostream& output, string lname, string fname);
    /*************************************************************************/

    /*************************************************************************/
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
    int find(ostream& output, Contact record_to_find);
    /*************************************************************************/

    /*************************************************************************/
    /** make_empty()
     * Deletes all of the contacts in the contact list. 
     * 
     * @pre     None. 
     * @post    The contact list becomes an empty list.
     * @returns int The number of records deleted.
     */
    int make_empty();
    /*************************************************************************/
private:
    link head; // pointer to the first node in the list 
    unsigned int listSize; // number of nodes of the list
};


#endif  //__CONTACTLIST_H__

