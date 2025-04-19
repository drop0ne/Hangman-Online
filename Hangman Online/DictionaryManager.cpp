#include "PCH.h"
#include "DictionaryManager.h"

// Constructor to initialize DictionaryManager and set file paths.
DictionaryManager::DictionaryManager() : wordLimit(100), dictFilePath("words.json") {
    checkAndLoadAPIKey();
}

// checkAndLoadAPIKey: Checks for the presence of the API key file, validates the key, and creates the file if necessary.
void DictionaryManager::checkAndLoadAPIKey() {
    const std::string apiFileName = "wordnik_api_key.txt";
    std::ifstream infile(apiFileName);

    // If the API key file doesn't exist, create it with instructions.
    if (!infile) {
        std::ofstream outfile(apiFileName);
        outfile << "Please enter your Wordnik API key below:\n";
        outfile << "API Key: <Your_API_Key>\n";
        std::cerr << "API key file missing. Please provide a valid key.\n";
        throw std::runtime_error("API key file missing. Please provide a valid key.");
    }

    // Load and validate the API key.
    std::string key;
    std::getline(infile, key);
    if (key.empty() || key.size() != 49) {  // Key length is 49 char for the API key.
        std::cerr << "Invalid API key.\n";
        throw std::runtime_error("Invalid API key. Please provide a valid key.");
    }

    apiKey = key;  // Store the valid API key
}

// loadLocalDictionary: Loads words from the local JSON file. If the file doesn't exist, it will create a new one.
void DictionaryManager::loadLocalDictionary() {
    std::ifstream inFile(dictFilePath);
    if (inFile) {
        json j;
        inFile >> j;

        if (j.contains("words") && j["words"].is_array()) {
            for (auto& w : j["words"]) {
                words.push_back(w.get<std::string>());
            }
        }
    }
    else {
        std::ofstream outFile(dictFilePath);
        json j;
        j["words"] = {};
        outFile << j.dump(4);  // Create an empty JSON file
    }
}

// updateLocalDictionary: Fetches new words from the Wordnik API and updates the local dictionary file.
bool DictionaryManager::updateLocalDictionary(int count) {
    try {
        std::string result = fetchWordsFromAPI(count);
        if (result.empty()) {
            return false;  // If API call failed, return false.
        }

        json j = json::parse(result);
        std::vector<std::string> newWords;
        for (auto& entry : j) {
            if (entry.contains("word")) {
                newWords.push_back(entry["word"]);
            }
        }

        // Update the local dictionary file with new words.
        json out;
        out["words"] = newWords;
        std::ofstream outFile(dictFilePath);
        outFile << out.dump(4);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating dictionary: " << e.what() << std::endl;
        return false;
    }
}

// fetchWordsFromAPI: Makes the API call to Wordnik to get a specified number of random words.
std::string DictionaryManager::fetchWordsFromAPI(int count) {
    std::string result;
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL.\n";
        return result;
    }

    std::string url = "https://api.wordnik.com/v4/words.json/randomWords?hasDictionaryDef=true"
        "&includePartOfSpeech=noun%2Cproper-noun&minCorpusCount=0"
        "&minLength=1&maxLength=-1&limit=" + std::to_string(count) +
        "&api_key=" + apiKey;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
        return "";
    }

    return result;
}

// writeCallback: This is a helper function used by CURL to store the API response data.
size_t DictionaryManager::writeCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    userData->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// getRandomLocalWord: Returns a random word from the local dictionary for offline use.
std::string DictionaryManager::getRandomLocalWord() const {
    if (words.empty()) {
        return "";
    }
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// getOnlineWord: Fetches a random word directly from the Wordnik API without storing it locally.
std::string DictionaryManager::getOnlineWord() {
    std::string result = fetchWordsFromAPI(1);
    if (result.empty()) {
        return "";
    }

    json j = json::parse(result);
    if (j.size() > 0 && j[0].contains("word")) {
        return j[0]["word"];
    }

    return "";
}

// listLocalDictionary: Lists the contents of the local dictionary to the console.
void DictionaryManager::listLocalDictionary() const {
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }
}

// setWordLimit: Sets the maximum number of words that can be stored in the local dictionary.
void DictionaryManager::setWordLimit(int newLimit) {
    wordLimit = newLimit;
}

// getWordLimit: Returns the current word limit for the local dictionary.
int DictionaryManager::getWordLimit() const {
    return wordLimit;
}
