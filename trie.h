#pragma once
#include <iostream>
#include <string>
constexpr int alphabetSize = 26;
struct TrieNode
{
	TrieNode* children[alphabetSize];
	int counter = 0;
	bool isEndOfWord;
};
TrieNode* getNewNode();
void insert(TrieNode* root, const std::string& key);
bool search(TrieNode* root, const std::string& key);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode* root, const std::string& key, int depth = 0);
void autocomplete(TrieNode* root, std::string& prefix);
void getWords(TrieNode* root, char buf[], int ind, std::string& res, const std::string& prefix);
void erase(TrieNode* root);

