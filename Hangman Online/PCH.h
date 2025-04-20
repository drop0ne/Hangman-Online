#pragma once

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

// Standard headers
#include <stdexcept>
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <locale>
#include <codecvt>
#include <map>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>

// Libcurl and JSON (needed by DictionaryManager.cpp)
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// UTF‑8 / wide‑string conversions
static std::string wideToUtf8(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    int sizeNeeded = WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), (int)wstr.size(),
        nullptr, 0, nullptr, nullptr);
    std::string result(sizeNeeded, 0);
    WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), (int)wstr.size(),
        &result[0], sizeNeeded, nullptr, nullptr);
    return result;
}

static std::wstring utf8ToWide(const std::string& str) {
    if (str.empty()) return {};
    int sizeNeeded = MultiByteToWideChar(
        CP_UTF8, 0,
        str.data(), (int)str.size(),
        nullptr, 0);
    std::wstring result(sizeNeeded, 0);
    MultiByteToWideChar(
        CP_UTF8, 0,
        str.data(), (int)str.size(),
        &result[0], sizeNeeded);
    return result;
}
