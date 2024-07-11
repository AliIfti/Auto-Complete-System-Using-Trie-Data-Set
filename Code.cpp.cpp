#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TrieNode
{
public:
    TrieNode *children[26];
    bool is_end_of_word;

    TrieNode()
    {
        is_end_of_word = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

class Trie
{
private:
    TrieNode *root;

    void dfs(TrieNode *node, string word, vector<string> &results)
    {
        if (node->is_end_of_word)
        {
            results.push_back(word);
        }
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (node->children[c - 'a'] != nullptr)
            {
                dfs(node->children[c - 'a'], word + c, results);
            }
        }
    }

public:
    TrieNode *getRoot() const
    {
        return root;
    }
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word) 
        {  
            if (node->children[c - 'a'] == nullptr)
            {
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
        node->is_end_of_word = true;
    }

    bool search(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (node->children[c - 'a'] == nullptr)
            {
                return false;
            }
            node = node->children[c - 'a'];
        }
        return node->is_end_of_word;
    }

    vector<string> words_with_prefix(const string &prefix)
    {
        vector<string> results;
        TrieNode *node = root;
        for (char c : prefix)
        {
            if (node->children[c - 'a'] == nullptr)
            {
                return results;
            }
            node = node->children[c - 'a'];
        }
        dfs(node, prefix, results);
        return results;
    }
};

int main()
{
    Trie trie;
    cout << "Trie initialized." << endl;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Get words with a prefix\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string word;
            cout << "Enter the word to insert: ";
            cin >> word;
            trie.insert(word);
            cout << "\"" << word << "\" inserted into the Trie." << endl;
            break;
        }
        case 2:
        {
            string word;
            cout << "Enter the word to search: ";
            cin >> word;
            cout << boolalpha << "Word \"" << word << "\" found: " << trie.search(word) << endl;
            break;
        }
        case 3:
        {
            string prefix;
            cout << "Enter the prefix: ";
            cin >> prefix;

            TrieNode *prefixNode = trie.getRoot();
            for (char c : prefix)
            {
                if (prefixNode->children[c - 'a'] == nullptr)
                {
                    cout << "No words with prefix \"" << prefix << "\" found." << endl;
                    break;
                }
                prefixNode = prefixNode->children[c - 'a'];
            }

            // Check if the prefix exists before calling dfs
            if (prefixNode != nullptr)
            {
                vector<string> completions = trie.words_with_prefix(prefix);
                cout << "Words with prefix \"" << prefix << "\":\n";
                for (const string &word : completions)
                {
                    cout << word << endl;
                }
            }

            break;
        }

        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    }

    return 0;
}