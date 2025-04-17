// PCH.h – list your stable headers here
#pragma once

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

// Standard headers
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

#include <curl/curl.h> // Libcurl for HTTP requests
