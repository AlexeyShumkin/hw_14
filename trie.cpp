#include "trie.h"

TrieNode* getNewNode()
{
    TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
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
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
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
    if (node != nullptr)
        return node;
    return nullptr;
}

void autocomplete(TrieNode* root, std::string& prefix)
{
    int index = prefix[0] - 'a';
    if (!root->children[index])
    {
        std::cout << "There is no word starts with this letter in the dictionary.\nYou can add it yourself by entering the whole word: ";
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
            if (prefix.size() == 1)
                getPostfixes(root->children[index], buf, ind, res, prefix);
            else
                getPostfixes(getNode(root, prefix), buf, ind, res, prefix);
            std::cout << res;
            
        }
        else
        {
            std::cout << "There is no word starts with this prefix in the dictionary.\nYou can add it yourself by entering the whole word: ";
            std::string newWord;
            std::cin >> newWord;
            insert(root, newWord);
        }
    }
}

void getPostfixes(TrieNode* root, char buf[], int ind, std::string& res, const std::string& prefix)
{
    if (root == nullptr)
        return;
    if (root->isEndOfWord)
    {
        if (root->counter)
        {
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (root->children[i] != nullptr)
                {
                    buf[ind] = 'a' + i;
                    getPostfixes(root->children[i], buf, ind + 1, res, prefix);
                }
            }
        }
        buf[ind] = '\0';
        res.append(prefix + buf);
        res.push_back('\n');
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = 'a' + i;
            getPostfixes(root->children[i], buf, ind + 1, res, prefix);
        }
    }
}