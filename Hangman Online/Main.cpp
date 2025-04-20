
//------------------------------------------------------------------------------
// main.cpp
//------------------------------------------------------------------------------
#include "PCH.h"

int wmain() {
    // Quick JSON test
    json j;
    j["key"] = "value";
    std::wcout << utf8ToWide(j.dump(4)) << L"\n";

    system("pause");
    return 0;
}
