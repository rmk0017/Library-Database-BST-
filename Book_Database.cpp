#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include"Book_Database.h"
#include <iomanip>

//--------------------------------------------
// Function: readDatabase()
// Purpose: Read the inventory data file and
//		build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Database::readDatabase(const char *filename)
{
	char     line[128];
	int      numBooks;
	// define other variables here as needed

	m_InFile.open(filename, ifstream::in);
	if (!m_InFile.is_open())
	{
		// m_InFile.is_open() returns false if the file could not be found or
		//    if for some other reason the open failed.
		cout << "Unable to open file" << filename << "\nProgram terminating...\n";
		return false;
	}
	// Read number of books
	getNextLine(line, 128);
	numBooks = atoi(line);
	for (int i = 0; i < numBooks; i++)
	{
		// ------------------------------------------
		// Your code to read the database goes here
		// ------------------------------------------

		BookRecord *temp = new BookRecord;
		long stock;
		int classification;
		double cost;
		int count;

		getNextLine(line, 128);
		stock = atoi(line);
		temp->setStockNum(stock);
		getNextLine(line, 128);
		temp->setName(line);
		getNextLine(line, 128);
		classification = atoi(line);
		temp->setClassification(classification);
		getNextLine(line, 128);
		cost = atof(line);
		temp->setCost(cost);
		getNextLine(line, 128);
		count = atoi(line);
		temp->setNumberInStock(count);
		addBook(temp);
	}
	return true;
}
//--------------------------------------------
// Function: getNextLine() 
// Purpose:  Read a line from a data file.
//   The next non-comment line read from file
//   is stored in line char array.
//   An empty string is stored if the end of
//   file is reached.
// Returns: bool - true if a valid line was
//   read, false if end of file is reached. 
//--------------------------------------------
bool Book_Database::getNextLine(char *line, int lineLen)
{
	int    done = false;
	while (!done)
	{
		m_InFile.getline(line, lineLen);

		if (m_InFile.good())    // If a line was successfully read
		{
			if (strlen(line) == 0)  // Skip any blank lines
				continue;
			else if (line[0] == '#')  // Skip any comment lines
				continue;
			else return true;    // Got a valid data line so return with this line
		}
		else // No valid line read, meaning we reached the end of file
		{
			strcpy(line, ""); // Copy empty string into line as sentinal value
			return false;
		}
	} // end while
	return false; // Cannot reach this point but include a return to avoid compiler warning
				  //   that not all paths return a value.
}

Book_Database::Book_Database() {
	m_pRoot = NULL;
	found = false;
}

Book_Database::~Book_Database() {
	ClearList(m_pRoot);
}

void Book_Database::PrintAll() {
	PrintAll(m_pRoot);
}

void Book_Database::searchByClassification(int cl) {
	found = false;
	searchByClassification(cl, m_pRoot);
	if (found == false) {
		cout << "Error: Book(s) with given classification not found" << endl;
	}
}



BookRecord*Book_Database::searchByStockNumber(long sn) {
	found = false;
	BookRecord* temp = new BookRecord;

	temp = searchStock(m_pRoot, sn);
	if (found == true) {
		return temp;
	}
	else {
		cout << "***********************\n";
		cout << "Error: No book found\n";
		cout << "***********************\n";
	}
}

BookRecord*Book_Database::searchStock(BookRecord* rt, long sn) {
	if (sn == rt->getStockNum()) {
		rt->printRecord();
		checker();
		return rt;
	}
	else if (sn < rt->getStockNum()) {
		if (rt->m_pLeft == nullptr) {
			cout << "";
		}
		else {
			searchStock(rt->m_pLeft, sn);
		}
	}
	else if (sn > rt->getStockNum()) {
		if (rt->m_pRight == nullptr) {
			cout << "";
		}
		else {
			searchStock(rt->m_pRight, sn);
		}
	}
}
//All the recursive functions:::::
void Book_Database::PrintAll(BookRecord *br) {
	if (br->m_pLeft != NULL) {
		PrintAll(br->m_pLeft);
	}

	br->printRecord();

	if (br->m_pRight != NULL) {
		PrintAll(br->m_pRight);
	}
}



void Book_Database::searchByCost(double min, double max) {
	found = false;
	searchByCost(min, max, m_pRoot);
	if (found == false) {
		cout << "************************************************\n";
		cout << "Error: No book was found within the cost range\n";
		cout << "************************************************\n";
	}
}

void Book_Database::searchByCost(double min, double max, BookRecord* rt) {
	double nodeCost = rt->getCost();
	if (rt == NULL) {
		cout << "Error: The BST is empty!\n";
	}
	else if ((nodeCost >= min) && (nodeCost <= max)) {
		rt->printRecord();
		checker();
	}

	if (rt->m_pLeft != NULL) {
		searchByCost(min, max, rt->m_pLeft);
	}
	if (rt->m_pRight != NULL) {
		searchByCost(min, max, rt->m_pRight);
	}
}

void Book_Database::searchByClassification(int cl, BookRecord *rt) {
	int BookClass;
	rt->getClassification(BookClass);

	if (rt == NULL) {
		cout << "Error: Book(s) with given classification not found";
	}
	else if (cl == BookClass) {
		rt->printRecord();
		checker();
	}

	if (rt->m_pLeft != NULL) {
		searchByClassification(cl, rt->m_pLeft);
	}

	if (rt->m_pRight != NULL) {
		searchByClassification(cl, rt->m_pRight);
	}
}

void Book_Database::ClearList(BookRecord *br) {
	if (br->m_pLeft != NULL) {
		ClearList(br->m_pLeft);
	}
	delete br;
	if (br->m_pRight != NULL) {
		ClearList(br->m_pRight);
	}
}

void Insert(BookRecord*& tree, BookRecord* a);

bool Book_Database::addBook(BookRecord* br) {
	Insert(m_pRoot, br);
	return true;
}

void Insert(BookRecord*& root, BookRecord* a) {
	if (root == NULL) {
		int classification;
		a->getClassification(classification);
		char str[128];
		a->getName(str);
		root = new BookRecord;
		root->m_pLeft = NULL;
		root->m_pRight = NULL;
		root->setClassification(classification);
		root->setCost(a->getCost());
		root->setName(str);
		root->setNumberInStock(a->getNumberInStock());
		root->setStockNum(a->getStockNum());
	}
	else if (root->getStockNum() > a->getStockNum()) {
		Insert(root->m_pLeft, a);
	}
	else if (root->getStockNum() < a->getStockNum()) {
		Insert(root->m_pRight, a);
	}
}

void Book_Database::checker() {
	found = true;
}

int Book_Database::getNumInStock(long sn) {
	int count;
	found = false;
	count = FindBook(m_pRoot, sn);
	if (found == true) {
		return count;
	}
	else {
		cout << "******************************************************\n";
		cout << "Error: No Book was found for the given stock number\n";
		cout << "******************************************************\n";
	}
}

int Book_Database::FindBook(BookRecord* rt, long sn) {
	int BookStockNum;
	BookStockNum = rt->getStockNum();
	int count = 0;
	if (sn == BookStockNum) {
		cout << "Number of Books in Stock: " << rt->getNumberInStock() << endl;
		count = rt->getNumberInStock();
		checker();
		return count;
	}
	else if (sn < BookStockNum) {
		if (rt->m_pLeft == NULL) {
			return count;
		}
		else {
			FindBook(rt->m_pLeft, sn);
		}
	}
	else if (sn > BookStockNum) {
		if (rt->m_pRight == NULL) {
			return count;
		}
		else {
			FindBook(rt->m_pRight, sn);
		}
	}
}

void GetPredecessor(BookRecord* root, BookRecord* data); //To find rightmost node in the subtree

BookRecord*Book_Database::removeBook(long stockNum){
	found = false;
	BookRecord* temp = new BookRecord;
	temp = Delete(m_pRoot, stockNum);
	if (found == true) {
		return temp;
	}
	else {
		cout << "Error: A book was not found\n";
	}
}

BookRecord*Book_Database::Delete(BookRecord*& root, long stockNum) {
		if (stockNum < root->getStockNum()) {
			Delete(root->m_pLeft, stockNum);
		}
		else if (stockNum > root->getStockNum()) {
			Delete(root->m_pRight, stockNum);
		}
		else if (stockNum == root->getStockNum()) {
			checker();
			return DeleteNode(root);
		}
}

BookRecord*Book_Database::DeleteNode(BookRecord*& root) {
	BookRecord* data = new BookRecord;
	BookRecord* temp;

	temp = root;
	if (root->m_pLeft == NULL) {
		root = root->m_pRight;
		return temp;
		delete temp;
	}
	else if (root->m_pRight == NULL) {
		root = root->m_pLeft;
		return temp;
		delete temp;
	}
	else {
		GetPredecessor(root->m_pLeft, data);
		int classification;
		data->getClassification(classification);
		char str[128];
		data->getName(str);
		root->setClassification(classification);
		root->setCost(data->getCost());
		root->setName(str);
		root->setNumberInStock(data->getNumberInStock());
		root->setStockNum(data->getStockNum());
		Delete(root->m_pLeft, data->getStockNum());
	}
}

void GetPredecessor(BookRecord* root, BookRecord* data) {
	while (root->m_pRight != NULL) {
		root = root->m_pRight;
	}
	int classification;
	root->getClassification(classification);
	char str[128];
	root->getName(str);
	data->setClassification(classification);
	data->setCost(root->getCost());
	data->setName(str);
	data->setNumberInStock(root->getNumberInStock());
	data->setStockNum(root->getStockNum());
}



