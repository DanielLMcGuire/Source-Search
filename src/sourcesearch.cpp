
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Load words from a file (obv previously for curse words lol)
std::set<std::string> loadCurseWords(const std::string& filePath) {
    std::set<std::string> curseWords;
    std::ifstream file(filePath);
    std::string word;
    while (file >> word) {
        curseWords.insert(word);
    }
    return curseWords;
}

// Find words in a file and return matching lines
std::vector<std::string> findCurseWordsInFile(const std::string& filePath, const std::set<std::string>& curseWords) {
    std::vector<std::string> matchingLines;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            if (curseWords.find(word) != curseWords.end()) {
                matchingLines.push_back(filePath + ": " + line);
                break;
            }
        }
    }
    return matchingLines;
}

// Search a directory for files containing curse words and write results to an output file
void searchDirectory(const std::string& directory, const std::set<std::string>& curseWords, const std::string& outputFile, const std::vector<std::string>& extensions) {
    std::ofstream outFile(outputFile);
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;

        std::string filePath = entry.path().string();
        for (const auto& ext : extensions) {
            if (filePath.size() >= ext.size() && filePath.substr(filePath.size() - ext.size()) == ext) {
                auto matchingLines = findCurseWordsInFile(filePath, curseWords);
                for (const auto& line : matchingLines) {
                    outFile << line << std::endl;
                }
                break;
            }
        }
    }
}

int main() {
    std::string curseWordsFile = "words.txt";
    std::string outputFile = "lines.txt";
    std::string directory = ".";  // Directory to search in (current directory)

    // File extensions to search
    std::vector<std::string> sourceCodeExtensions = {
        ".c", ".cpp", ".h", ".hpp", ".cc", ".cxx", ".hxx",  // C/C++
        ".java", ".class",  // Java
        ".py",  // Python
        ".js", ".jsx",  // JavaScript
        ".rb",  // Ruby
        ".php",  // PHP
        ".go",  // Go
        ".rs",  // Rust
        ".swift",  // Swift
        ".ts", ".tsx"  // TypeScript
    };

    auto curseWords = loadCurseWords(curseWordsFile);
    searchDirectory(directory, curseWords, outputFile, sourceCodeExtensions);

    std::cout << "Done! Results are in " << outputFile << std::endl;

    return 0;
}
