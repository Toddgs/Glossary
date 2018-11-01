#pragma once
#include <string>
#include "Node.h"

using namespace std;

class Tree
{
	Node* root; //Pointer to the first node in the tree.
public:
	Tree(); //Default constructor
	~Tree(); //Destructor

	Node* getRoot() { return root; } //Returns the root pointer.
	bool isEmpty() { return (root == NULL); } //Checks to see if there is anything in the tree.
	void addNode(string theTerm, string theDefinition);
	void deleteNode(Node* node, string theTerm);
	void searchNode(Node* node, string theTerm);
	bool nodeSearch(Node* node, string theTerm);
	void stringSearch(Node* node, string theString);
	void writeToText(Node* node, ofstream & treeTextFile);
	//Basic traversals of the tree.
	void levelOrder(Node* node);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	void preOrder() { preOrder(root); }

	//Flashcards...
	void levelOrderFlashcards(Node* node);
	void inOrderFlashcards(Node* node);
	void postOrderFlashcards(Node* node);
	void preOrderFlashcards(Node* node);

	void inOrderTreeDisplay(Node *node);
	Node* findMin(Node* node);

private:
	void addNode(string theTerm, string theDefinition, Node* node);
	void postOrderDeletion(Node* node);
};