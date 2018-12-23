// ASU CSE310 Honors Contract: Huffman
// Name of Author: Michael Li
// ASU ID: 1212612191
// Description: Header file for the tree

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string>
#include <vector>
#include "BinaryHeap.cpp"

using namespace std;

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

struct Node
{
public:
	int freq;
	char data;
	Node *parent;
	Node *leftChild;
	Node *rightChild;
	Node(int freq, char data) : freq{ freq }, data{ data }, parent{ nullptr }, leftChild{ nullptr }, rightChild{ nullptr } {};
	Node() : Node(0, '\0') {};
	bool operator> (const Node  &) const;
	bool operator>=(const Node  &) const;
	bool operator==(const Node  &) const;
	bool operator<=(const Node  &) const;
	bool operator< (const Node  &) const;
};

//Overloads the comparison operators to ensure the BinaryHeap sorts by frequency
inline bool Node::operator> (const Node  &f) const { return freq > f.freq; }
inline bool Node::operator>=(const Node  &f) const { return freq >= f.freq; }
inline bool Node::operator==(const Node  &f) const { return freq == f.freq; }
inline bool Node::operator<=(const Node  &f) const { return freq <= f.freq; }
inline bool Node::operator< (const Node  &f) const { return freq < f.freq; }

class HuffmanTree
{
	private:
		Node * root;
		int length;
		int comp;
	public:
		HuffmanTree();
		~HuffmanTree();
		void deleteTree(Node * n);
		void initialize(string contents);
		double traverse(int length);
		void traverseHelper(Node * n, string location);
		void vectorize(string contents, vector<char>& c, vector<int>& i);
		//void encode(char c);
		//string getCompressionRatio();
};

#endif
