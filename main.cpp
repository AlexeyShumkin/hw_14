#include "trie.h"

int main()
{
	TrieNode* root = getNewNode();
	std::string k1 = "ball";
	std::string k2 = "base";
	std::string k3 = "baseball";
	std::string k4 = "brand";
	std::string k5 = "brain";
	std::string k6 = "bort";
	std::string k7 = "bra";
	insert(root, k1);
	insert(root, k2);
	insert(root, k3);
	insert(root, k4);
	insert(root, k5);
	insert(root, k6);
	insert(root, k7);
	std::string prefix;
	std::cout << "Start typing the word: ";
	std::cin >> prefix;
	autocomplete(root, prefix);
	
}