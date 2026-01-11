#include "QueryProcessor.hpp"
#include <algorithm>

DEBUG_log QueryProcessor::report;

QueryProcessor::QueryProcessor(DocumentStore& ds, InvertedIndex& idx, Trie& tr)
    : docStore(ds), index(idx), trie(tr) {}

QueryProcessor::~QueryProcessor() = default;

[[nodiscard]] auto QueryProcessor::processQuery(const std::string& query, std::size_t topK) -> std::vector<RankedResult>
{
    std::unordered_map<DocumentStore::Docid, int> scores;
    auto tokens = strutil.tokenize(query);

    if (!strutil.isValidToken(tokens))
    {
        report.enable_module("QUERY");
        report.log("QUERY", DEBUG_log::WARNING, "Invalid query tokens");
        report.disable_module("QUERY");
        return {};
    }

    for (auto& token : tokens)
    {
        auto normalized = strutil.normalizeword(token);
        auto postings = index.getPostings(normalized);

        if (!postings)
        {
            continue;
        }

        for (const auto& [docid, freq] : *postings)
        {
            scores[docid] += freq;
        }
    }

    std::vector<RankedResult> ranked;
    ranked.reserve(scores.size());

    for (const auto& [docid, score] : scores)
    {
        ranked.push_back({docid, score});
    }

    std::sort(ranked.begin(), ranked.end(),
    [](const RankedResult& a, const RankedResult& b)
    {
        if (a.score != b.score)
        return a.score > b.score;
        return a.docid < b.docid;
    });


    if (topK > 0 && ranked.size() > topK)
    {
        ranked.resize(topK);
    }


    return ranked;
}
