/*
file: sourcesearch.cpp
Program: Source Search (C++)

Writer: (Originally) Andrew M.

Porter: Daniel McGuire (from Python) (Original is at ../py)

Purpose: Search Source Code for Words.
*/

// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Load words from a file
std::set<std::string> loadSearchWords(const std::string& filePath) {
    std::set<std::string> searchWords;
    std::ifstream file(filePath);
    std::string word;
    while (file >> word) {
        searchWords.insert(word);
    }
    return searchWords;
}

// Find words in a file and return matching lines
std::vector<std::string> findWordsInFile(const std::string& filePath, const std::set<std::string>& searchWords) {
    std::vector<std::string> matchingLines;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            if (searchWords.find(word) != searchWords.end()) {
                matchingLines.push_back(filePath + ": " + line);
                break;
            }
        }
    }
    return matchingLines;
}

// Search a directory for files containing specified words and write results to an output file
void searchDirectory(const std::string& directory, const std::set<std::string>& searchWords, const std::string& outputFile, const std::vector<std::string>& extensions) {
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        return;
    }

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;

        std::string filePath = entry.path().string();
        std::string fileExtension = entry.path().extension().string();

        if (std::find(extensions.begin(), extensions.end(), fileExtension) != extensions.end()) {
            auto matchingLines = findWordsInFile(filePath, searchWords);
            for (const auto& line : matchingLines) {
                outFile << line << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <searchWordsFile> [<outputFile> <directory>]" << std::endl;
        return 1;
    }

    std::string searchWordsFile = argv[1];
    std::string outputFile = (argc > 2) ? argv[2] : "lines.txt";
    std::string directory = (argc > 3) ? argv[3] : ".";

    // File extensions to search
    std::vector<std::string> sourceCodeExtensions = {
        ".c", ".cpp", ".h", ".hpp", ".cc", ".cxx", ".hxx",
        ".java", ".class",
        ".py",
        ".js", ".jsx",
        ".rb",
        ".php",
        ".go",
        ".rs",
        ".swift",
        ".ts", ".tsx"
    };

    auto searchWords = loadSearchWords(searchWordsFile);
    searchDirectory(directory, searchWords, outputFile, sourceCodeExtensions);

    std::cout << "Done! Results are in " << outputFile << std::endl;

    return 0;
}
