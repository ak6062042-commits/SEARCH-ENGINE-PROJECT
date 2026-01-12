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

class QueryProcessor {
public:
    enum class Mode {
        OR,
        AND
    };

    struct Result {
        DocumentStore::Docid docid;
        int score;
    };

public:
    QueryProcessor(DocumentStore& docStore, InvertedIndex& index, Trie& trie);
    ~QueryProcessor();

    [[nodiscard]] auto processQuery(
        const std::string& query,
        Mode mode
    ) -> std::vector<Result>;

private:
    DocumentStore& docStore;
    InvertedIndex& index;
    Trie& trie;
    StrUtil strutil;

    static DEBUG_log report;
};

#endif
