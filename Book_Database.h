#pragma once
#pragma once
#pragma once
//-----------------------------------------------------------------------------
// Book_Database.h
// Header file for a book database program implemented as a binary search tree
//
// Note: All functions which print data on a book must print an appropriate
//       message if it fails to find any book(s) meeting the search criteria
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "BookRecord.h"

using namespace std;

class Book_Database
{
private:
	BookRecord *m_pRoot;                         		// Pointer to root of the tree
	ifstream   m_InFile;                         		// File containing inventory


public:
	bool found;
	Book_Database();    //Done                        		// Class constructor
	~Book_Database();   //Done                        		// Class destuctor
	bool readDatabase(const char *filename);   //Done        	// Read database from file
	bool addBook(BookRecord *br);              //Done  		// Add the given book to the list
	BookRecord *removeBook(long stockNum);     //NOT DONE         // Remove a book from the list
	BookRecord *searchByStockNumber(long stockNum); //DONE   	// Search for a book by stock number
	void searchByClassification(int cl);         //DONE		// Search for all books of the given classification
	void searchByCost(double min, double max);   //DONE		// Search for all books whose cost is within the given range
	int getNumInStock(long sn);					 //DONE		// Get number of books of given stock number in stock 
	void PrintAll();                             //DONE		// Print all items in the database

private:
	void ClearList(BookRecord *rt);              		// Recursively remove any items from the list
	bool getNextLine(char *line, int lineLen);   		// Read next line from a file
	void searchByClassification(int cl, BookRecord *rt);// Recursive search by classification
	void searchByCost(double min, double max, BookRecord *rt);// Recursive search by cost range
	void PrintAll(BookRecord *rt);               		// Recursive print all

	void checker();
	int FindBook(BookRecord* rt, long sn);
	BookRecord*searchStock(BookRecord* rt, long sn);
	BookRecord*Delete(BookRecord*& root, long stockNum);
	BookRecord*DeleteNode(BookRecord*& root);

};
