#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution
{
public:
  struct Trie
  {
    struct TrieNode
    {
      std::unordered_map<char, TrieNode *> edges;
      bool endsWord;
      TrieNode() : endsWord(false) {}
      ~TrieNode()
      {
        for (auto &edge : edges)
        {
          delete edge.second;
        }
      }

      void insert(TrieNode *node, const std::string &word)
      {
        auto currentNode = node;
        for (const char c : word)
        {
          if (currentNode->edges.find(c) == currentNode->edges.end())
          {
            currentNode->edges[c] = new TrieNode();
          }
          currentNode = currentNode->edges[c];
        }
        currentNode->endsWord = true;
      }

      bool find(TrieNode *node, const std::string &word) const
      {
        auto currentNode = node;
        for (const char c : word)
        {
          if (currentNode->edges.find(c) == currentNode->edges.end())
          {
            return false;
          }
          currentNode = currentNode->edges.at(c);
        }
        return currentNode->endsWord;
      }
    };

    TrieNode *root;
    Trie()
    {
      root = new TrieNode();
    }
    ~Trie()
    {
      delete root;
    }
    void insert(const std::string &word)
    {
      root->insert(root, word);
    }
    bool find(const std::string &word) const
    {
      return root->find(root, word);
    }
  };

  struct HeapNode
  {
    std::string word;
    int frequency;
    HeapNode(const std::string &w, int f) : word(w), frequency(f) {}
  };

  class MaxHeap
  {
  private:
    std::vector<HeapNode> heap;

    void heapifyDown(int index)
    {
      int largest = index;
      int left = 2 * index + 1;
      int right = 2 * index + 2;

      if (left < heap.size() && compare(heap[left], heap[largest]))
        largest = left;

      if (right < heap.size() && compare(heap[right], heap[largest]))
        largest = right;

      if (largest != index)
      {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
      }
    }

    void heapifyUp(int index)
    {
      if (index && compare(heap[index], heap[(index - 1) / 2]))
      {
        std::swap(heap[index], heap[(index - 1) / 2]);
        heapifyUp((index - 1) / 2);
      }
    }

    bool compare(const HeapNode &a, const HeapNode &b)
    {
      if (a.frequency == b.frequency)
        return a.word < b.word;         // Change to '<' for min-heap property with words
      return a.frequency > b.frequency; // Max-heap based on frequency
    }

  public:
    void push(const HeapNode &node)
    {
      heap.push_back(node);
      heapifyUp(heap.size() - 1);
    }

    void pop()
    {
      if (heap.size() > 1)
      {
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
      }
      else
      {
        heap.pop_back();
      }
    }

    HeapNode top() const
    {
      if (!heap.empty())
      {
        return heap[0];
      }
      throw std::out_of_range("Heap is empty");
    }

    size_t size() const
    {
      return heap.size();
    }

    bool empty() const
    {
      return heap.empty();
    }
  };

  std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k)
  {
    std::unordered_map<std::string, int> wordCount;
    for (const auto &word : words)
    {
      wordCount[word]++;
    }

    MaxHeap maxHeap;
    for (const auto &entry : wordCount)
    {
      maxHeap.push(HeapNode(entry.first, entry.second));
    }

    std::vector<std::string> result;
    for (int i = 0; i < k && !maxHeap.empty(); ++i)
    {
      result.push_back(maxHeap.top().word);
      maxHeap.pop();
    }

    return result;
  }
};