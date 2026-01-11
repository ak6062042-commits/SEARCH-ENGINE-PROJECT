#include <unordered_map>
#include <string>
#include <vector>
#include<iostream>
#include "Utils.hpp"
#include "config_debug.hpp"
#include "DocumentStore.hpp"

using std::cout;
using std::endl;
Utilities DocumentStore::utils;
DEBUG_log DocumentStore::report;

DocumentStore::DocumentStore() = default;
DocumentStore::~DocumentStore() = default;

[[nodiscard]] auto DocumentStore::addDocument(const std::string& filename,
const std::string& filepath,std::size_t filesize) -> Docid
{
    if (filename_to_id.find(filename) != filename_to_id.end())
        return filename_to_id[filename];

    Docid id = documents.size();

    Document doc;
    doc.id = id;
    doc.filename = filename;
    doc.filepath = filepath;
    doc.filesize = filesize;

    documents.push_back(doc);
    filename_to_id[filename] = id;

    return id;
}

[[nodiscard]] auto DocumentStore::getDocument(Docid id) const -> const Document&
{
    if(id >= documents.size()) [[unlikely]]
    {
        report.enable_module("DOCID");
        report.log("DOCID", DEBUG_log::WARNING, "DocumentStore::getDocument - Docid out of range");
        report.disable_module("DOCID");
        throw std::out_of_range("Invalid Docid");
    }
    return documents[id];
}

[[nodiscard]] auto DocumentStore::getFilename(Docid id) const -> const std::string&
{
    if(id >= documents.size()) [[unlikely]]
    {
        report.enable_module("DOCID");
        report.log("DOCID", DEBUG_log::WARNING, "DocumentStore::getFilename - Docid out of range");
        report.disable_module("DOCID");
        throw std::out_of_range("Invalid Docid");
    }
    return documents[id].filename;
}

[[nodiscard]] auto  DocumentStore::getFilepath(Docid id) const -> const std::string&
{
    if(id >= documents.size()) [[unlikely]]
    {
        report.enable_module("DOCID");
        report.log("DOCID", DEBUG_log::WARNING, "DocumentStore::getFilepath - Docid out of range");
        report.disable_module("DOCID");
        throw std::out_of_range("Invalid Docid");
    }
    return documents[id].filepath;
}

[[nodiscard]] auto DocumentStore::hasDocument(const std::string& filename) const -> bool
{
    return filename_to_id.find(filename) != filename_to_id.end();
}

[[nodiscard]] auto DocumentStore::getDocID(const std::string& filename) const -> Docid
{
    auto it = filename_to_id.find(filename);
    if(it == filename_to_id.end()) throw std::logic_error("Invalid filename");
    return it->second;
}

[[nodiscard]] auto DocumentStore::documentCount() const -> std::size_t
{
    const size_t num_files = documents.size();
    return num_files;
}

[[nodiscard]] auto DocumentStore::getAllDocuments() const -> const std::vector<Document>&
{
    if(documents.empty())
    {
        report.enable_module("documents vector");
        report.log("documents vector", DEBUG_log::ERROR, 
        "DocumentStore::getAllDocuments - vector DATA 404 not found");
        report.disable_module("documents vector");
    }
    return documents;
}
