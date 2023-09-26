#include "trie.h"

int main()
{
	using namespace std::string_literals;
	TrieNode* root = getNewNode();
	std::string k1 = "ball"s;
	std::string k2 = "base"s;
	std::string k3 = "baseball"s;
	std::string k4 = "brand"s;
	std::string k5 = "brain"s;
	std::string k6 = "bort"s;
	std::string k7 = "bra"s;
	std::string k8 = "human"s;
	std::string k9 = "humus"s;
	std::string k10 = "hurma"s;
	insert(root, k1);
	insert(root, k2);
	insert(root, k3);
	insert(root, k4);
	insert(root, k5);
	insert(root, k6);
	insert(root, k7);
	insert(root, k8);
	insert(root, k9);
	insert(root, k10);

	bool open = true;
	do
	{
		std::cout << " Start/continue(1), exit(2): ";
		char choice = '0';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> choice;
		std::string prefix;
		switch (choice)
		{
		case '1':
			std::cout << "\n Start typing the word: ";
			std::cin >> prefix;
			autocomplete(root, prefix);
			break;
		case '2':
			std::cout << "\n Goodbye!";
			open = false;
			break;
		default:
			std::cout << "\n Your command is unclear. Please, select an action from the list:\n";
		}
		std::cout << '\n';
	} while (open);
	erase(root);
}