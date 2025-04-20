//------------------------------------------------------------------------------
// DictionaryManager.cpp
//------------------------------------------------------------------------------

#include "PCH.h"
#include "DictionaryManager.h"

DictionaryManager::DictionaryManager()
    : wordLimit(50), dictFilePath("words.json")
{
    checkAndLoadAPIKey();
    loadLocalDictionary();
}

void DictionaryManager::checkAndLoadAPIKey() {
    const std::string keyFile = "wordnik_api_key.txt";
    std::ifstream in(keyFile);
    if (!in) {
        std::ofstream out(keyFile);
        out << "Enter your Wordnik API key here:";
        throw std::runtime_error("Created '" + keyFile + "'. Please add your API key.");
    }
    std::getline(in, apiKey);
    if (apiKey.empty())
        throw std::runtime_error("API key file is empty.");
}

void DictionaryManager::loadLocalDictionary() {
    words.clear();
    if (std::filesystem::exists(dictFilePath)) {
        std::ifstream f(dictFilePath);
        json j; f >> j;
        for (auto& w : j["words"])
            words.push_back(w.get<std::string>());
    }
    else {
        // initialize empty file
        json j; j["words"] = json::array();
        std::ofstream f(dictFilePath);
        f << j.dump(4);
    }
}

bool DictionaryManager::updateLocalDictionary(int count) {
    try {
        std::string resp = fetchWordsFromAPI(count);
        auto arr = json::parse(resp);
        words.clear();
        for (auto& item : arr) {
            if (item.contains("word"))
                words.push_back(item["word"].get<std::string>());
        }
        json out; out["words"] = words;
        std::ofstream f(dictFilePath);
        f << out.dump(4);
        return true;
    }
    catch (...) {
        return false;
    }
}

std::string DictionaryManager::fetchWordsFromAPI(int count) {
    std::ostringstream url;
    url << "https://api.wordnik.com/v4/words.json/randomWords"
        << "?hasDictionaryDef=true"
        << "&includePartOfSpeech=noun,proper-noun"
        << "&limit=" << count
        << "&api_key=" << apiKey;
    CURL* curl = curl_easy_init();
    if (!curl) return {};
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return response;
}

size_t DictionaryManager::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), total);
    return total;
}

std::string DictionaryManager::getRandomLocalWord() const {
    if (words.empty()) return {};
    return words[rand() % words.size()];
}

std::string DictionaryManager::getOnlineWord() {
    auto resp = fetchWordsFromAPI(1);
    auto arr = json::parse(resp);
    if (!arr.empty() && arr[0].contains("word"))
        return arr[0]["word"].get<std::string>();
    return {};
}

void DictionaryManager::listLocalDictionary() const {
    for (auto& w : words)
        std::wcout << utf8ToWide(w) << L"\n";
    std::wcout << L"Press Enter to continue...";
    std::wstring tmp; std::getline(std::wcin, tmp);
}

void DictionaryManager::setWordLimit(int newLimit) {
    wordLimit = newLimit;
}

int DictionaryManager::getWordLimit() const {
    return wordLimit;
}
