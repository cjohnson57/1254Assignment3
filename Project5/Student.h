/*
	Author: W. Douglas Lafield
	Student.h
*/
#ifndef _STUDENT_GUARD
#define _STUDENT_GUARD 1
#define NUM_OF_QUIZZES 4
#define NUM_OF_HOMEWORKS 4
#define LOWEST_A 90
#define LOWEST_B 80
#define LOWEST_C 70
#define LOWEST_D 60
#define LOWEST_PASS LOWEST_D

#include <iostream>
#include <ostream>

using namespace std;

class Student
{
	private:
		string lastN;
		string firstN;
		int quizzes[NUM_OF_QUIZZES];
		int homeWorks[NUM_OF_HOMEWORKS];
		int finalExam;
		/* weights are all between 0.0 and 1.0, and should all add up to 1.0 */
		double quizWeight;
		double hwWeight;
		double finalExamWeight;
	public:
		/* constructer */
		Student(string lastName, string firstName, int q[], int hw[], int final, double qw, double hwW, double fxW);
		
		/* constructer -- name and weights */
		Student(string lastName, string firstName, double qw, double hwW, double fxW);
		
		/* constructer -- name only */
		Student(string lastName, string firstName);
		
		/* generic constructer */
		Student();
		
		/* destructer */
		~Student();

		int 	getFinalExam() const;
		/* returns the grade for the final exam */
		
		string 	getFirstName() const;
		/* returns the student's first name */
		
		int 	getHWScore(int x) const;
		/* returns the student's score for the x-th homework assignment */
		
		string 	getLastName() const;
		/* returns the student's last name */
		
		int 	getQuizScore(int x) const;
		/* returns the student's score for the x-th quiz */
		
		int 	getTotalHW() const;
		/* returns the sum total of the student's homework scores */
		
		int 	getTotalQuizzes() const;
		/* returns the sum total of the student's quiz scores */

		void setFinalExamGrade(int grade);
		/* sets the student's score for the final exam */
		
		void setHWGrade(int x, int grade);
		/* sets the student's score for the x-th homework assignment */
		
		void setQuizGrade(int x, int grade);
		/* sets the student's score for the x-th quiz */
		
		double calculateGrade() const;
		/* calculates the student's grade */
		
		void displayIfA() const;
		/* if the student has an A, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfB() const;
		/* if the student has a B, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfC() const;
		/* if the student has a C, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfD() const;
		/* if the student has a D, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfF() const;
		/* if the student has an F, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfFail() const;
		/* if the fails the class, then display the student's name 
		 * otherwise, do nothing */
		 
		void displayIfPass() const;
		/* if the passes the class, then display the student's name 
		 * otherwise, do nothing */
		 
		bool isEqualToName(Student *s) const;
		/* return true if the student has the same name as *s
		 * otherwise, return false */
		 
		bool isEqualToGrade(Student *s) const;
		/* return true if the student has the same grade as *s
		 * otherwise, return false */
		
		bool isGreaterThanName(Student *s) const;
		/* return true if the student would appear after *s in 
		 * lexicographical order by their last and first names
		 * otherwise, return false */
		 
		bool isGreaterThanGrade(Student *s) const;
		/* return true if the student's grade is greater than the grade of *s
		 * otherwise, return false */
		 
		bool isLessThanName(Student *s) const;
		/* return true if the student would appear before *s in 
		 * lexicographical order by their last and first names
		 * otherwise, return false */
		 
		bool isLessThanGrade(Student *s) const;
		/* return true if the student's grade is less than the grade of *s
		 * otherwise, return false */

		char letterGrade() const;
		/* return the student's letter grade */
		
		string toString() const;
		/* show the studen't name with the last name first, followed by
		 * the first name, each separated by a comma */
};

#endif
