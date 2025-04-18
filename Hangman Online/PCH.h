// PCH.h – list your stable headers here
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
#include <cwctype>
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
#include <cctype>
#include <algorithm>

#include <curl/curl.h> // Libcurl for HTTP requests
#include <nlohmann/json.hpp> // JSON library for parsing responses
using json = nlohmann::json;

// Global Helper functions for string conversion
std::wstring utf8_to_wide(const std::string& str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wideStr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], len);
    return wideStr;
}

std::string wide_to_utf8(const std::wstring& wstr) {
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], len, nullptr, nullptr);
    return str;
}