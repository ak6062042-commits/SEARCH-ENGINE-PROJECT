#ifndef DOCUMENTSTORE_HPP
#define DOCUMENTSTORE_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include "Utils.hpp"
#include "config_debug.hpp"

class DocumentStore{
    public:
        using Docid = std::size_t;
        struct Document
        {
            Docid id;
            std::string filename;
            std::string filepath;
            std::size_t filesize;
        };

    public:
        DocumentStore();
        ~DocumentStore();

        [[nodiscard]] auto addDocument(const std::string& filename,
        const std::string& filepath,std::size_t filesize) -> Docid;
        [[nodiscard]] auto getDocument(Docid id) const -> const Document&;

        [[nodiscard]] auto getFilename(Docid id) const -> const std::string&;
        [[nodiscard]] auto getFilepath(Docid id) const -> const std::string&;
        [[nodiscard]] auto getFilesize(Docid id) const -> std::size_t;

        [[nodiscard]] auto hasDocument(const std::string& filename) const -> bool;
        [[nodiscard]] auto getDocID(const std::string& filename) const -> Docid;

        [[nodiscard]] auto documentCount() const -> std::size_t;
        [[nodiscard]] auto getAllDocuments() const -> const std::vector<Document>&;

    private:
        std::vector<Document> documents;
        std::unordered_map<std::string, Docid> filename_to_id;
        static Utilities utils;
        static DEBUG_log report;
};

#endif