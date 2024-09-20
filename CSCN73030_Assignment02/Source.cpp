/*******************************************************************
*	Assignment 01:		Debugging vs. Release Coding Practice
*	Course:				CSCN73030-24F
*	Section:			2
*	Professor:			Sara-Ross Howe
*	Author:				Hangsihak Sin
*	Date:				September/19/2024
* *******************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define PRE_RELEASE

#ifdef PRE_RELEASE
#define STU_DATA_FILE "../StudentData_Emails.txt"
#else 
#define STU_DATA_FILE "../StudentData.txt"
#endif // PRE_RELEASE

#define DELIMINATOR ','

// a struct to hold student data
typedef struct STUDENT_DATA {
	string firstName;
	string lastName;
#ifdef PRE_RELEASE
	string email;
#endif // PRE_RELEASE

}STUDENT_DATA;

// A helper function to parse student data from file
bool parseStudentDataFromFile(string fileName, vector<STUDENT_DATA>& studentDataList) {

	// open the student data file
	ifstream myFile(STU_DATA_FILE);

	// Validate if the file can be opened
	if (!myFile.is_open()) {
		cout << "Unable to open the file " << STU_DATA_FILE << endl;
		return false;
	}

	string studentLine;

	// read student data file line by line
	while (getline(myFile, studentLine)) {
		STUDENT_DATA tempStudentData;	// create STUDENT_DATA object
		istringstream iss(studentLine);
		// parse first and last name that is separated by a comma (deliminator)
		getline(iss, tempStudentData.firstName, DELIMINATOR);
		getline(iss, tempStudentData.lastName, DELIMINATOR);
#ifdef PRE_RELEASE
		getline(iss, tempStudentData.email, DELIMINATOR);
#endif // PRE_RELEASE

		// add the parsed student data to the vector
		studentDataList.push_back(tempStudentData);
	}

	// close the file after use
	myFile.close();

	return true;
}

#ifdef _DEBUG	// print student data from vector - only for Debug Mode
void printStudentDataFromVector(vector<STUDENT_DATA> studentDataList) {

	for (int i = 0; i < studentDataList.size(); i++) {
		cout << studentDataList[i].lastName << ", " << studentDataList[i].firstName;
#ifdef PRE_RELEASE
		cout << ", " << studentDataList[i].email << endl;
#else
		cout << endl;
#endif // PRE_RELEASE
	}
}
#endif // DEBUG

int main(void) {
#ifdef PRE_RELEASE
	cout << "This application is running on pre-release source code" << endl;
#else
	cout << "This application is running on standard source code" << endl;
#endif // PRE_RELEASE

	// vector to store list of student data
	vector<STUDENT_DATA> studentDataList;

	// parse student data from the text file
	parseStudentDataFromFile(STU_DATA_FILE, studentDataList);

#ifdef _DEBUG	// print student data from vector - only for Debug Mode
	printStudentDataFromVector(studentDataList);
#endif // DEBUG

}