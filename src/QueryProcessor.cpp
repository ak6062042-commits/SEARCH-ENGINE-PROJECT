#include "QueryProcessor.hpp"
#include <algorithm>

DEBUG_log QueryProcessor::report;

QueryProcessor::QueryProcessor(DocumentStore& ds, InvertedIndex& idx, Trie& tr)
    : docStore(ds), index(idx), trie(tr) {}

QueryProcessor::~QueryProcessor() = default;

auto QueryProcessor::processQuery(
    const std::string& query,
    Mode mode
) -> std::vector<Result>
{
    std::vector<Result> final_results;
    std::unordered_map<DocumentStore::Docid, int> score_map;
    std::unordered_map<DocumentStore::Docid, int> doc_hit_count;

    auto tokens = strutil.tokenize(query);

    const int token_count = static_cast<int>(tokens.size());

    for (auto& token : tokens)
    {
        std::string normalized = strutil.normalizeword(token);
        if (normalized.empty()) continue;

        if (!trie.startsWith(normalized)) 
        {
            report.enable_module("QUERY");
            report.log("QUERY", DEBUG_log::INFO,
            "No prefix found for token: " + normalized);
            report.disable_module("QUERY");
            continue;
        }

        if (!index.hasWord(normalized)) 
        {
            report.enable_module("QUERY");
            report.log("QUERY", DEBUG_log::INFO,
            "Prefix exists but exact word not found: " + normalized);
            report.disable_module("QUERY");
            continue;
        }

        auto postings = index.getPostings(normalized);
        if (!postings) continue;

        for (const auto& [docid, freq] : *postings)
        {
            score_map[docid] += freq;
            doc_hit_count[docid]++;
        }
    }
    if (!strutil.isValidToken(tokens)) return final_results;

    for (const auto& [docid, score] : score_map)
    {
        if (mode == Mode::AND)
        {
            if (doc_hit_count[docid] != token_count)
                continue;
        }

        final_results.push_back({ docid, score });
    }

    std::sort(
        final_results.begin(),
        final_results.end(),
        [](const Result& a, const Result& b) {
            return a.score > b.score;
        }
    );

    return final_results;
}
