
#include<fstream>
#include<iostream>
using namespace std;
//this class just can read a smail file

class FileManager {
protected:
	fstream fp;
public:
	string sFileName;

	FileManager(string strInput);
	//Please Input File Name
	void saveString(string InputString);
	//Input How Many Lines Do u Want to Read
	string *readString(int iStartLines, int iEndLines);

	//get the integer of the file; if file have some letter , it will be remove
	//input how many integer in one line
	int *getInt(int numOfLine);

	// Retrurn how many lines in this file
	int getLines();

	// If you don't need this file , just use this function
	void deleteFile();

	void saveInt(int *numList, int numberOf);

private:
	int fileLines;
	// Read file and return num of Lines of this file 
	int returnLines();
};