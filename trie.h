#pragma once
#include <iostream>
#include <vector>
#include <string>
#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	int counter = 0;
	bool isEndOfWord;
};
TrieNode* getNewNode();
void insert(TrieNode* root, const std::string& key);
bool search(TrieNode* root, const std::string& key);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode* root, const std::string& key, int depth = 0);
void autocomplete(TrieNode* root, std::string& prefix);
void getPostfixes(TrieNode* root, char buf[], int ind, std::string& res, const std::string& prefix);


