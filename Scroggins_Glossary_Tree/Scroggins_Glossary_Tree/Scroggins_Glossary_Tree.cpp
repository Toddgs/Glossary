// Scroggins_Glossary_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
//#include "Node.h"
#include "Tree.h"

using namespace std;


Tree yggdrasil = Tree(); //FIXME: Need a better solution than a global variable, maybe a tree pointer?

void pressAnyKey()
{
	cout << "\nPress any key to continue" << endl << endl;
	_getch();
}

void readTermsFile()
{
	ifstream termsFile("Terms.txt", ios::in);
	string theWord, theDefinition;

	if (!termsFile)
	{
		cerr << "Inorrect file type!" << endl;
		exit(1);
	}

	while (!termsFile.eof())
	{
		getline(termsFile, theWord, '\t');
		getline(termsFile, theDefinition, '\n');
		yggdrasil.addNode(theWord, theDefinition);
	}
}

void writeTermsFile()
{
	ofstream termsTextFile("Terms.txt", ios::out);
	int i = 0;
	if (!termsTextFile)
	{
		cerr << "File is in TROUBLE BETTER MAKE IT DOUBLE! (Doesn't exist or couldn't be opened)" << endl;
		exit(1);
	}
	/*FIXME: Need to find a way to cycle through every option in the tree. 
	while (i < )
	{
	Node* node;
	node = 
	termsTextFile	<< node->term
					<< node->definition

	}
	*/	

	termsTextFile.close();
	
}

int menuDisplay()
{
	int userChoice; //Int to store the users choice from the menu.
	

	
	//Menu display information
	cout << "SELECT AN OPTION OR FACE IMMINENT DOOM\n";
	cout << "Please make a selection:\n";
	cout << "1: Add a term and it's meaning.\n";
	cout << "2: Edit a term.\n";
	cout << "3: Find and display a term.\n";
	cout << "4: View all the terms in a list.\n";
	cout << "5: Show flashcards.\n";
	cout << "6: Delete a term.\n";
	cout << "7: Search for text within a term or it's definition.\n";
	cout << "8: Exit the program.\n";
	cout << "Please enter a selection: ";

	cin >> userChoice;
	return userChoice; //FIXME remove this upon finishing the remaining returns
}

void addTerm()
{
	string theTerm, theDefinition; //Variables to hold information needed to create a new term.
	
	cout << "Please enter a term to add:" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	getline(cin, theTerm); //Gets all the entered text and puts it into the string theTerm.

	cout << "Now, enter the definition for that term:" << endl;
	getline(cin, theDefinition); //Gets all the entered text and puts it into the string theDefinition.

	yggdrasil.addNode(theTerm, theDefinition); //Adds a leaf to the world tree...
}

void editTerm()
{
	
	string theTerm, tempTerm, tempDefinition; //The term needed to search for, find, and edit the term in question.
	bool found;

	cout << "Please enter the term to be modified:" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	getline(cin, theTerm); //Gets all the entered text and puts it into the string theTerm.
	found = yggdrasil.nodeSearch(yggdrasil.getRoot(), theTerm);
	if (found)
	{
		yggdrasil.deleteNode(yggdrasil.getRoot(), theTerm);

		cout << "Please enter the new term: " << endl;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
		getline(cin, tempTerm); //Gets all the entered text and puts it into the string theTerm.

		cout << "Now, enter the new definition for that term:" << endl;
		getline(cin, tempDefinition); //Gets all the entered text and puts it into the string theDefinition.

		yggdrasil.addNode(tempTerm, tempDefinition);
	}
	else
	{
		cout << "Bruh, it wasn't there!" << endl;
	}
	

	
	//yggdrasil.deleteNode(yggdrasil.getRoot(), theTerm); Delete  the offending term

}

void displayTerm()
{
	string theTerm;
	cout << "Please enter a term to have it's definition displayed." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	getline(cin, theTerm); //Gets all the entered text and puts it into the string theTerm.

	//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.

	yggdrasil.searchNode(yggdrasil.getRoot(), theTerm);
	
	
}

void listAllTerms()
{
	yggdrasil.inOrder(yggdrasil.getRoot());
}

void flashcards()
{
	int choice;
	cout << "Please choose a type of traversal to view the flashcards in:" << endl;
	cout << "1. PreOrder Traversal" << endl;
	cout << "2. InOrder Traversal" << endl;
	cout << "3. PostOrder Traversal" << endl;
	cout << "4. LevelOrder Traversal" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		yggdrasil.preOrderFlashcards(yggdrasil.getRoot());
		break;
	}
	case 2:
	{
		yggdrasil.inOrderFlashcards(yggdrasil.getRoot());
		break;
	}
	case 3:
	{
		yggdrasil.postOrderFlashcards(yggdrasil.getRoot());
		break;
	}
	case 4:
	{
		yggdrasil.levelOrderFlashcards(yggdrasil.getRoot());
		break;
	}
	default:
		cout << "I'm sorry, that isn't a valid selection." << endl;
		break;
	}
}

void deleteTerm()
{
	string theTerm;
	cout << "Please enter a term to be deleted." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	getline(cin, theTerm); //Gets all the entered text and puts it into the string theTerm.
	
	//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	if (yggdrasil.nodeSearch(yggdrasil.getRoot(), theTerm) == true)
	{
		cout << "Term deleted." << endl;
	}
	yggdrasil.deleteNode(yggdrasil.getRoot(), theTerm);
	
}

void stringSearch()
{
	string theString;
	cout << "Please enter what you wish to search for: " << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cuz CIN is dumb, hangs onto newline characters, and has several other issues.
	getline(cin, theString);
	
	yggdrasil.stringSearch(yggdrasil.getRoot(), theString);
}

void saveAndExit()
{

}

int main()
{
	//Declare variables
	int userChoice; //Users choice from menuDisplay function.
	bool theMeaningOfLife = true; //Boolean to trigger end condition of while loop.

	readTermsFile();
	while (theMeaningOfLife)
	{
		userChoice = menuDisplay();
		switch (userChoice)
		{
		case 1: //Add a term and it's meaning.
		{
			addTerm();
			pressAnyKey();
			break;
		}
		case 2: //Edit a term.
		{
			cout << "Editing a term.";
			editTerm();
			break;
		}
		case 3: //Find and display a term and it's definition.
		{
			displayTerm();
			pressAnyKey();
			break;
		}
		case 4: //View all terms in a list. 
		{
			cout << "Viewing all terms:" << endl;
			listAllTerms();
			pressAnyKey();
			break;
		}
		case 5: //Show flashcards.
		{
			//cout << "Showing Flashcards.";
			flashcards();
			break;
		}
		case 6: //Delete a term.
		{
			//cout << "Deleting a term.";
			deleteTerm();
			pressAnyKey();
			break;
		}
		case 7: // Show all entries containing a search string.
		{
			cout << "Searching for a string.";
			stringSearch();
			break;
		}
		case 8: //Exit.
		{
			cout << "Exiting.";
			theMeaningOfLife = false;
			break;
		}
		userChoice = NULL;
		}
	}
}
