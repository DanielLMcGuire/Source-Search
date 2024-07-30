/*
 * file:
 * Program: OS Info (C++)
 *
 * Writer: Daniel McGuire
 *
 * Purpose: Get OS Info
 */

#include "OSInfo.hpp"
#include <cstdio>
#include <stdexcept>
#include <array>
#include <string>

// If OS = Windows
#ifdef _WIN32
#include <windows.h>
#include <VersionHelpers.h>
// End If
#endif

std::string getOSName() {
    static std::string osName;

    if (!osName.empty()) {
        return osName;
    }

#ifdef _WIN32
    if (IsWindows10OrGreater()) {
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

        if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
            osName = "win32-" + std::to_string(osvi.dwMajorVersion) + "." + std::to_string(osvi.dwMinorVersion);
            if (osvi.dwBuildNumber) {
                osName += "." + std::to_string(osvi.dwBuildNumber);
            }
        } else {
            throw std::runtime_error("Failed to get Windows version.");
        }
    } else {
        osName = "win32-unknown";
    }

#elif __linux__
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen("uname -r", "r");

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    // Remove the trailing newline character
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    osName = "gnulinux-" + result;

#elif __APPLE__
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen("sw_vers -productVersion", "r");

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    // Remove the trailing newline character
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    osName = "darwin-" + result;

#else
    osName = "unknown";
#endif

    return osName;
}
