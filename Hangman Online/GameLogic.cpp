//------------------------------------------------------------------------------
// GameLogic.cpp
//------------------------------------------------------------------------------
#include "PCH.h"
#include "GameLogic.h"
#include "SettingsManager.h"
#include "DictionaryManager.h"
#include "Logger.h"
#include "UserInput.h"
#include "ConsoleControl.h"


GameLogic::GameLogic(SettingsManager& settings, Logger& logger)
    : settings(settings), logger(logger)
{
    srand((unsigned)time(nullptr));
    dictManager.setWordLimit(settings.getWordLimit());
    logger.logInfo("Initialized with wordLimit=" + std::to_string(settings.getWordLimit()));
}

void GameLogic::run() {
    bool running = true;
    while (running) {
        ConsoleControl::clearScreen();
        showMainMenu(running);
    }
    logger.logInfo("Exiting game loop");
}

void GameLogic::showMainMenu(bool& running) {
    std::wcout << L"=== Hangman ===\n"
        << L"1) New Game (Local)\n"
        << L"2) New Game (Online)\n"
        << L"3) Update Dictionary\n"
        << L"4) List Words\n"
        << L"5) Set Word Limit\n"
        << L"6) Quit\n";
    int choice = UserInput::getIntInRange(1, 6, L"Choice: ");
    switch (choice) {
    case 1: startGame(false);   break;
    case 2: startGame(true);    break;
    case 3: updateDictionary(); break;
    case 4: dictManager.listLocalDictionary(); break;
    case 5: changeWordLimit();  break;
    case 6: running = false;    break;
    }
}

void GameLogic::startGame(bool useOnline) {
    ConsoleControl::clearScreen();
    std::wcout << L"1) Single Player\n2) Multiplayer\n";
    int mode = UserInput::getIntInRange(1, 2, L"Mode: ");
    if (mode == 1) playSingle(useOnline);
    else            playMulti(useOnline);
}

void GameLogic::playSingle(bool useOnline) {
    ConsoleControl::clearScreen();
    int diff = selectDifficulty();
    int maxWrong = wrongFor(diff);
    std::string secret = useOnline
        ? dictManager.getOnlineWord()
        : dictManager.getRandomLocalWord();
    bool won = playRound(secret, maxWrong);

    ConsoleControl::clearScreen();
    std::wstring msg = won ? L"You won!" : L"Game over!";
    std::wcout << msg << L" Word: " << utf8ToWide(secret) << L"\n";
    std::wcout << L"Press Enter..."; std::wstring tmp; std::getline(std::wcin, tmp);
}

void GameLogic::playMulti(bool useOnline) {
    ConsoleControl::clearScreen();
    int np = UserInput::getIntInRange(1, 10, L"Players: ");
    std::vector<std::wstring> names(np);
    for (int i = 0; i < np; ++i)
        names[i] = UserInput::getLine(L"Name " + std::to_wstring(i + 1) + L": ");

    int rounds = UserInput::getIntInRange(1, 10, L"Rounds: ");
    int diff = selectDifficulty();
    int maxWrong = wrongFor(diff);
    std::map<std::wstring, int> scores;
    for (auto& n : names) scores[n] = 0;

    for (int r = 1; r <= rounds; ++r) {
        for (auto& n : names) {
            ConsoleControl::clearScreen();
            std::wcout << n << L"'s turn, Round " << r << L". Enter to play.";
            std::wstring tmp; std::getline(std::wcin, tmp);

            std::string secret = useOnline
                ? dictManager.getOnlineWord()
                : dictManager.getRandomLocalWord();
            bool won = playRound(secret, maxWrong);
            if (won) scores[n]++;

            ConsoleControl::clearScreen();
            std::wstring res = won ? L"Won" : L"Lost";
            std::wcout << n << L" " << res
                << L" Word: " << utf8ToWide(secret)
                << L"\nPress Enter..."; std::getline(std::wcin, tmp);
        }
    }

    ConsoleControl::clearScreen();
    std::wcout << L"Final Scores:\n";
    for (auto& kv : scores)
        std::wcout << kv.first << L": " << kv.second << L"\n";
    std::wcout << L"Press Enter..."; std::wstring tmp; std::getline(std::wcin, tmp);
}

bool GameLogic::playRound(const std::string& secret, int maxWrong) {
    std::string upper;
    for (char c : secret) upper.push_back(toupper(c));
    std::string mask(secret.size(), '_');
    std::string guessed;
    int wrong = 0;

    while (wrong < maxWrong && mask != upper) {
        ConsoleControl::clearScreen();
        std::wcout << L"Misses " << wrong << L"/" << maxWrong << L"\nWord: ";
        for (char c : mask)
            std::wcout << utf8ToWide(std::string(1, c)) << L" ";
        std::wcout << L"\nGuessed: " << utf8ToWide(guessed) << L"\n";
        wchar_t ch = UserInput::getChar(L"Guess: ");
        if (guessed.find((char)ch) != std::string::npos) continue;
        guessed.push_back((char)ch);
        bool found = false;
        for (size_t i = 0; i < upper.size(); ++i)
            if (upper[i] == ch) { mask[i] = ch; found = true; }
        if (!found) ++wrong;
    }
    return mask == upper;
}

int GameLogic::selectDifficulty() {
    ConsoleControl::clearScreen();
    std::wcout << L"1) Easy(8)\n2) Normal(6)\n3) Hard(4)\n";
    return UserInput::getIntInRange(1, 3, L"Select: ");
}

int GameLogic::wrongFor(int diff) const {
    return diff == 1 ? 8 : (diff == 2 ? 6 : 4);
}

void GameLogic::updateDictionary() {
    ConsoleControl::clearScreen();
    std::wcout << L"Updating...";
    bool ok = dictManager.updateLocalDictionary(settings.getWordLimit());
    std::wcout << (ok ? L"Done" : L"Fail") << L"\nPress Enter...";
    std::wstring tmp; std::getline(std::wcin, tmp);
}

void GameLogic::changeWordLimit() {
    ConsoleControl::clearScreen();
    int nl = UserInput::getIntInRange(1, 1000, L"New limit: ");
    settings.setWordLimit(nl);
    dictManager.setWordLimit(nl);
    std::wcout << L"Limit set to " << nl << L"\nPress Enter...";
    std::wstring tmp; std::getline(std::wcin, tmp);
}
