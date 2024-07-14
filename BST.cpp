#include <iostream>
#include <fstream>
#include <algorithm>
#include	<string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::deepestNodes()
{
	int height, curheight;
	BTNode* cur = root;

	if (cur == NULL)
	{
		cout << "Tree is empty" << endl << endl;
		return false;
	}

	//using findHeight function to get the height of tree
	height = findHeight(cur);

	printDeepestNodes(root, height, 1);

	return true;
}

int BST::findHeight(BTNode* cur)
{
	int left_height, right_height;

	if (cur == NULL)
		return 0;

	left_height = findHeight(cur->left);
	right_height = findHeight(cur->right);

	if (left_height > right_height)
		return left_height + 1;

	else
		return right_height + 1;
}


void BST::printDeepestNodes(BTNode* cur, int height, int curheight)
{
	if (cur == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}

	if (height == curheight)
	{
		cout << cur->item.id << " is the deepest student node."<<endl << endl;
		return;

	}

	if (cur->left != NULL)
		printDeepestNodes(cur->left, height, curheight + 1);

	if (cur->right != NULL)
		printDeepestNodes(cur->right, height, curheight + 1);
}

bool BST::display(int order, int source)
{

	ofstream OutFile;
	OutFile.open("student-info.txt");

	if (empty())
	{
		cout << "This tree is empty!" << endl;
		return false;
	}

	if (order == 1) //in order
	{
		if (source == 1) // print out
		{
			inOrderPrint();
		}
		else if (source == 2) //print into Oufile
		{
			inOrderPrintOutFile(OutFile);
			cout << "Sucessfully inserted into student-info.txt." << endl << endl;
		}
		else
		{
			cout << "Error typing! " << endl;
			return false;
		}
	}

	else if (order == 2) // ReverseInOrder
	{
		if (source == 1) // print out
		{
			ReverseinOrderPrint();
		}
		else if (source == 2) //print into Oufile
		{
			ReverseinOrderPrintOutFile(OutFile);
			cout << "Sucessfully inserted into student-info.txt." << endl << endl;
		}
		else
		{
			cout << "Error typing! " << endl;
			return false;
		}
	}

	else
	{
		cout << "Error typing!" << endl;
		return false;
	}

	OutFile.close();
	return true;

}
//inOrder into file
void BST::inOrderPrint2OutFile(BTNode* cur, ofstream& OutFile)
{

	if (cur == NULL) return;

	inOrderPrint2OutFile(cur->left, OutFile);
	cur->item.print(OutFile);
	inOrderPrint2OutFile(cur->right, OutFile);
}

void BST::inOrderPrintOutFile(ofstream& OutFile)
{
	if (root == NULL) return;// handle special case
	else inOrderPrint2OutFile(root, OutFile);// do normal process
	cout << endl;
}

//ReverseOrder print
void BST::ReverseinOrderPrint2(BTNode* cur)
{

	if (cur == NULL) return;

	ReverseinOrderPrint2(cur->right);
	cur->item.print(cout);
	ReverseinOrderPrint2(cur->left);
}
void BST::ReverseinOrderPrint()
{
	if (root == NULL) return;// handle special case
	else ReverseinOrderPrint2(root);// do normal process
	cout << endl;
}

//ReverseinOrder into file
void BST::ReverseinOrderPrint2OutFile(BTNode* cur, ofstream& OutFile)
{

	if (cur == NULL) return;

	ReverseinOrderPrint2OutFile(cur->right, OutFile);
	cur->item.print(OutFile);
	ReverseinOrderPrint2OutFile(cur->left, OutFile);
}

void BST::ReverseinOrderPrintOutFile(ofstream& OutFile)
{
	if (root == NULL) return;// handle special case
	else ReverseinOrderPrint2OutFile(root, OutFile);// do normal process
	cout << endl;
}

BTNode* BST::Find(type a)
{
	if (root == NULL)
	{
		return nullptr;// handle special case
	}

	return Find2(root, a); // do normal process
}


BTNode* BST::Find2(BTNode* cur, type a)
{
	int result;
	if (cur == NULL)
	{
		return nullptr;
	}
	result = cur->item.compare2(a);
	if (result == 1)
	{
		return cur; // Item found, return the current node
	}
	else if (result == 0)
	{
		BTNode* leftResult = Find2(cur->left, a);
		if (leftResult != nullptr)
		{
			return leftResult; // Item found in the left subtree, return it
		}

		return Find2(cur->right, a); // Item found in the right subtree, return it (or nullptr)
	}
}


bool BST::CloneSubtree(BST* t1, type item)
{
	if (t1->empty())  //empty tree
	{
		cout << "Cannot clone subtree." << endl;
		return false;
	}

	BTNode* rootToClone = t1->Find(item);

	if (rootToClone == nullptr)
	{
		cout << "Item not found for cloning." << endl << endl;
		return false;
	}

	BST t2;

	// Clone the subtree starting from the root
	cloneSubtree2(rootToClone, t2);

	// Display t1 and t2 after cloning
	cout << "Original Tree (t1):" << endl;
	t1->preOrderPrint();

	cout << "Cloned Subtree (t2):" << endl;
	t2.preOrderPrint();

	return true;
}



void BST::cloneSubtree2(BTNode* rootToClone, BST& t2)
{

	if (rootToClone == nullptr)
	{
		return; // Base case: empty subtree, nothing to clone
	}

	// Clone the current node and insert it into t2
	t2.insert(rootToClone->item);

	// Recursively clone the left and right subtrees
	cloneSubtree2(rootToClone->left, t2);
	cloneSubtree2(rootToClone->right, t2);
}

bool BST::printLevelNodes()
{
	BTNode* cur = root;
	Queue q1;
	int level = 1;


	if (root == NULL)
	{
		cout << "The tree is empty" << endl;
		return false;
	}

	q1.enqueue(cur);

	while (!q1.empty())
	{
		int qsize = q1.size();

		cout << "Level " << level << " nodes: " << endl;

		//using queue size to get the number of nodes in each level
		for (int i = 0; i < qsize; i++)
		{
			q1.dequeue(cur);

			if (cur != NULL)
			{
				cout << cur->item.id << " ";

				if (cur->left != NULL)
					q1.enqueue(cur->left);

				if (cur->right != NULL)
					q1.enqueue(cur->right);
			}
		}
		cout << endl << endl;
		level++;
	}
	return true;
}

bool BST::printPath() {

	BTNode* cur = root;

	if (empty())
		return false;

	else {
		cout << "Below are all the external path of tree: " << endl ;
		printTree(cur,""); //pass in the root and an empty string
		cout << endl;
		return true;
	}


}

void BST::printTree(BTNode* root, string a) {

	if (root == NULL)
		return;

	a += to_string(root->item.id) + " "; //convert the integer ID in root to string form, add with spacing and save to string variable a

	if (root->left == nullptr && root->right == nullptr)//when both left right is null the value of a printed 
		cout << a << endl;

	else{
		//recursively check the left tree and right tree node  
		printTree(root->left, a);
		printTree(root->right, a);
	}
}
