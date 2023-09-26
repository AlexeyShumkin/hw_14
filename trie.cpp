#include "trie.h"

TrieNode* getNewNode()
{
    TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < alphabetSize; ++i)
        pNode->children[i] = nullptr;
    return pNode;
}

void insert(TrieNode* root, const std::string& key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.size(); ++i)
    {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr)
            node->children[index] = getNewNode();
        node = node->children[index];
        ++node->counter;
    }
    node->isEndOfWord = true;
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < alphabetSize; i++)
        if (root->children[i])
            return false;
    return true;
}


bool search(TrieNode* root, const std::string& key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.size(); ++i)
    {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr)
            return false;
        node = node->children[index];
    }
    return true;
}

TrieNode* getNode(TrieNode* root, const std::string& key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.size(); ++i)
    {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr)
            continue;
        node = node->children[index];
    }
    return node;
}

void autocomplete(TrieNode* root, std::string& prefix)
{
    int index = prefix[0] - 'a';
    if (!root->children[index])
    {
        std::cout << "\n There is no word starts with this letter in the dictionary.\n You can add it yourself by entering the whole word: ";
        std::string newWord;
        std::cin >> newWord;
        insert(root, newWord);
    }
    else
    {
        if (search(root, prefix))
        {
            char buf[1000];
            int ind = 0;
            std::string res;
            TrieNode* node = nullptr;
            if (prefix.size() == 1)
            {
                node = root->children[index];
                getWords(node, buf, ind, res, prefix);
            }
            else
            {
                node = getNode(root, prefix);
                getWords(node, buf, ind, res, prefix);
            }
            int k = -1;
            for (int i = 0; i < node->counter; ++i)
            {
                std::string tmp;
                for (int j = k + 1; j < res.size(); ++j)
                {
                    if (res[j] == ' ')
                        break;
                    tmp.push_back(res[j]);
                    ++k;
                }
                std::cout << "\n Word version " << i + 1 << ": " << tmp << "\t confirm(y): ";
                char choice = '0';
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin >> choice;
                if (choice == 'y')
                {
                    std::cout << "\n Result: " << tmp << std::endl;
                    return;
                }
                else
                    ++k;
            }
            std::cout << "\n There are no more words in the dictionary with this prefix.\n";
        }
        else
        {
            std::cout << "\n There is no word starts with this prefix in the dictionary.\n You can add it yourself by entering the whole word: ";
            std::string newWord;
            std::cin >> newWord;
            insert(root, newWord);
        }
    }
}

void getWords(TrieNode* root, char buf[], int ind, std::string& res, const std::string& prefix)
{
    if (root == nullptr)
        return;
    if (root->isEndOfWord)
    {
        if (root->counter)
        {
            for (int i = 0; i < alphabetSize; i++)
            {
                if (root->children[i] != nullptr)
                {
                    buf[ind] = 'a' + i;
                    getWords(root->children[i], buf, ind + 1, res, prefix);
                }
            }
        }
        buf[ind] = '\0';
        res.append(prefix + buf);
        res.push_back(' ');
        return;
    }
    for (int i = 0; i < alphabetSize; i++)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = 'a' + i;
            getWords(root->children[i], buf, ind + 1, res, prefix);
        }
    }
}

TrieNode* remove(TrieNode* root, const std::string& key, int depth)
{
    if (!root)
        return nullptr;
    if (depth == key.size())
    {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        if (isEmpty(root))
        {
            delete root;
            root = nullptr;
        }
        return root;
    }
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) 
    {
        delete root;
        root = nullptr;
    }
    return root;
}

void erase(TrieNode* root)
{
    if (isEmpty(root))
    {
        delete root;
        return;
    }
    for (int i = 0; i < alphabetSize; ++i)
    {
        if (root->children[i] != nullptr)
            erase(root->children[i]);
    }
    delete root;
}
