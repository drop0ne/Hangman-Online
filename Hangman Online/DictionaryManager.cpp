#include "PCH.h"
#include "DictionaryManager.h"

refactor for zerotrust and centrolized error logging and complete data verifucation and exception handling


Using libcurl
Wordnik API
nlohmann / json

the .cpp file
https://api.wordnik.com/v4/words.json/randomWords?hasDictionaryDef=true
&includePartOfSpeech = noun, proper - noun & minCorpusCount = 0
& minLength = 5 & maxLength = -1 & limit = N & api_key = YOUR_API_KEY

std::ifstream infile("words.json");
json j = json::parse(infile);

#include <curl/curl.h>
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    userData->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string DictionaryManager::fetchWordsFromAPI(int count) {
    std::string result;
    CURL* curl = curl_easy_init();
    if (!curl) return result;
    std::string url = "https://api.wordnik.com/v4/words.json/randomWords?hasDictionaryDef=true"
        "&includePartOfSpeech=noun%2Cproper-noun&minCorpusCount=0"
        "&minLength=1&maxLength=-1&limit=" + std::to_string(count) +
        "&api_key=" + apiKey; // apiKey is stored securely
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); // ensure GET&#8203;:contentReference[oaicite:10]{index=10}
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    // (Optional) set timeout, user-agent, SSL options here
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error: Wordnik API request failed\n";
        result.clear();
    }
    return result;
}

json j = json::parse(result);
// j is an array of objects, each with a "word" field
std::vector<std::string> newWords;
for (auto& entry : j) {
    if (entry.contains("word")) {
        newWords.push_back(entry["word"]);
    }
}

json out;
out["words"] = newWords;
std::ofstream outFile("words.json");
outFile << out.dump(4); // dump pretty-prints with indent of 4 spaces

{
    "words": ["apple", "banana", "Chicago", "London", ...]
}

std::ifstream inFile("words.json");
if (inFile) {
    json j = json::parse(inFile);
    if (j.contains("words") && j["words"].is_array()) {
        for (auto& w : j["words"]) {
            localWordList.push_back(w.get<std::string>());
        }
    }
}


the headder.h file
#ifndef DICTIONARYMANAGER_HPP
#define DICTIONARYMANAGER_HPP

#include <string>
#include <vector>

class DictionaryManager {
public:
    DictionaryManager();

    // Load words from local JSON (or defaults if not available)
    void loadLocalDictionary();
    // Fetch new words from API and update local list and file
    bool updateLocalDictionary(int count);
    // Get a random word from the local list (for offline play)
    std::string getRandomLocalWord() const;
    // Get a random word directly from online (without storing)
    std::string getOnlineWord();
    // List dictionary contents (print to console)
    void listLocalDictionary() const;

    // Setters/Getters
    void setWordLimit(int newLimit);
    int getWordLimit() const;
private:
    std::vector<std::string> words;
    int wordLimit;
    std::string apiKey;
    std::string dictFilePath;
    // helper to call Wordnik API
    std::string fetchWordsFromAPI(int count);
};
#endif
