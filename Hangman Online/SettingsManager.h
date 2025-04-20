//------------------------------------------------------------------------------
// SettingsManager.h
//------------------------------------------------------------------------------

#pragma once

class SettingsManager {
public:
    explicit SettingsManager(const std::wstring& iniFilePath);
    void loadSettings();
    void createDefault();

    int          getWordLimit() const;
    void         setWordLimit(int);

    std::wstring getTheme()     const;
    void         setTheme(const std::wstring&);

private:
    std::wstring iniPath;
    int          wordLimit;
    std::wstring theme;

    bool validateEnum(const std::wstring&, const std::vector<std::wstring>&, std::wstring&) const;
    std::wstring readString(const wchar_t* sec, const wchar_t* key, const wchar_t* def) const;
    int          readInt(const wchar_t* sec, const wchar_t* key, int def) const;
    void         writeString(const wchar_t* sec, const wchar_t* key, const std::wstring&) const;
    void         writeInt(const wchar_t* sec, const wchar_t* key, int) const;
};
