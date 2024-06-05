#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
public:
  struct Trie
  {
    struct TrieNode
    {
      unordered_map<char, TrieNode *> edges;
      bool endsWord;
      TrieNode() : endsWord(false) {}
      ~TrieNode() {}

      void insert(TrieNode *node, string word)
      {
        auto currentNode = node;
        for (const auto c : word)
        {
          if (currentNode->edges.find(c) == currentNode->edges.end())
          {
            currentNode->edges.insert({c, new TrieNode()});
          }
          currentNode = currentNode->edges.at(c);
        }
        currentNode->endsWord = true;
      }

      string find(TrieNode *node, string word)
      {
        auto currentNode = node;
        string prefix = "";
        for (const auto c : word)
        {
          if (currentNode->edges.find(c) == currentNode->edges.end())
          {
            return prefix;
          }
          currentNode = currentNode->edges.at(c);
          prefix += c;
          if (currentNode->endsWord)
          {
            return prefix;
          }
        }
        return prefix;
      }
    };

    TrieNode *root;
    Trie()
    {
      root = new TrieNode();
    }
    void insert(string word)
    {
      root->insert(root, word);
    }
    string find(string word)
    {
      return root->find(root, word);
    }
    ~Trie() {}
  };

  string longestCommonPrefix(vector<string> &strs)
  {
    Trie trie;
    for (const auto &word : strs)
    {
      trie.insert(word);
    }
    string prefix = trie.find(strs[0]);
    return prefix;
  }
};