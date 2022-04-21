#include "Book_Database.h"
#include "BookRecord.h"
#include <iostream>

using namespace std;

int main() {
	Book_Database* database = new Book_Database;
	database->readDatabase("Prog3TestPlanDataFile.txt");
	database->PrintAll();
	cout << endl;
	database->getNumInStock(678);
	cout << endl;
	database->getNumInStock(6789);
	cout << endl;
	database->getNumInStock(123);
	cout << endl;
	database->searchByStockNumber(123);
	cout << endl;
	database->searchByStockNumber(890);
	cout << endl;
	database->searchByStockNumber(10101);
	cout << endl;
	database->searchByClassification(613);
	cout << endl;
	database->searchByClassification(316);
	cout << endl;
	cout << "*****************************\n";
	database->searchByClassification(0);
	cout << "*****************************\n";
	cout << endl;
	database->searchByCost(50, 100);
	cout << endl;
	database->searchByCost(0, 50);
	cout << endl;
	database->searchByCost(100, 200);
	cout << endl;

	BookRecord* book = new BookRecord;
	book->setClassification(120);
	book->setCost(61.25);
	book->setName("Dark Nights: Metal");
	book->setNumberInStock(1);
	book->setStockNum(10000);
	database->addBook(book);
	database->PrintAll();
	cout << endl << endl;
	database->removeBook(678);
	database->PrintAll();
	cout << endl;
	database->removeBook(123);
	database->PrintAll();
	cout << endl;
	database->removeBook(890);
	database->PrintAll();
	cout << endl;

}