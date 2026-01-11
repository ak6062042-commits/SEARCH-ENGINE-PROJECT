#include "Trie.hpp"

Trie::TrieNode::TrieNode() : is_end(false){}
Trie::Trie() { root = new TrieNode(); }
Trie::~Trie(){ freeNode(root); }

auto Trie::freeNode(TrieNode* node) -> void
{
    if (!node) return;
    for (auto& pair : node->children) freeNode(pair.second);
    delete node;
}

auto Trie::insert(const std::string& word) -> void
{
    TrieNode* current = root;
    for (char ch : word)
    {
        if (current->children.find(ch) == current->children.end())
        {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->is_end = true;
}

[[nodiscard]] auto Trie::search(const std::string& word) const -> bool
{
    TrieNode* current = root;
    for (char ch : word)
    {
        auto it = current->children.find(ch);
        if (it == current->children.end()) return false;
        current = it->second;
    }
    return current->is_end;
}

[[nodiscard]] auto Trie::startsWith(const std::string& prefix) const -> bool
{
    TrieNode* current = root;

    for (char ch : prefix)
    {
        auto it = current->children.find(ch);
        if (it == current->children.end()) return false;
        current = it->second;
    }
    return true;
}
