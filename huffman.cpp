// ASU CSE310 Honors Contract: Huffman
// Name of Author: Michael Li
// ASU ID: 1212612191
// Description: Using predefined priority queues to build an optimal Huffman tree
// Program will take in an input, and feed into a priority queue. This will then 
// generate priority and create a tree. Only goal is to generate a tree.

//Tree generation algorithm:
//Creates a parent node, fills children nodes with the heapMin
//Puts parent node back into heap, sorts
//Repeat

//To operate, input the name of the file to generate a Huffman Tree for. This should be in .txt format
//The program will then create a tree accordingly. Spaces and \n characters have their own encodings.

#define _CRT_SECURE_NO_WARNINGS
#include <cerrno>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <time.h> 
#include "HuffmanTree.h"

using namespace std;

string gen_random() {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> in(1, 1000);
	std::uniform_int_distribution<> ch(0, 26);
	string returnString = "";
	char c;
	for (int i = 0; i < in(gen); ++i) {
		c = 'a' + ch(gen);
		returnString += c;
	}

	return returnString;
}

//Returns the contents of the inputted file as a string
string get_file_contents(string filename)
{
	//appends a .txt extension if not already there
	string suffix = ".txt";
	if (filename.size() < suffix.size() ||
		filename.compare(filename.size() - suffix.size(), suffix.size(), suffix) != 0) {
		filename += ".txt";
	}
	fstream in(filename, ios::in | ios::binary);
	if (in)
	{
		std::ostringstream contents;
		contents << in.rdbuf();
		in.close();
		return(contents.str());
	}
	else {
		return "";
	}
}

int huffman1() {
	//Reads in input including white spaces
	string fileName;
	cout << "Please enter a text file name: \n";
	getline(cin, fileName);

	//ofstream myfile; //sets up a myFile object
	//myfile.open(fileName); //opens up the file with the inputted name
	//myfile << "Writing this to a file.\n"; //writes to the file
	//myfile.close(); //closes the file


	string contents = get_file_contents(fileName); //calls the function to read the file
	if (contents.length() == 0) { //Ends program if document is empty
		cout << "Empty Document";
		cin.get();
		return 0;
	}
	cout << contents + "\n";

	//int y = contents.length();
	/*
	string* minitem = new string[y]; //Holder for the output of the binary tree (remove later?)
	int count = 0;
	bin.deleteMin(minitem[count]);
	char priority;
	count++;
	//Migrates contents to minitem
	while (!bin.isEmpty()) {
		bin.deleteMin(minitem[count]);
		cout << minitem[count] << endl;
		count++;
	}
	*/

	HuffmanTree *tree = new HuffmanTree();
	tree->initialize(contents);

	cout << "The optimal Huffman code is:" << endl;

	cout << "The compression ratio is:" << endl;
	tree->traverse(contents.length());
	
	return 1;
}

int huffman2() {
	clock_t t;
	t = clock();
	string randString = "";
	double totalCompRatio = 0;
	for (int x = 0; x < 1000; x++) {
		randString = gen_random();
		cout << randString << endl;

		HuffmanTree *tree = new HuffmanTree();
		tree->initialize(randString);

		cout << "The optimal Huffman code is:" << endl;

		cout << "The compression ratio is:" << endl;
		totalCompRatio += tree->traverse(randString.length());
	}

	totalCompRatio = totalCompRatio / 1000;
	cout << "\nThe average compression ratio is: " << totalCompRatio << endl;
	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 1;
}

int main() {
	
	huffman2();
	cin.get(); //pauses the program
}
