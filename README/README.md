# MINI SEARCH ENGINE
====================================================================================

# MY FIRST EVER GITHUB PUBLISH
# C++ SIMPLE MINI SEARCH ENGINE
# 1:33AM 1/12/2026 (3RD SEMESTER UNIVERSITY)


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

2. Class Summary
DocumentStore
struct Document {
    Docid id;
    std::string filename;
    std::string filepath;
    size_t filesize;
};


Functions: addDocument(), getFilename(), getFilepath(), getAllDocuments(), hasDocument()

InvertedIndex

Stores mapping: word → {docid → frequency}

Functions: addWord(), addDocument(), getPostings(), hasWord(), clear()

Trie

Node structure: bool is_end, unordered_map<char, TrieNode*> children

Functions: insert(word), search(word), startsWith(prefix)

QueryProcessor

Functions: processQuery(query), getFilenames(docids)

Features: tokenization, normalization, ranking, AND/OR logic, logging

Utilities

StrUtil: tokenize(), normalizeword(), trim()

DF_Util: scanDataFolder(), validateDataFolder()

DEBUG_log: log(), enable_module(), disable_module()

3. Logging Usage

Enable logs at different levels: INFO, WARNING, ERROR

Log examples:

Invalid token

Prefix exists but word not found

Document ID out of range

Log file: log/debug_log.txt

4. How to Build

Open Command Prompt in scripts/ directory

Run:

build.bat


Output executable: SearchEngine.exe

5. How to Run
SearchEngine.exe


Enter queries interactively

Type exit to quit

6. Future Work

Implement TF-IDF for ranking

Extract query snippets from documents

Add advanced Boolean query parsing

Integrate top-K results

Improve prefix expansion using Trie
