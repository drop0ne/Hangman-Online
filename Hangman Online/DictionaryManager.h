#pragma once
#ifndef DICTIONARYMANAGER_HPP
#define DICTIONARYMANAGER_HPP

// The DictionaryManager class handles operations related to managing a local dictionary,
// fetching words from the Wordnik API, and storing them locally. It also manages API key loading
// and handles errors related to fetching data.

class DictionaryManager {
public:
    // Constructor: Initializes the DictionaryManager object and sets up API file path.
    DictionaryManager();

    // loadLocalDictionary: Loads words from the local JSON file. If the file is missing or empty, it creates a new one.
    void loadLocalDictionary();

    // updateLocalDictionary: Fetches new words from the Wordnik API and updates the local dictionary file.
    bool updateLocalDictionary(int count);

    // getRandomLocalWord: Returns a random word from the locally stored dictionary for offline play.
    std::string getRandomLocalWord() const;

    // getOnlineWord: Fetches a random word directly from the Wordnik API without saving it locally.
    std::string getOnlineWord();

    // listLocalDictionary: Prints the contents of the local dictionary to the console.
    void listLocalDictionary() const;

    // setWordLimit: Sets a limit on the number of words in the local dictionary.
    void setWordLimit(int newLimit);

    // getWordLimit: Returns the current word limit for the local dictionary.
    int getWordLimit() const;

private:
    std::vector<std::string> words;   // Stores the list of words loaded from the dictionary
    int wordLimit;                    // The maximum number of words allowed in the dictionary
    std::string apiKey;               // The API key for accessing the Wordnik API
    std::string dictFilePath;         // The path to the local dictionary file

    // fetchWordsFromAPI: Makes an API call to Wordnik to fetch a specified number of random words.
    std::string fetchWordsFromAPI(int count);

	// writeCallback: A helper function used by CURL to store the API response data.
	static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userData);

    // checkAndLoadAPIKey: Checks if the API key file exists and loads the API key. If it's missing or invalid, it creates the file with instructions.
    void checkAndLoadAPIKey();
};

#endif  // DICTIONARYMANAGER_HPP
