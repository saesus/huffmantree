// ASU CSE310 Honors Contract: Huffman
// Name of Author: Michael Li
// ASU ID: 1212612191
// Description: Converts the array to a a psuedo-tree, with associated outputs

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <sstream>
#include <cerrno>
#include <iostream>
#include <vector>
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree()
{
	root = new Node();
	length = 1;
	comp = 0;
}

HuffmanTree::~HuffmanTree()
{
	deleteTree(root);
}

void HuffmanTree::deleteTree(Node * n) {
	if (n->leftChild != NULL) {
		deleteTree(n->leftChild);
	}
	if (n->rightChild != NULL) {
		deleteTree(n->rightChild);
	}
	delete n;
}

void HuffmanTree::initialize(string contents)
{
	vector<char> c;
	vector<int> i;
	vectorize(contents, c, i); //Convert the contents into two vectors, # of occurrences and char
	length = contents.length();

	//Generates the BinaryHeap to organize the contents by creating nodes with
	//frequency and datapoint and inserting
	BinaryHeap<Node> bin;
	for (int x = 0; x < (int)c.size(); x++) {
		//cout << contents[x]<<endl;
		Node n;
		n.freq = i[x];
		n.data = c[x];
		bin.insert(n);
	}

	/* View contents of Binary Heap
	while (!bin->isEmpty()) {
	Node * t = new Node();
	bin->deleteMin(t);
	cout << t->data << t->freq << endl;
	}
	*/

	/*
	Generates the Huffman tree
	1) Creates a parent node to hold one to two children nodes
	2) Adds the frequencies of the children nodes and inserts back into the BinaryHeap
	3) Repeats until only one node left
	*/
	string h;
	Node* parent = new Node();
	while (!bin.isEmpty()) {
		parent = new Node();
		parent->data = '*';

		Node* x = new Node();
		bin.deleteMin(*x);
		parent->leftChild = x;
		parent->freq = x->freq;
		if (!bin.isEmpty()) {
			Node* x = new Node();
			bin.deleteMin(*x);
			parent->rightChild = x;
			parent->freq += x->freq;
			bin.insert(*parent);
		}
	}
	root = parent;
}

//Prints the contents of the HuffmanTree using a helper function
double HuffmanTree::traverse(int length) {
	traverseHelper(root->leftChild, "");
	double compRatio = ((double)length - (comp*.125)) / (length);
	cout << compRatio;
	return compRatio;
}
//Helper function to print the contents of the tree, prints out 
//the optimal compression when done traversing to each node
void HuffmanTree::traverseHelper(Node * n, string location) {
	if (n->leftChild != NULL) {
		traverseHelper(n->leftChild, location + "0");
	}
	if (n->rightChild != NULL) {
		traverseHelper(n->rightChild, location + "1");
	}
	else if (n->data != '*') {
		cout << n->data << " " << location << endl;
		comp += n->freq * location.length();
	}
}
//ZGGCICQ testing line

//Helper function for instantiate, generates a frequency and data vector for each new char
void HuffmanTree::vectorize(string contents, vector<char>& c, vector<int>& i) {
	char character;
	int counter;
	//Outer loop iterates through the array looking for unique chars
	//Inner loop counts instances of the char and places the value into the vector i
	for (int x = 0; x < (int)contents.length(); x++) {
		counter = 0;
		character = contents[x];
		c.push_back(character);
		for (int y = 0; y < (int)contents.length(); y++) {
			if (contents[y] == character) {
				counter++;
				contents.erase(y, 1); //removes the instances of the char
				y--;
			}
		}
		x--;
		i.push_back(counter);
	}
}

