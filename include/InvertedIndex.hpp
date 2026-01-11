#ifndef INVERTEDINDEX_HPP
#define INVERTEDINDEX_HPP

#include <unordered_map>
#include <string>
#include <vector>
using Docid = std::size_t;

class InvertedIndex{
    private:
        std::unordered_map<std::string, std::unordered_map<Docid, int>> index;

    public:
        InvertedIndex();
        ~InvertedIndex();

        auto addWord(const std::string& word, Docid docid) -> void;
        auto addDocument(const std::vector<std::string>& words, Docid docid) -> void;
        auto clear() -> void;

        [[nodiscard]] auto hasWord(const std::string& word) const -> bool;
        [[nodiscard]] auto getPostings(const std::string& word) const 
        -> const std::unordered_map<Docid, int>*;
        [[nodiscard]] auto vocabularySize() const -> std::size_t;

};

#endif