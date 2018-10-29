#pragma once
#include "pch.h"
#include <stdio.h>
#include <queue>
#include <iostream>
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
		//cout << "Add root node..." << theTerm << endl;
		Node* node = new Node();
		node->term = theTerm;
		node->definition = theDefinition;
		root = node;
	}
	else
	{
		//cout << "Add new node: " << theTerm << endl;
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
	if (!node)
	{
		cout << "The data \"" << theTerm << "\" wasn't found. (Data set empty)\n";
	}
	else
	{
		Node* current = node, *parent = NULL;
		bool found = false;
		while ((current) && (!found))
		{
			if (current->term == theTerm)
			{
				found = true;
			}
			else
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
		if (!found)
		{
			cout << theTerm << " not in the data set. (the tree)" << endl;
		}
		else if ((!current->left) && (!current->right))
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
			cout << "\"" << theTerm << "\" has been deleted." << endl;
		}
		else if (((current->left) && (!current->right)) || ((!current->left) && (current->right)))
		{
			Node* child;
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
			cout << "\"" << theTerm << "\" has been deleted.";
		}
		else
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

void Tree::searchNode(Node* node, string theTerm)
{
	if (!node)
	{
		cout << "THE DATA AIN'T THERE SON" << endl;
	}
	else
	{
		Node* current = node, *parent = NULL;
		bool found = false; //Gotta find it if we're searching right?
		while ((current) && (!found))
		{
			if (current->term == theTerm)
			{
				found = true;
			}
			else
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
		if (!found)
		{
			cout << theTerm << " ain't here son, try again." << endl;
		}
		else
		{
			cout << theTerm << " was found, definition: " << current->definition << endl;
		}
	}
}

void Tree::editNode(Node* node, string theTerm)
{
	if (!node)
	{
		cout << "Oh, data, where art thou? NOT HERE" << endl;
	}
	else
	{
		Node* current = node, *parent = NULL;
		bool found = false;
		while ((current) && (!found))
		{
			if (current->term == theTerm)
			{
				found = true;
			}
			else
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
		if (!found)
		{
			cout << theTerm << " ain't here son, try again." << endl;
		}
		else
		{
			string tempTerm, tempDefinition; //Temporary strings to hold new information.
			cout << theTerm << " was found, definition: " << current->definition << endl; 
			cout << "Edit the term or leave it the same by pressing enter: " << endl;
			
			getline(cin, tempTerm);
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//If statement to confirm they actually entered something
			if (tempTerm == "\n")
			{
				current->term = theTerm;
			}
			else
			{
				current->term = tempTerm;
			}
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Now enter the updated definition, again press enter to leave it the same." << endl;
			getline(cin, tempDefinition);
			if (tempDefinition != "\n")
			{
				current->definition == tempDefinition;
			}
			cout << theTerm << " has been updated to: " << current->term << " and the definition is: " << current->definition << endl;
		}
	}
}