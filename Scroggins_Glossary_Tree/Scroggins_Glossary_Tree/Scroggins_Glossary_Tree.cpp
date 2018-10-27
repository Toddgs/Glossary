// Scroggins_Glossary_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>



using namespace std;

void pressAnyKey()
{
	cout << "\nPress any key to continue" << endl << endl;
	_getch();
}

void readTerms()
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
		getline(termsFile, theDefinition, '\t');
		
	}
}


int main()
{
    
}
