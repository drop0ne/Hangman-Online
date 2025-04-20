
//------------------------------------------------------------------------------
// main.cpp
//------------------------------------------------------------------------------

#include "PCH.h"
#include "SettingsManager.h"
#include "Logger.h"
#include "GameLogic.h"

int wmain()
{
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    try {
        // Load settings (creates .ini if missing)
        SettingsManager settings(L".\\HangmanSettings.ini");
        // Set up logging
        Logger logger;
        // Launch the game
        GameLogic game(settings, logger);
        game.run();
    }
    catch (const std::exception& e) {
        // Fatal error—report and exit nonzero
        std::wcerr << L"Fatal error: "
            << utf8ToWide(e.what())
            << std::endl;
        curl_global_cleanup();
        return 1;
    }

    // Clean up libcurl
    curl_global_cleanup();
    return 0;
}