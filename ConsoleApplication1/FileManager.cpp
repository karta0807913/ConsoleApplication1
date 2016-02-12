#include"FileManager.h"

FileManager::FileManager(string strInput)
{
	//the file name
	sFileName = strInput;
	fileLines = returnLines();
}
void FileManager::saveString(string InputString)
{
	//save string
	fp.open(sFileName, ios::out | ios::app);
	//	InputString += '\n';
		/**************************************************************************************
		*							Actually it needless									  *
		*																					  *
		* int num = 100;																	  *
		* //Let int to char*																  *
		* fp.write(reinterpret_cast<const char *>(&num), sizeof(num)); //Write A Value		  *
		*																					  *
		***************************************************************************************/
	fp.write(InputString.c_str(), strlen(InputString.c_str()));
	fp.close();

	fileLines = returnLines();
}

string* FileManager::readString(int iStartLines, int iEndLines)
{
	if (iEndLines < iStartLines)
	{
		int x = iStartLines;
		iStartLines = iEndLines;
		iEndLines = x;
	}

	if (iEndLines > fileLines)
		return 0;
	fp.open(sFileName, ios::in);
	//read Array

	string *read = new string[iEndLines - iStartLines];

	for (int i = 0; i < iEndLines; i++) {
		if (i >= iStartLines)
		{
			char *tmp = new char[1000];
			fp.getline(tmp, 1000, '\n');
			*(read + i - iStartLines) = string(tmp);
			delete[] tmp;
		}
	}
	fp.close();
	return read;
}

int * FileManager::getInt(int numOfLine)
{
	string *chars; //save the file on this char pointer
	chars = readString(0, fileLines); // get the file
	int numOfArray = numOfLine * fileLines; // Preset one line have 'numOfLine' integer
	int *num = new int[numOfArray];
	int num_counter = 0; // to save how many integer had saved
	string str = ""; // it must be optimization
	for (int i = 0; i < fileLines; i++)
	{
		for (int o = 0; o < 100; o++) {
			// a integer is divided by a space
			// if chars equals '\0'((int)0) that means this line was end
			if (chars[i][o] == ' ' || chars[i][o] == '\0')
			{
				num[num_counter] = 0;
				// let a string to integer
				int length = str.size();
				for (int i = 0; i < length; i++)
				{
					num[num_counter] *= 10;
					num[num_counter] += str[i] - '0';
				}

				num_counter++;
				str = "";

				if (chars[i][o] == '\0')
				{
					o = 0;
					break;
				}
				o++;
			}
			// if chars is a number
			if (chars[i][o] >= '0' && chars[i][o] <= '9')
				str += chars[i][o];
		}
	}
	return num;
}

int FileManager::getLines()
{
	return fileLines;
}

void FileManager::deleteFile() {
	remove(sFileName.c_str());
	fileLines = returnLines();
}

void FileManager::saveInt(int * numList, int numberOf)
{
	string str = "";
	for (int i = 0; i < numberOf; i++) {
		int iDigit = 100000;
		bool haveNumber = false;
		do {
			if (numList[i] / iDigit != 0 || haveNumber) {
				str += (numList[i] / iDigit + '0');
				numList[i] %= iDigit;
				haveNumber = true;
			}
			iDigit /= 10;
		} while (iDigit != 0 && (haveNumber || numList[i] != 0));
		if (!haveNumber)
			str += '0';
		str += ' ';
	}

	//	str[str.size() - 1] = '\n';
	str += '\0';
	saveString(str);
}

int FileManager::returnLines()
{
	fp.open(sFileName, ios::in);
	//how many lines in this file , use '\n' to identify
	__int64 i64Lines = count(istreambuf_iterator<char>(fp), istreambuf_iterator<char>(), '\n');
	fp.close();
	int returnInt = static_cast<int>(i64Lines);
	return returnInt;
}

