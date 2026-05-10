#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
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
    DF_Util dfutil;

    std::vector<std::string> filenames;
    std::vector<std::string> filepaths;
    dfutil.scanDataFolder(filenames, filepaths);
    size_t total_files = filenames.size();

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < total_files; ++i)
    {
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

        std::string line;
        StrUtil util;

        while (std::getline(file, line))
        {
            line = util.trim(line);
            auto tokens = util.tokenize(line);

            for (auto& token : tokens)
            {
                std::string normalized = util.normalizeword(token);
                if (!normalized.empty())
                {
                    index.addWord(normalized, docid);
                    trie.insert(normalized);
                }
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;

    std::cout << "\nTime Taken = " << elapsed_time.count()  << "sec\n";
    std::cout << "Index built successfully\n";
    std::cout << "Documents indexed: " << docStore.documentCount() << "\n";
    QueryProcessor qp(docStore, index, trie);

    while (true)
    {
        std::string query;
        std::string lowerd_query = "";
        int mode_choice;

        std::cout << "\nEnter query (or 'exit'): ";
        std::getline(std::cin, query);
        
        for(auto& ch : query)
        {
            ch = std::tolower(ch);
            lowerd_query += ch;
        }
        query = lowerd_query;

        if (query == "exit") break;

        std::cout << "Mode (1 = OR, 2 = AND): ";
        std::cin >> mode_choice;
        std::cin.ignore();

        QueryProcessor::Mode mode =
            (mode_choice == 2)
            ? QueryProcessor::Mode::AND
            : QueryProcessor::Mode::OR;

        auto results = qp.processQuery(query, mode);

        if (results.empty())
        {
            std::cout << "\nNo documents matched.\n";
            continue;
        }

        std::cout << "\nMatched documents:\n";

        for (const auto& res : results)
        {
            const auto& doc = docStore.getDocument(res.docid);

            std::cout << "-------------------------\n";
            std::cout << "File: " << doc.filename << "\n";
            std::cout << "Path: " << doc.filepath << "\n";
            std::cout << "Size: " << doc.filesize << " bytes\n";
            std::cout << "Score: " << res.score << "\n";
        }
    }

    return 0;
}
