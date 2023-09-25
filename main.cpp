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
}