/*
        Author: Caleb Johnson
        OrderedList.h
*/

#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1

using namespace std;

template <class T>

class OrderedList
{
	
	private:
		int length; 	// number of items currently in the list
		struct Node
		{
			T Value;
			struct Node *nextNode;
		};
		Node *firstNode;
		
		/* the following prototype is for an optional function,
		 * if you don't wish for searchReturnIndex to be used, 
		 * you may comment the prototype out */
		//int searchReturnIndex(string lastName, string firstName);
		/* If there exists a student in the list with a matching 
		 * first name and matching last name (known as target), return its index
		 * otherwise, return -1 if target would be the first item
		 * and return index of highest item lower than what would be
		 * the index of the target, had the target existed in the list
		 * 
		 * Note: The term "target" is used to indicate a first and last
		 * name that a function may search for, and the student, which may 
		 * or may not exist in the list with both a matching first and last name.
		 * All searches done by this class are done by first and last name.
		 * */
	 
	public:
		/* constructer */
		OrderedList()
		{
			length = 0;
			firstNode = nullptr;
		}
		
		/* destructer */
		~OrderedList()
		{
			Node *tempNode = firstNode;
			Node *prevNode = nullptr;
			while (tempNode != nullptr)
			{
				prevNode = tempNode;
				tempNode = tempNode->nextNode;
				delete prevNode;
			}
		}
		
		T getNode(int index)
		{
			Node *tempNode = firstNode;
			int count = 0;
			while (tempNode != nullptr)
			{
				if (count == index)
				{
					return &tempNode;
				}
				else
				{
					count++;
					tempNode = tempNode->nextNode;
				}
			}
		}
		int getLength()
		{
			return length;
		}
		
		void setNode(int index, T value)
		{
			Node *tempNode = firstNode;
			int count = 0;
			while (tempNode != nullptr)
			{
				if (count == index)
				{
					tempNode.Value = value;
				}
				else
				{
					count++;
					tempNode = tempNode->nextNode;
				}
			}
		}
		
		
		bool remove(string lastName, string firstName, string(T::*toStringFunction)() const)
		{
			Node *tempNode = firstNode;
			Node *prevNode = nullptr;
			while (tempNode != nullptr)
			{
				if ((tempNode->Value.*toStringFunction)() == lastName + ", " + firstName)
				{
					if (prevNode == nullptr)
					{
						firstNode = tempNode->nextNode;
					}
					else if (tempNode->nextNode == nullptr)
					{
						prevNode->nextNode = nullptr;
					}
					else
					{
						prevNode->nextNode = tempNode->nextNode;
					}
					delete tempNode;
					length--;
					return true;
				}
				else
				{
					prevNode = tempNode;
					tempNode = tempNode->nextNode;
				}
			}
			return false;
		}
	 
		bool insert(T newItem)
		{
			Node *tempNode = new Node;
			tempNode->Value = newItem;
			tempNode->nextNode = nullptr;
			if (firstNode == nullptr)
			{
				firstNode = tempNode;
			}
			else
			{
				Node *lastNode = firstNode;
				while (lastNode->nextNode != nullptr)
				{
					lastNode = lastNode->nextNode;
				}
				lastNode->nextNode = tempNode;
			}
			length++;
			return true;
		}
	 
		T* search(string lastName, string firstName, string (T::*toStringFunction)() const)
		{
			Node *tempNode = firstNode;
			while (tempNode != nullptr)
			{
				if ((lastName + ", " + firstName) == (tempNode->Value.*toStringFunction)())
				{
					return &tempNode->Value;
				}
				else
				{
					tempNode = tempNode->nextNode;
				}
			}
			return nullptr;
		}
		 
		void traverse(string(T::*toStringFunction)() const, char (T::*letterFunction)() const)
		{

			sortByString(toStringFunction);

			Node *tempNode = firstNode;
			int count = 0;
			while (tempNode != nullptr)
			{
				cout << count + 1 << ".\t" << (tempNode->Value.*toStringFunction)() << " - " << (tempNode->Value.*letterFunction)() << endl;
				count++;
				tempNode = tempNode->nextNode;
			}
		}
		 
		void traverseByGrade(string(T::*toStringFunction)() const, double (T::*calculationFunction)() const, char (T::*letterFunction)() const)
		{
			bool finishedsorting = false;
			T temp;
			while (!finishedsorting)
			{
				finishedsorting = true;
				Node *tempNode = firstNode;
				while (tempNode->nextNode != nullptr)
				{
					string a = (tempNode->Value.*toStringFunction)();
					string b = (tempNode->nextNode->Value.*toStringFunction)();

					int comparer;
					if ((tempNode->Value.*calculationFunction)() > (tempNode->nextNode->Value.*calculationFunction)())
					{
						comparer = -1;
					}
					else if ((tempNode->Value.*calculationFunction)() < (tempNode->nextNode->Value.*calculationFunction)())
					{
						comparer = 1;
					}
					else
					{
						comparer = a.compare(b);
					}

					if (comparer > 0)
					{
						finishedsorting = false;

						temp = tempNode->Value;
						tempNode->Value = tempNode->nextNode->Value;
						tempNode->nextNode->Value = temp;
					}
					tempNode = tempNode->nextNode;
				}
			}

			Node *tempNode = firstNode;
			int count = 0;
			while (tempNode != nullptr)
			{
				cout << count + 1 << ".\t" << (tempNode->Value.*toStringFunction)() << " - " << (tempNode->Value.*letterFunction)() << endl;
				count++;
				tempNode = tempNode->nextNode;
			}

			sortByString(toStringFunction); //Sorts the list by string again, since this function sorts by grade
		}
		 
		void traverseOut(ofstream *f, double hwWeight, double qzWeight, double fxWeight, string(T::*lastNameFunction)() const, string(T::*firstNameFunction)() const, int(T::*HWFunction)(int) const, int(T::*QZFunction)(int) const, int(T::*finalExamFunction)() const)
		{
			string newRoster;
			newRoster = to_string(hwWeight) + '\n' + to_string(qzWeight) + '\n' + to_string(fxWeight) + '\n' + to_string(length) + '\n';
			Node *tempNode = firstNode;
			while (tempNode != nullptr)
			{
				newRoster += (tempNode->Value.*lastNameFunction)() + "\t" + (tempNode->Value.*firstNameFunction)();
				for (int j = 0; j < 4; j++)
				{
					int a = (tempNode->Value.*HWFunction)(j);
					newRoster += "\t" + to_string(a);
				}
				for (int j = 0; j < 4; j++)
				{
					int a = (tempNode->Value.*QZFunction)(j);
					newRoster += "\t" + to_string(a);
				}
				newRoster += "\t" + to_string((tempNode->Value.*finalExamFunction)()) + '\n';
				tempNode = tempNode->nextNode;
			}
			*f << newRoster;
		}

		void sortByString(string(T::*toStringFunction)() const)
		{
			bool finishedsorting = false;
			T temp;
			while (!finishedsorting)
			{
				finishedsorting = true;
				Node *tempNode = firstNode;
				while (tempNode->nextNode != nullptr)
				{
					string a = (tempNode->Value.*toStringFunction)();
					string b = (tempNode->nextNode->Value.*toStringFunction)();
					int comparer = a.compare(b);
					if (comparer > 0)
					{
						finishedsorting = false;

						temp = tempNode->Value;
						tempNode->Value = tempNode->nextNode->Value;
						tempNode->nextNode->Value = temp;
					}
					tempNode = tempNode->nextNode;
				}
			}
		}

		void traverseDisplayFunctions(void (T::*displayFunction)() const, string(T::*toStringFunction)() const)
		{
			sortByString(toStringFunction);

			Node *tempNode = firstNode;
			while (tempNode != nullptr)
			{
				(tempNode->Value.*displayFunction)();
				tempNode = tempNode->nextNode;
			}
		}

		void calculateAverage(double (T::*calculationFunction)() const)
		{
			double total = 0;
			Node *tempNode = firstNode;
			while (tempNode != nullptr)
			{
				total += (tempNode->Value.*calculationFunction)();
				tempNode = tempNode->nextNode;
			}
			cout << "The average grade for this class is " << total / length << endl;
		}
};

#endif
