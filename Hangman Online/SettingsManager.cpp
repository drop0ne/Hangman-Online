//------------------------------------------------------------------------------
// SettingsManager.cpp
//------------------------------------------------------------------------------

#include "PCH.h"
#include "SettingsManager.h"

SettingsManager::SettingsManager(const std::wstring& iniFilePath)
    : iniPath(iniFilePath), wordLimit(50), theme(L"Default")
{
    if (!std::filesystem::exists(iniPath)) {
        createDefault();
    }
    loadSettings();
}

void SettingsManager::createDefault() {
    writeInt(L"General", L"WordLimit", wordLimit);
    writeString(L"General", L"Theme", theme);
}

void SettingsManager::loadSettings() {
    wordLimit = readInt(L"General", L"WordLimit", wordLimit);

    std::vector<std::wstring> themes = { L"Default", L"Dark" };
    std::wstring t = readString(L"General", L"Theme", theme.c_str());
    std::wstring valid;
    if (validateEnum(t, themes, valid))
        theme = valid;
}

int SettingsManager::getWordLimit() const {
    return wordLimit;
}
void SettingsManager::setWordLimit(int wl) {
    wordLimit = wl;
    writeInt(L"General", L"WordLimit", wl);
}

std::wstring SettingsManager::getTheme() const {
    return theme;
}
void SettingsManager::setTheme(const std::wstring& t) {
    std::vector<std::wstring> themes = { L"Default", L"Dark" };
    std::wstring valid;
    if (validateEnum(t, themes, valid)) {
        theme = valid;
        writeString(L"General", L"Theme", valid);
    }
}

bool SettingsManager::validateEnum(
    const std::wstring& s,
    const std::vector<std::wstring>& opts,
    std::wstring& out) const
{
    for (auto& o : opts) {
        if (_wcsicmp(s.c_str(), o.c_str()) == 0) {
            out = o;
            return true;
        }
    }
    return false;
}

std::wstring SettingsManager::readString(
    const wchar_t* sec,
    const wchar_t* key,
    const wchar_t* def
) const {
    wchar_t buf[128] = {};
    GetPrivateProfileStringW(sec, key, def, buf, 128, iniPath.c_str());
    return buf;
}

int SettingsManager::readInt(
    const wchar_t* sec,
    const wchar_t* key,
    int def
) const {
    return static_cast<int>(GetPrivateProfileIntW(sec, key, def, iniPath.c_str()));
}

void SettingsManager::writeString(
    const wchar_t* sec,
    const wchar_t* key,
    const std::wstring& val
) const {
    WritePrivateProfileStringW(sec, key, val.c_str(), iniPath.c_str());
}

void SettingsManager::writeInt(
    const wchar_t* sec,
    const wchar_t* key,
    int val
) const {
    writeString(sec, key, std::to_wstring(val));
}
