//------------------------------------------------------------------------------
// GameLogic.h
//------------------------------------------------------------------------------

#pragma once
#include "SettingsManager.h"
#include "DictionaryManager.h"
#include "Logger.h"
#include "UserInput.h"
#include "ConsoleControl.h"


class GameLogic {
public:
    GameLogic(SettingsManager& settings, Logger& logger);
    void run();

private:
    SettingsManager& settings;
    Logger& logger;
    DictionaryManager dictManager;

    void showMainMenu(bool& running);
    void startGame(bool useOnline);
    void updateDictionary();
    void changeWordLimit();

    void playSingle(bool useOnline);
    void playMulti(bool useOnline);
    bool playRound(const std::string& secret, int maxWrong);

    int  selectDifficulty();
    int  wrongFor(int diff) const;
};
