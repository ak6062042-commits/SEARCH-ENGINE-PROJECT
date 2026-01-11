#include <iostream>
#include <fstream>
#include <vector>
#include "Utils.hpp"
#include "DocumentStore.hpp"
#include "InvertedIndex.hpp"
#include "Trie.hpp"
#include "QueryProcessor.hpp"

int main()
{
    DocumentStore docStore;
    InvertedIndex index;
    Trie trie;
    QueryProcessor qp(docStore, index, trie);
    DF_Util dfutil;

    std::vector<std::string> filenames;
    std::vector<std::string> filepaths;
    dfutil.scanDataFolder(filenames, filepaths);

    for (size_t i = 0; i < filenames.size(); ++i) {
        std::ifstream file(filepaths[i]);
        if (!file.is_open()) continue;

        file.seekg(0, std::ios::end);
        std::size_t filesize = file.tellg();
        file.seekg(0, std::ios::beg);

        auto docid = docStore.addDocument(
            filenames[i],
            filepaths[i],
            filesize
        );

        StrUtil strutil;
        std::string line;

        while (std::getline(file, line)) {
            auto tokens = strutil.tokenize(strutil.trim(line));
            for (auto& token : tokens) {
                std::string word = strutil.normalizeword(token);
                if (!word.empty()) {
                    index.addWord(word, docid);
                    trie.insert(word);
                }
            }
        }
    }

    std::cout << "Index built with "
              << docStore.documentCount()
              << " documents.\n";

    std::string query;
    while (true) {
        std::cout << "\nSearch (or 'exit'): ";
        std::getline(std::cin, query);
        if (query == "exit") break;

        auto results = qp.processQuery(query/*, 20 ->for top 20 */ );

        if (results.empty()) {
            std::cout << "No results found.\n";
            continue;
        }

        std::cout << "\nRank  Score  Filename\n";
        std::cout << "---------------------------\n";

        int rank = 1;
        for (const auto& r : results) {
            std::cout
                << rank++ << "     "
                << r.score << "     "
                << docStore.getFilename(r.docid)
                << "\n";
        }
    }

    return 0;
}
