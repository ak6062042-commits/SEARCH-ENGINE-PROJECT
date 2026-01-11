#ifndef TRIE_HPP
#define TRIE_HPP

#include <unordered_map>
#include <string>

class Trie
{
private:
    struct TrieNode
    {
        bool is_end;
        std::unordered_map<char, TrieNode*> children;
        TrieNode();
    };

    TrieNode* root;
    auto freeNode(TrieNode* node) -> void;

public:
    Trie();
    ~Trie();

    auto insert(const std::string& word) -> void;
    [[nodiscard]] auto search(const std::string& word) const -> bool;
    [[nodiscard]] auto startsWith(const std::string& prefix) const -> bool;
};

#endif