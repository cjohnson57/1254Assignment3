/*
        Author: Caleb Johnson
        main.cpp
*/

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include "Student.h"
#include "OrderedList.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define EXIT_CHOICE 11

using namespace std;

/***************************************************/

int menu(void);

/***************************************************/

int main(int argc, char** argv)
{
	//argc = 2; //For testing
	if(argc < 2)
	{
		cout << "You must enter a filename by command line." << endl;
		cout << "The command should be as follows:" << endl;
		cout << argv[0] << " [file containing roster]." << endl;
		return 0;
	}
	
	OrderedList<Student> *l = new OrderedList<Student>;
	
	/* read file */
	ifstream f;
	f.open(argv[1]); //should be argv[1], for testing "C:\\Users\\Caleb\\Desktop\\1254 Projects\\prog3\\testRoster.txt"
	if(!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}
	
	double hwWeight, qzWeight, fxWeight;
	int numInRoster;
	string tempS;
	
	f >> hwWeight >> qzWeight >> fxWeight >> numInRoster;

	for(int x = 0; x < numInRoster; x++)
	{ /* go through each student in roster */
		
		int tempHw[4];
		int tempQz[4];
		int tempFx;
		string tempFn;
		string tempLn;
		f >> tempLn >> tempFn;
		for(int i = 0; i < 4; i++)
			f >> tempHw[i];
		for(int i = 0; i < 4; i++)
			f >> tempQz[i];
		f >> tempFx;
		
		Student *tempStudent = new Student(tempLn, tempFn, tempQz, tempHw, tempFx, qzWeight, hwWeight, fxWeight);
		l->insert(*tempStudent);
		
	} /* go through each student in roster */
	
	f.close();
	
	int choice = menu();
	
	while(choice != EXIT_CHOICE)
	{
		if(choice == 1)
		{ /* search */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			/* search */
			Student *s = l->search(lastN, firstN, &Student::toString);
			
			if(s != nullptr && s->getFirstName() == firstN && s->getLastName() == lastN)
			{
				cout << "\n\n\n" << s->toString() << "\tHw total: " << s->getTotalHW() << "\tQz total: " << s->getTotalQuizzes() << "\tFinal exam: " << s->getFinalExam() << "\tGrade: " << s->calculateGrade() << " " << s->letterGrade() << endl;
				cout << "Hmwk:\t\t\tQuiz" << endl;
				for(int i = 0; i < MIN(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS); i++)
					cout << s->getHWScore(i) << "\t\t\t" << s->getQuizScore(i) << endl;
				for(int i = MIN(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS) + 1; i < MAX(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS); i++)
					cout << s->getHWScore(i) << "\t\t\t" << s->getQuizScore(i) << endl;
				cout << "Final Exam: " << s->getFinalExam() << "\n\n\n";
			}
			else
				cout << "No student with the name " << lastN << ", " << firstN << " was found" << endl;

		} /* search */
		
		if(choice == 2)
		{ /* insert */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			Student *s = l->search(lastN, firstN, &Student::toString);
			
			if(s != nullptr && s->getFirstName() == firstN && s->getLastName() == lastN)
				cout << "The student " << lastN << ", " << firstN << " already exists in the roster" << endl;
			else
			{ /* student not found, so insert */

				int tempHw[4];
				int tempQz[4];
				int tempFx;
				for(int i = 0; i < 4; i++)
				{
					cout << "Enter grade for homework " << i + 1 << ": ";
					cin >> tempHw[i];
				}
				
				for(int i = 0; i < 4; i++)
				{
					cout << "Enter grade for quiz " << i + 1 << ": ";
					cin >> tempQz[i];
				}
				
				cout << "Enter final exam grade: ";
				cin >> tempFx;
				
				/* insert */
				Student *tempStudent = new Student(lastN, firstN, tempQz, tempHw, tempFx, qzWeight, hwWeight, fxWeight);
				if(l->insert(*tempStudent))
					cout << "New student added" << endl;
				else
					cout << "WARNING!!!  Student add failed." << endl;

			} /* student not found, so insert */
				
		} /* insert */
		
		if(choice == 3)
		{ /* remove */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			/* delete it */
			if(l->remove(lastN, firstN, &Student::toString))
				cout << "Student deleted" << endl;
			else
				cout << "No student with the name " << lastN << ", " << firstN << " was found" << endl;
		} /* remove */

		if(choice == 4)
			cout << "There are " << l->getLength() << " items in the list." << endl;
			
		if(choice == 5)
		{
			cout << "-----Begin List-----" << endl;
			l->traverse(&Student::toString, &Student::letterGrade);
			cout << "-----End List-----" << endl;
		}
		
		if(choice == 6)
		{
			cout << "-----Begin List-----" << endl;
			l->traverseByGrade(&Student::toString, &Student::calculateGrade, &Student::letterGrade);
			cout << "-----End List-----" << endl;
		}

		if (choice == 7)
		{
			cout << "-----Begin List-----" << endl;
			l->traverseDisplayFunctions(&Student::displayIfPass, &Student::toString);
			cout << "-----End List-----" << endl;
		}

		if (choice == 8)
		{
			cout << "-----Begin List-----" << endl;
			l->traverseDisplayFunctions(&Student::displayIfFail, &Student::toString);
			cout << "-----End List-----" << endl;
		}

		if (choice == 9)
		{
			char letter;
			while (true)
			{
				cout << "Please enter the grade (A-F):";
				cin >> letter;
				if (letter == 'A' || letter == 'B' || letter == 'C' || letter == 'D' || letter == 'F')
				{
					break;
				}
				else
				{
					cout << "\"" << letter << "\"" << " is not a valid grade" << endl;
				}
			}
			cout << "-----Begin List-----" << endl;
			void(Student::*foo)() const;
			switch (letter)
			{
				case 'A':
				{
					foo = &Student::displayIfA;
					break;
				}
				case 'B':
				{
					foo = &Student::displayIfB;
					break;
				}
				case 'C':
				{
					foo = &Student::displayIfC;
					break;
				}
				case 'D':
				{
					foo = &Student::displayIfD;
					break;
				}
				case 'F':
				{
					foo = &Student::displayIfF;
					break;
				}
			}
			l->traverseDisplayFunctions(foo, &Student::toString);
			cout << "-----End List-----" << endl;
		}

		if (choice == 10)
		{
			cout << "-----Begin List-----" << endl;
			l->calculateAverage(&Student::calculateGrade);
			cout << "-----End List-----" << endl;
		}

		choice = menu();
	}
	
	/* update file */
	ofstream g;
	g.open(argv[1]); //should be argv[1], for testing "C:\\Users\\Caleb\\Desktop\\1254 Projects\\prog3\\testRoster.txt"
	l->traverseOut(&g, hwWeight, qzWeight, fxWeight, &Student::getLastName, &Student::getFirstName, &Student::getHWScore, &Student::getQuizScore, &Student::getFinalExam);
	g.close();
	delete l;
	cout << "Done." << endl;
	
	return 0;
} /* main */

/***************************************************/

int menu(void)
{
	int choice;
	
	
	while(true)
	{
		cout << "1: Search" << endl;
		cout << "2: Insert" << endl;
		cout << "3: Delete" << endl;
		cout << "4: Count" << endl;
		cout << "5: List all students by name" << endl;
		cout << "6: List all students by grade" << endl;
		cout << "7: List all passing students" << endl;
		cout << "8: List all failing students" << endl;
		cout << "9: List all students by letter grade" << endl;
		cout << "10: Get average grade for the whole class" << endl;
		cout << "11: exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		if(choice >= 1 && choice <= EXIT_CHOICE)
			return choice;
		cout << "\"" << choice << "\" is not a valid option" << endl;
		
	} /* repeat until return */
	
} /* menu */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
