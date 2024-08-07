/*
 * file: sourcesearch.cpp
 * Program: Source Search (C++)
 *
 * Writer: (Originally) Andrew M.
 * Porter: Daniel McGuire (from Python)
 *
 * Purpose: Search Source Code for Words and include context.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <deque>
#include "extensions.hpp"
#include "version.hpp"
namespace fs = std::filesystem;

void printLogo() {
    const std::string program = "Source Search";
    std::string logo = program + " " + vernum;
    std::cout << logo << '\n';
    std::cout << std::endl;
}
void printHelp(const std::string& programName) {
    printLogo();
    std::cout << "Usage: " << programName << " <searchWordsFile> [<outputFile> <directory>]" << std::endl;
    std::cout << "\nOptions:\n";
    std::cout << "  --version      Show the version of the program\n";
    std::cout << "  --help         Show this help message\n";
}
// Define an enum for the command-line options
// TODO: make this not be this.
enum Option {
    NONE,
    VERSION,
    HELP,
    UNKNOWN
};
// Function to convert string arguments to enum values
Option getOption(const char* arg) {
    if (strcmp(arg, "--version") == 0) {
        return VERSION;
    } else if (strcmp(arg, "--help") == 0) {
        return HELP;
    } else {
        return UNKNOWN;
    }
}
int parseArgs(int argc, char* argv[]) {
    if (argc > 1) {
        // Get the option from the command-line argument
        Option opt = getOption(argv[1]);

        // Switch on the option
        switch (opt) {
            case VERSION:
                std::cout << vernum << std::endl;
                return 1; // Special case handled

            case HELP:
                printHelp(argv[0]);
                return 1; // Special case handled

            case UNKNOWN:
                std::cout << "Unknown option: " << argv[1] << std::endl;
                printHelp(argv[0]);
                return 1; // Error code for unknown option

            default:
                // No valid options, show help
                printHelp(argv[0]);
                return 1; // Indicate that no valid arguments were provided
        }
    } else {
        // No arguments provided, show help
        printHelp(argv[0]);
        return 1; // Indicate that no valid arguments were provided
    }
}// Load words from a file
//TODO: multi-threading
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
    std::set<int> processedLines; // Track processed line numbers
    std::string line;
    int lineNumber = 0;
    const int contextSize = 2; // Number of lines before and after

    while (std::getline(file, line)) {
        buffer.push_back(line);
        lines.push_back(line);
        lineNumber++;

        if (buffer.size() > contextSize * 2 + 1) { // Buffer size for context lines
            buffer.pop_front();
        }

        // Check if the current line contains any search words
        for (const auto& word : searchWords) {
            size_t pos = line.find(word);
            if (pos != std::string::npos) {
                if (processedLines.find(lineNumber) == processedLines.end()) {
                    // Output to console
                    std::cout << fs::path(filePath).filename().string() << ": Found the word '" << word << "' on line: " << lineNumber << std::endl;

                    // Output context lines
                    int startLine = std::max(0, lineNumber - contextSize - 1);
                    int endLine = std::min(static_cast<int>(lines.size()) - 1, lineNumber + contextSize - 1);
                    
                    for (int i = startLine; i <= endLine; ++i) {
                        resultLines.push_back(filePath + ": Line " + std::to_string(i + 1) + ": " + lines[i]);
                    }
                    processedLines.insert(lineNumber);
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

    std::string newFileName = baseName + "_" + std::to_string(index);
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
                    std::cout << "Switching to new file." << std::endl;
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
    printLogo();
    std::cout << "Done! Results are in files starting with " << outputFile << std::endl;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No arguments provided." << std::endl;
        printHelp(argv[0]);
        return 1;
    }

    // Parse arguments and handle special cases
    int result = parseArgs(argc, argv);
    if (result != 0) {
        // If parseArgs returns a non-zero value, it indicates a special case
        return result;
    }

    // If not an error, proceed with normal execution
    printLogo();
    std::string searchWordsFile = argv[1];
    std::string outputFile = (argc > 2) ? argv[2] : "lines.txt";
    std::string directory = (argc > 3) ? argv[3] : ".";

    auto searchWords = loadSearchWords(searchWordsFile);
    searchDirectory(directory, searchWords, outputFile, sourceCodeExtensions);

    return 0;
}

