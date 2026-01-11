#ifndef QUERYPROCESSOR_HPP
#define QUERYPROCESSOR_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "Utils.hpp"
#include "Trie.hpp"
#include "InvertedIndex.hpp"
#include "DocumentStore.hpp"
#include "config_debug.hpp"

class QueryProcessor
{
public:
    struct RankedResult
    {
        DocumentStore::Docid docid;
        int score;
    };

    QueryProcessor(DocumentStore& docStore, InvertedIndex& index, Trie& trie);
    ~QueryProcessor();

    [[nodiscard]] auto processQuery(const std::string& query, std::size_t topK = 0) -> std::vector<RankedResult>;

private:
    DocumentStore& docStore;
    InvertedIndex& index;
    Trie& trie;
    StrUtil strutil;
    static DEBUG_log report;
};

#endif
