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
#include <regex>
#include <algorithm>

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

    std::string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
    std::deque<std::string> buffer;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        buffer.push_back(line);
        lineNumber++;

        if (buffer.size() > 5) {
            buffer.pop_front();
        }

        for (const auto& word : searchWords) {
            if (line.find(word) != std::string::npos) {
                // Print to console
                std::cout << "Match found in file: " << fileName << " on line " << lineNumber << " with word: " << word << std::endl;

                // Output context lines
                int startLine = std::max(0, lineNumber - static_cast<int>(buffer.size()));
                for (int i = startLine; i < lineNumber; ++i) {
                    resultLines.push_back(fileName + ": Line " + std::to_string(i + 1) + ": " + buffer[i - startLine] + " [Matched word: " + word + "]");
                }
                break;
            }
        }
    }

    return resultLines;
}



// Function to generate a new output file name with an incremented suffix
std::string getNewFileName(const std::string& baseFileName, int index) {
    std::string::size_type pos = baseFileName.find_last_of('.');
    std::string baseName = baseFileName.substr(0, pos);
    std::string extension = (pos != std::string::npos) ? baseFileName.substr(pos + 1) : "";

    std::string newFileName = baseName + std::to_string(index);
    if (!extension.empty()) {
        newFileName += "." + extension;
    } else {
        newFileName += ".txt";
    }

    return newFileName;
}

// Search a directory for files containing specified words and write results to an output file
void searchDirectory(const std::string& directory, const std::set<std::string>& searchWords, const std::string& outputFile, const std::vector<std::string>& extensions) {
    int maxLinesPerFile = 950;
    int fileIndex = 1;
    int currentLineCount = 0;
    std::ofstream outFile;

    auto openNewFile = [&]() {
        if (outFile.is_open()) {
            outFile.close();
        }
        std::string newFileName = getNewFileName(outputFile, fileIndex);
        outFile.open(newFileName);
        if (!outFile.is_open()) {
            std::cerr << "Error opening output file: " << newFileName << std::endl;
            exit(1);
        }
        std::cout << "Created new file: " << newFileName << std::endl; // Log new file creation
        currentLineCount = 0;
        fileIndex++;
    };

    openNewFile(); // Open the first output file

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;

        std::string filePath = entry.path().string();
        std::string fileExtension = entry.path().extension().string();

        if (!fileExtension.empty() && fileExtension[0] == '.') {
            fileExtension = fileExtension.substr(1);
        }

        std::string searchExtension = fileExtension;

        if (std::find(extensions.begin(), extensions.end(), searchExtension) != extensions.end()) {
            auto matchingLines = findWordsInFile(filePath, searchWords);
            for (const auto& line : matchingLines) {
                if (currentLineCount >= maxLinesPerFile) {
                    openNewFile();
                }
                outFile << line << std::endl;
                currentLineCount++;
            }
        }
    }

    if (outFile.is_open()) {
        outFile.close();
    }

    std::cout << "Done! Results are in files starting with " << outputFile << std::endl;
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
        "c", "cpp", "h", "hpp", "cc", "cxx", "hxx",
        "java", "class",
        "py",
        "js", "jsx",
        "rb",
        "php",
        "go",
        "rs",
        "swift",
        "ts", "tsx"
    };

    auto searchWords = loadSearchWords(searchWordsFile);
    searchDirectory(directory, searchWords, outputFile, sourceCodeExtensions);

    std::cout << "Done! Results are in " << outputFile << std::endl;

    return 0;
}
