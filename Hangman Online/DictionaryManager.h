//------------------------------------------------------------------------------
// DictionaryManager.h
//------------------------------------------------------------------------------

#pragma once

#ifndef DICTIONARYMANAGER_HPP
#define DICTIONARYMANAGER_HPP


class DictionaryManager {
public:
    DictionaryManager();

    void loadLocalDictionary();
    bool updateLocalDictionary(int count);
    std::string getRandomLocalWord() const;
    std::string getOnlineWord();
    void listLocalDictionary() const;

    void setWordLimit(int newLimit);
    int  getWordLimit() const;

private:
    std::vector<std::string> words;
    int                       wordLimit;
    std::string               apiKey;
    std::string               dictFilePath;

    void checkAndLoadAPIKey();
    std::string fetchWordsFromAPI(int count);
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
};


#endif  // DICTIONARYMANAGER_HPP
