#pragma once
#include "pch.h"
#include <stdio.h>
#include <queue>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "Tree.h"



using namespace std;

Tree::Tree() //Default constructor
{
	root = NULL;
}

Tree::~Tree() //Destructor
{
	postOrderDeletion(root);
}

void Tree::postOrderDeletion(Node* node)
{
	if (node)
	{
		postOrderDeletion(node->left);
		postOrderDeletion(node->right);
		delete node;
	}
}

void Tree::addNode(string theTerm, string theDefinition)
{
	if (isEmpty())
	{
		Node* node = new Node();
		node->term = theTerm;
		node->definition = theDefinition;
		root = node;
	}
	else
	{
		addNode(theTerm, theDefinition, root);
	}
}


void Tree::addNode(string theTerm, string theDefinition, Node* node)
{
	if (theTerm <= node->term)
	{
		if (node->left)
		{
			addNode(theTerm, theDefinition, node->left);
		}
		else
		{
			Node* newNode = new Node();
			newNode->term = theTerm;
			newNode->definition = theDefinition;
			node->left = newNode;
		}
	}
	else
	{
		if (node->right)
		{
			addNode(theTerm, theDefinition, node->right);
		}
		else
		{
			Node* newNode = new Node();
			newNode->term = theTerm;
			newNode->definition = theDefinition;
			node->right = newNode;
		}
	}
}

void Tree::levelOrder(Node* node)
{
	queue<Node*> termQueue;

	termQueue.push(node);

	while (!termQueue.empty())
	{
		Node* visitNode = termQueue.front();
		termQueue.pop();

		cout << visitNode->term << endl;

		if (visitNode->left)
		{
			termQueue.push(visitNode->left);
		}

		if (visitNode->right)
		{
			termQueue.push(visitNode->right);
		}
	}
}

void Tree::preOrder(Node* node)
{
	if (node)
	{
		std::cout << node->term << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void Tree::inOrder(Node* node)
{
	if (node)
	{
		inOrder(node->left);
		std::cout << node->term << endl;
		inOrder(node->right);
	}
}

void Tree::postOrder(Node* node)
{
	if (node)
	{
		postOrder(node->left);
		postOrder(node->right);
		cout << node->term << endl;
	}
}

Node* Tree::findMin(Node* node)
{
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

void Tree::inOrderTreeDisplay(Node *node)
{
	if (node)
	{
		inOrderTreeDisplay(node->left);
		cout << node->term;
		if (node->left)
		{
			cout << ": left child-> " << node->left->term;
		}
		if (node->right)
		{
			cout << " rightchild-> " << node->right->term;
		}
		cout << endl;
		inOrderTreeDisplay(node->right);
	}
}

void Tree::deleteNode(Node* node, string theTerm)
{
	if (!node) //Check and make sure there is a node.
	{
		cout << "The data \"" << theTerm << "\" wasn't found. (Data set empty)\n";
	}
	else //If there is a node, DO STUFF
	{
		Node* current = node, *parent = NULL; //create and set pointer variables.
		bool found = false; //Boolean values to determine if we've found what we're looking for.
		while ((current) && (!found)) //While there is a node and it isn't found continue looping.
		{
			if (current->term == theTerm) //Check to see if the this term matches the term we were given.
			{
				found = true;
			}
			else //If not, Move on down the line, moving closer each time we check and fail to find it.
			{
				parent = current;
				if (theTerm > (current->term))
				{
					current = current->right;
				}
				else
				{
					current = current->left;
				}
			}
		}
		if (!found) //If the term is not found.
		{
			cout << theTerm << " not in the data set. (the tree)" << endl;
		}
		else if ((!current->left) && (!current->right)) //Deletes the node if it is the last node in the tree.
		{
			if ((parent) && (parent->left == current))
			{
				parent->left = NULL;
			}
			else if (parent)
			{
				parent->right = NULL;
			}
			delete current;
		}
		else if (((current->left) && (!current->right)) || ((!current->left) && (current->right))) //Moves the nodes around as needed to allow the deletion of a node with no dangling pointers.
		{
			Node* child; 
			//The following if/else segment checks to make sure there isn't a node to the left or right, if there is, it moves the node before deleting it. 
			if (current->left)
			{
				child = current->left;
			}
			else
			{
				child = current->right;
			}
			if (parent->left == current)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}
			delete current;
		}
		else //Emergency case, in case of real weirdness. 
		{
			Node *minRight = findMin(current->right);
			current->term = minRight->term;
			cout << "\"" << theTerm << "\" has been deleted\n";
			cout << "A copy of \"" << minRight->term << "\" has been put in the place of \"" << theTerm << "\".\n";
			cout << "Now the original \"" << minRight->term << "\" must be deleted.\n";
			deleteNode(current->right, minRight->term);
		}
	}
}

void Tree::searchNode(Node* node, string theTerm) //Searches for a node in the tree by the term included.
{
	if (!node) //Checks to make sure a node is present. 
	{
		cout << "THE DATA AIN'T THERE SON" << endl;
	}
	else
	{
		Node* current = node, *parent = NULL; //Temp pointer variables
		bool found = false; //Gotta find it if we're searching right?
		while ((current) && (!found))
		{
			if (current->term == theTerm) //If it is found, tells us so.
			{
				found = true;
			}
			else //If not, continues to find it.
			{
				parent = current;
				if (theTerm > (current->term))
				{
					current = current->right;
				}
				else
				{
					current = current->left;
				}
			}
		}
		if (!found) //If it isn't found, displays a message to the user that the term hasn't been found.
		{
			cout << theTerm << " ain't here son, try again. Remember! Uppercase/lowercase matters!" << endl;
		}
		else
		{
			cout << theTerm << " was found, definition: " << current->definition << endl;
		}
	}
}

bool Tree::nodeSearch(Node* node, string theTerm) //Checks to see if a node exists, used as a helper function for other code.
{
	if (node == NULL)
	{
		return false;
	}
	else if (node->term == theTerm)
	{
		return true;
	}
	else if (theTerm <= node->term)
	{
		return nodeSearch(node->left, theTerm);
	}
	else
	{
		return nodeSearch(node->right, theTerm);
	}
}


void Tree::stringSearch(Node* node, string theString) //Searches for a string within the Term and Definition of a node. If found, it displays them.
{
	if (node)
	{
		stringSearch(node->left, theString);
		if ((node->term.find(theString) <= 1000) || (node->definition.find(theString) <= 1000)) //The .find string operator returns the function no_pos if the string is not found, this returns a huge positive number, thus the need for less than 1000.
		{
			cout << node->term << endl;
			cout << node->definition << endl << endl;
		}
		stringSearch(node->right, theString);
	}	
}

void Tree::preOrderFlashcards(Node* node) //Flashcard function with preorder traversal.
{
	if (node)
	{
		string input;

		cout << node->term << endl << endl;
		cout << "\nPress any key to see the definition." << endl << endl;
		_getch();
		cout << node->definition << endl << endl;
		_getch();
		cout << "Press e (followed by enter) to exit or any of other key (followed by enter) to continue." << endl;
		
		cin >> input;
		
		if (input == "e") //If statements allow exiting the loop if desired. Thought it would be a nice touch.
		{
			return;
		}
		else if (input != "e") //If not exited, recursively displays more flashcards.
		{
			preOrderFlashcards(node->left);
			preOrderFlashcards(node->right);
		}
	}
}

void Tree::postOrderFlashcards(Node* node) //Flashcards with post order traversal.
{
	if (node)
	{
		
		postOrderFlashcards(node->left);
		postOrderFlashcards(node->right);
		cout << node->term << endl << endl;
		cout << "\nPress any key to see the definition." << endl << endl;
		_getch();
		cout << node->definition << endl << endl;
		_getch();

	}
}

void Tree::inOrderFlashcards(Node* node) //Flash cards with in order traversal.
{
	string input;

	if (input == "e")
	{
		return;
	}
	else if (input != "e")
	{
		postOrderFlashcards(node->left);
	}
	cout << node->term << endl << endl;
	cout << "\nPress any key to see the definition." << endl << endl;
	_getch();
	cout << node->definition << endl << endl;
	_getch();
	cout << "Press e (followed by enter) to exit or any of other key (followed by enter) to continue." << endl;

	cin >> input;

	if (input != "e")
	{
		postOrderFlashcards(node->right);
	}
}

void Tree::levelOrderFlashcards(Node* node) //Flash cards with level order traversal.
{
	queue<Node*> termQueue;

	termQueue.push(node);

	while (!termQueue.empty())
	{
		Node* visitNode = termQueue.front();
		termQueue.pop();

		cout << visitNode->term << endl << endl;
		cout << "\nPress any key to see the definition." << endl << endl;
		_getch();
		cout << visitNode->definition << endl << endl;
		_getch();


		if (visitNode->left)
		{
			termQueue.push(visitNode->left);
		}

		if (visitNode->right)
		{
			termQueue.push(visitNode->right);
		}
	}
}

void Tree::writeToText(Node* node, ofstream & treeTextFile) //A save function for the file. Needs to be passed the root and the text file to be saved to.
{
	if (node)
	{
		
		if (!treeTextFile)
		{
			cerr << "File ain't here son, better make it!" << endl;
			exit(1);
		}
		else
		{
			treeTextFile << node->term << '\t'
						 << node->definition << '\n';
			writeToText(node->left, treeTextFile);
			writeToText(node->right, treeTextFile);
		}


	}
}