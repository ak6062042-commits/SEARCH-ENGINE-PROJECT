#include <unordered_map>
#include <string>
#include <vector>
#include "InvertedIndex.hpp"

InvertedIndex::InvertedIndex() = default;
InvertedIndex::~InvertedIndex() = default;

auto InvertedIndex::addWord(const std::string& word, Docid docid) -> void
{
    ++index[word][docid];
}

auto InvertedIndex::addDocument(const std::vector<std::string>& words, Docid docid) -> void
{
    for (const auto& word : words)
    {
        ++index[word][docid];
    }
}

[[nodiscard]] auto InvertedIndex::hasWord(const std::string& word) const -> bool
{
    return index.find(word) != index.end();
}

[[nodiscard]] auto InvertedIndex::getPostings(const std::string& word) const 
-> const std::unordered_map<Docid, int>*
{
    auto it = index.find(word);
    if (it == index.end())
    {
        return nullptr;
    }
    return &it->second;
}

[[nodiscard]] auto InvertedIndex::vocabularySize() const -> std::size_t
{
    return index.size();
}

auto InvertedIndex::clear() -> void
{
    index.clear();
}