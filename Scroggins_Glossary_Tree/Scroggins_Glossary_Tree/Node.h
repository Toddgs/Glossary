#pragma once
#include <string>

using namespace std;
class Node
{
	string term;
	string definition;
	Node* left;
	Node* right;

	friend class Tree;
public:
	Node() { term = "~"; definition = "~"; left = right = NULL; };
};
