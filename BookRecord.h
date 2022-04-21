#pragma once
#pragma once
#pragma once
#pragma warning(disable : 4996)

class BookRecord {
private:
	//name of a book or periodical
	char m_sName[128];
	//unique stock number for the book or periodical
	long m_lStockNum;
	//specific information about the book or periodical
	int m_iClassification;
	//cost of this book or periodical
	double m_dCost;
	//number of copies of this item currently in the inventory
	int m_iCount;


public:

	BookRecord* m_pLeft;
	BookRecord* m_pRight;
	//Constructor
	BookRecord();
	//Constructor 2
	BookRecord(const char *name, long sn, int cl, double cost);//yes
	//Destructor
	~BookRecord();
	//This function will copy the member variable m_sName into the character array pointed to by the function argument
	void getName(char *name);
	//This function will copy the function argument into the member variable m_sName
	void setName(const char *name);
	//This function will return the value stored in the variable m_lStockNum
	long getStockNum();
	//This function will copy the argument into the member variable m_lStockNum
	void setStockNum(long sn);
	//This function will copy the variable m_iClassification into the integer variable referenced by the function 
	void getClassification(int& cl);
	//This function will copy the function argument into the variable m_iClassification
	void setClassification(int cl);
	//This function will copy the variable m_dCost into the double variable pointed to the function argument
	double getCost();
	//This function will copy the function argument into the member variable m_dCost
	void setCost(double c);
	//This function will return the value stored in m_iCount
	int getNumberInStock();
	//This function will copy the argument into the member variable m_iCount
	void setNumberInStock(int count);
	//This function will print out the contents of the library to the screen
	void printRecord();//yes
};



