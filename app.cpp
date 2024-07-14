#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char*, BST*);
bool Redundant(BTNode*, Student);
int menu();

int main() {
	BST* bst1 = new BST;
	char filename[] = { "student.txt" };
	char a = 'Y';
	int order, source,id;
	Student stu;

	do {
		switch (menu()) {
		case 1: {
			if (!readFile(filename, bst1))
				cout << "Can't read " << filename << " ." << endl;
			else
				cout << "The record insert successfully." << endl << endl;
			break;
		}
		case 2: {
			if (!bst1->deepestNodes())
			{
				cout << "Can't print. Please enter 1 before start running program if you didn't enter." << endl;
			}

			break;
		}
		case 3:
		{
			cout << "Please enter the order. (1 - Ascending Order, 2 - Descending Order)" << endl;
			cin >> order;
			cout << "Please enter the source. (1 - Screen, 2 - Files)" << endl;
			cin >> source;

			bst1->display(order, source);
			break;
		}
		case 4:
		{
			cout << "Please enter the student ID" <<endl;
			cin >> id;
			stu.id = id;
			bst1->CloneSubtree(bst1, stu);
			break;
		}
		case 5: {
			if (!bst1->printLevelNodes())
				cout << "Can't print level nodes. Please enter 1 before start running program if you didn't enter." <<endl<< endl;
			break;
		}
		case 6: {
			if (!bst1->printPath()) {
				cout << "Can't print. Please enter 1 before start running program if you didn't enter." << endl << endl;
			}
			break;
		}
		case 7: {
			cout << "Program Ended." << endl;
			return 0;
			break;
		}
		default:
			cout << "Please enter again. " <<endl<< endl;
			break;
		}
	} while (a == 'Y');

	system("pause");
	return 0;
}
bool readFile(const char* filename, BST* bst1) {
	ifstream infile(filename);
	Student stu;
	string dm;
	BTNode* find = bst1->root;
	if (infile.fail())
		return false;

	while (!infile.eof()) {
		for (int a = 0; a < 3; a++)
			infile >> dm;
		infile >> stu.id;
		for (int b = 0; b < 2; b++)
			infile >> dm;
		infile.getline(stu.name, 30);
		for (int c = 0; c < 2; c++)
			infile >> dm;
		infile.getline(stu.address, 100);
		for (int d = 0; d < 2; d++)
			infile >> dm;
		infile >> stu.DOB;
		for (int e = 0; e < 3; e++)
			infile >> dm;
		infile >> stu.phone_no;
		for (int f = 0; f < 2; f++)
			infile >> dm;
		infile >> stu.course;
		for (int g = 0; g < 2; g++)
			infile >> dm;
		infile >> stu.cgpa;

		if (!Redundant(find, stu)) {
			bst1->insert(stu);
		}
		else
			cout << stu.id << " are insert in BST list." << endl;
	}

	infile.close();
	return true;

}

bool Redundant(BTNode* find, Student student) { //check redundant from the root to leaf

	if (find == NULL)
		return false;

	if (find->item.id == student.id) //if the id existed will return true
		return true;
	if (Redundant(find->left, student))
		return true;
	return Redundant(find->right, student);

}

int menu() {

	int a;
	cout << "(1) Read data to BST " << endl;
	cout << "(2) Print deepest nodes " << endl;
	cout << "(3) Display student" << endl;
	cout << "(4) Clone Subtree  " << endl;
	cout << "(5) Print Level Nodes " << endl;
	cout << "(6) Print Path " << endl;
	cout << "(7) Exit " << endl;
	cout << "Enter your choice (1-6):";
	cin >> a;
	cout << endl;
	return  a;

}