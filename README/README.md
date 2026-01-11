# MINI SEARCH ENGINE
====================================================================================

*** WORKFLOW ***
/SearchEngineProject
│
├── include
│   ├── Trie.hpp
│   ├── InvertedIndex.hpp
│   ├── DocumentStore.hpp
│   ├── QueryProcessor.hpp
│   ├── config_debug.hpp
│   └── Utils.hpp
│
├── src
│   ├── Trie.cpp
│   ├── InvertedIndex.cpp
│   ├── DocumentStore.cpp
│   ├── QueryProcessor.cpp
│   ├── Utils.cpp
│   ├── config_debug.cpp
│   └── main.cpp
│
├── data
│   └── ( 9193 .txt files (average 2-10 lines each) )
│
├── scripts
│   └── build.bat
│
├── build
│   ├── Trie.o
│   ├── InvertedIndex.o
│   ├── DocumentStore.o
│   ├── QueryProcessor.o
│   ├── Utils.o
│   └── main.o
│
├── README
│   └── README.md
│
├── log
│   └── debug_log.txt
│
└── SearchEngine.exe

====================================================================================

Utils
 ├── Input helpers
 │    ├── safeIntInput
 │    ├── safeDoubleInput
 │
 ├── String helpers
 │    ├── toLower
 │    ├── trim
 │    ├── tokenize
 │    ├── normalizeWord
 │
 ├── File helpers
 │    ├── readFile
 │    ├── fileExists
 │    ├── listFiles
 │
 ├── Time helpers
 │    ├── now()
 │    ├── elapsedTime() 
 │
 └── Validation helpers
      ├── isNumeric
      ├── isValidToken

Raw line
  ↓
trim()
  ↓
tokenize()
  ↓
for each token:
    normalizeWord()
        ↓
    isValidToken()
        ↓
    index/store


    #ifndef DOCUMENT_STORE_HPP
#define DOCUMENT_STORE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>   // size_t

class DocumentStore
{
    public:
        using DocID = std::size_t;

        struct Document
        {
            DocID       id;
            std::string filename;
            std::string filepath;
            std::size_t filesize;
        };

    public:
        DocumentStore();
        ~DocumentStore();

        // Register a document and assign a DocID
        [[nodiscard]] auto addDocument(const std::string& filename,
                                       const std::string& filepath,
                                       std::size_t filesize) -> DocID;

        // Access by DocID
        [[nodiscard]] auto getDocument(DocID id) const -> const Document&;

        [[nodiscard]] auto getFilename(DocID id) const -> const std::string&;
        [[nodiscard]] auto getFilepath(DocID id) const -> const std::string&;

        // Lookup utilities
        [[nodiscard]] auto hasDocument(const std::string& filename) const -> bool;
        [[nodiscard]] auto getDocID(const std::string& filename) const -> DocID;

        // Metadata
        [[nodiscard]] auto documentCount() const -> std::size_t;
        [[nodiscard]] auto getAllDocuments() const -> const std::vector<Document>&;

    private:
        std::vector<Document> documents;
        std::unordered_map<std::string, DocID> filename_to_id;
};

#endif

    
    
#pragma once

#include <unordered_map>
#include <string>
#include <vector>

using Docid = std::size_t;

class InvertedIndex
{
private:
    // word -> (docid -> frequency)
    std::unordered_map<
        std::string,
        std::unordered_map<Docid, int>
    > index;

public:
    InvertedIndex() = default;

    // add a single word occurrence
    auto addWord(
        const std::string& word,
        Docid docid
    ) -> void
    {
        ++index[word][docid];
    }

    // add multiple words from a document
    auto addDocument(
        const std::vector<std::string>& words,
        Docid docid
    ) -> void
    {
        for (const auto& word : words)
        {
            ++index[word][docid];
        }
    }

    // check if a word exists in index
    [[nodiscard]] auto hasWord(const std::string& word) const -> bool
    {
        return index.find(word) != index.end();
    }

    // get posting list for a word
    [[nodiscard]] auto getPostings(const std::string& word) const -> const std::unordered_map<Docid, int>*
    {
        auto it = index.find(word);

        if (it == index.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    // total unique words indexed
    [[nodiscard]] auto vocabularySize() const -> std::size_t
    {
        return index.size();
    }

    // clear entire index
    auto clear() -> void
    {
        index.clear();
    }
};
