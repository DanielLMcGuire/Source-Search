/*
 * file: sourcesearch.cpp
 * Program: Source Search (C++)
 *
 * Writer: (Originally) Andrew M.
 * Porter: Daniel McGuire (from Python) (Original is at ../py)
 *
 * Purpose: Search Source Code for Words and include context.
 */

// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <filesystem>
#include <deque>

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

// Find words in a file and return matching lines with context
std::vector<std::string> findWordsInFile(const std::string& filePath, const std::set<std::string>& searchWords) {
    std::vector<std::string> resultLines;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return resultLines;
    }

    // Buffer for storing lines and their numbers
    std::deque<std::string> buffer;
    std::vector<std::string> lines;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        buffer.push_back(line);
        lines.push_back(line);
        lineNumber++;

        if (buffer.size() > 5) { // Buffer size for 2 lines before, 1 current, and 2 lines after
            buffer.pop_front();
        }

        // Check if the current line contains any search words
        for (const auto& word : searchWords) {
            if (line.find(word) != std::string::npos) {
                // Output context lines
                int startLine = std::max(0, lineNumber - static_cast<int>(buffer.size()));
                for (int i = startLine; i < lineNumber; ++i) {
                    resultLines.push_back(filePath + ": Line " + std::to_string(i + 1) + ": " + lines[i]);
                }
                break;
            }
        }
    }

    return resultLines;
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
