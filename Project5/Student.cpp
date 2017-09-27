/*
        Author: W. Douglas Lafield
        Student.cpp
*/

#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

/***************************************************/

Student::Student(string lastName, string firstName, int q[], int hw[], int final, double qw, double hwW, double fxW)
{ 
	lastN = lastName;
	firstN = firstName;
	finalExam = final;
	quizWeight = qw;
	hwWeight = hwW;
	finalExamWeight = fxW;
	for(int i = 0; i < NUM_OF_HOMEWORKS; i++)
		homeWorks[i] = hw[i];
	for(int i = 0; i < NUM_OF_QUIZZES; i++)
		quizzes[i] = q[i];
} /* constructer */

/***************************************************/

Student::Student(string lastName, string firstName, double qw, double hwW, double fxW) 
{ 
	lastN = lastName;
	firstN = firstName;
	finalExam = 0;
	quizWeight = qw;
	hwWeight = hwW;
	finalExamWeight = fxW;
	for(int i = 0; i < NUM_OF_HOMEWORKS; i++)
		homeWorks[i] = 0;
	for(int i = 0; i < NUM_OF_QUIZZES; i++)
		quizzes[i] = 0;
} /* constructer -- name and scale */

/***************************************************/

Student::Student(string lastName, string firstName)
{
	lastN = lastName;
	firstN = firstName;
} /* constructer -- name only */

/***************************************************/

Student::Student(){}
Student::~Student(){}

int Student::getFinalExam() const { return finalExam; }
string Student::getFirstName() const { return firstN; }
string Student::getLastName() const { return lastN; }
void Student::setFinalExamGrade(int grade) { finalExam = grade; }

/***************************************************/

int	Student::getHWScore(int x) const
{
	return x < NUM_OF_HOMEWORKS && x >= 0 ? homeWorks[x] : 0;
} /* get homework score */

/***************************************************/

int Student::getQuizScore(int x) const
{
	return x < NUM_OF_QUIZZES && x >= 0 ? quizzes[x] : 0;
} /* get quiz score */

/***************************************************/

int Student::getTotalHW() const
{
	int ret = 0;
	for(int i = 0; i < NUM_OF_HOMEWORKS; i++)
		ret += homeWorks[i];
	return ret;
} /* get total homework score */

/***************************************************/

int Student::getTotalQuizzes() const
{
	int ret = 0;
	for(int i = 0; i < NUM_OF_QUIZZES; i++)
		ret += quizzes[i];
	return ret;
} /* get total quizzes */

/***************************************************/

void Student::setHWGrade(int x, int grade)
{
	if(x >= 0 && x < NUM_OF_HOMEWORKS)
		homeWorks[x] = grade;
} /* set homework grade */

/***************************************************/

void Student::setQuizGrade(int x, int grade)
{
	if(x >= 0 && x < NUM_OF_QUIZZES)
		quizzes[x] = grade;
} /* set quiz grade */

/***************************************************/

double Student::calculateGrade() const
{
	/* get homework portion */
	double hw = hwWeight * getTotalHW() / NUM_OF_HOMEWORKS;
	
	/* get quiz portion */
	double q = quizWeight * getTotalQuizzes() / NUM_OF_QUIZZES;
	
	/* get final exam portion */
	double fin = finalExamWeight * finalExam;
	
	/* return sum of portions */
	return hw + q + fin;
	
} /* calculate grade if nothing is dropped */

/***************************************************/

void Student::displayIfA() const
{
	if(calculateGrade() >= LOWEST_A)
		cout << toString() << endl;
} /* display if A */

/***************************************************/

void Student::displayIfB() const
{
	if (calculateGrade() >= LOWEST_B && calculateGrade() < LOWEST_A)
		cout << toString() << endl;
} /* display if B */

/***************************************************/

void Student::displayIfC() const
{
	if(calculateGrade() >= LOWEST_C && calculateGrade() < LOWEST_B)
		cout << toString() << endl;
} /* display if C */

/***************************************************/

void Student::displayIfD() const
{
	if(calculateGrade() >= LOWEST_D && calculateGrade() < LOWEST_C)
		cout << toString() << endl;
} /* display if D */

/***************************************************/

void Student::displayIfF() const
{
	if(calculateGrade() < LOWEST_D)
		cout << toString() << endl;
} /* display if F */

/***************************************************/

void Student::displayIfFail() const
{
	if(calculateGrade() < LOWEST_PASS)
		cout << toString() << endl;
} /* display if fail */

/***************************************************/

void Student::displayIfPass() const
{
	if(calculateGrade() >= LOWEST_PASS)
		cout << toString() << endl;
} /* display if pass */

/***************************************************/

string Student::toString() const
{
	return lastN + ", " + firstN;
} /* to string */

/***************************************************/

bool Student::isEqualToName(Student *s) const
{
	return lastN == s->getLastName() && firstN == s->getFirstName();
} /* is equal */

/***************************************************/

bool Student::isEqualToGrade(Student *s) const
{
	return calculateGrade() == s->calculateGrade();
} /* is equal */

/***************************************************/

bool Student::isGreaterThanName(Student *s) const
{
	if(lastN > s->getLastName())
		return true;
	if(lastN < s->getLastName())
		return false;
	return firstN > s->getFirstName();
	
} /* is greater than */
		
/***************************************************/

bool Student::isGreaterThanGrade(Student *s) const
{
	return calculateGrade() > s->calculateGrade();
} /* is greater than */
		
/***************************************************/

bool Student::isLessThanName(Student *s) const
{
	if(lastN < s->getLastName())
		return true;
	if(lastN > s->getLastName())
		return false;
	return firstN < s->getFirstName();
	
} /* is less than */

/***************************************************/

bool Student::isLessThanGrade(Student *s) const
{
	return calculateGrade() < s->calculateGrade();
} /* is less than */

/***************************************************/

char Student::letterGrade() const
{
	double score = calculateGrade();

	if(score >= LOWEST_A)
		return 'A';
	if(score >= LOWEST_B)
		return 'B';
	if(score >= LOWEST_C)
		return 'C';
	if(score >= LOWEST_D)
		return 'D';
	return 'F';
	
} /* return letter grade */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
