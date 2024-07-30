# file: sourcesearch.py
# Program: Source Search (Python) (Originally named Curse Word Search)
#
# Writer: Andrew M.
#
# Updated on 7.30.24 by Daniel McGuire
#
# Purpose: Search Source Code for Words and include context.

# Imports
import os
import logging

# Setup logging
logging.basicConfig(filename='processing.log', level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')

def load_search_words(file_path):
    """Load words from a file and return a set of words."""
    with open(file_path, 'r') as file:
        return {line.strip().lower() for line in file if line.strip()}

def find_words_in_file(file_path, search_words):
    """Find and return lines from a file that contain any of the words with context."""
    matching_lines = []
    context_lines = []  # Buffer to keep context
    try:
        with open(file_path, 'r', errors='ignore') as file:
            # Read all lines first
            lines = file.readlines()
            num_lines = len(lines)

            # Iterate through lines to find matches and collect context
            for i in range(num_lines):
                line = lines[i].strip()
                lower_line = line.lower()

                if any(search_word in lower_line.split() for search_word in search_words):
                    # Collect context: 2 lines before, current line, and 2 lines after
                    start = max(0, i - 2)
                    end = min(num_lines, i + 3)
                    for j in range(start, end):
                        context_lines.append(f"{file_path}: Line {j + 1}: {lines[j].strip()}")
                    context_lines.append("")  # Blank line for separation

    except Exception as e:
        logging.error(f"Error processing file {file_path}: {e}")

    return context_lines

def search_directory(directory, search_words, output_file, extensions):
    """Search through files in a directory for words and write results to output file."""
    with open(output_file, 'w') as outfile:
        for root, _, files in os.walk(directory):
            for file_name in files:
                if file_name.lower().endswith(extensions):
                    file_path = os.path.join(root, file_name)
                    logging.info(f"Processing {file_path}...")
                    matching_lines = find_words_in_file(file_path, search_words)
                    if matching_lines:
                        outfile.write("\n".join(matching_lines) + "\n")
                    # Optionally flush periodically if dealing with very large files
                    # outfile.flush()

def main():
    search_words_file = 'words.txt'
    output_file = 'lines.txt'
    directory = '.'  # Directory to search in (current directory)

    # File extensions to search
    source_code_extensions = (
        '.c', '.cpp', '.h', '.hpp', '.cc', '.cxx', '.hxx',  # C/C++
        '.java', '.class',  # Java
        '.py',  # Python
        '.js', '.jsx',  # JavaScript
        '.rb',  # Ruby
        '.php',  # PHP
        '.go',  # Go
        '.rs',  # Rust
        '.swift',  # Swift
        '.ts', '.tsx'  # TypeScript
    )

    search_words = load_search_words(search_words_file)
    search_directory(directory, search_words, output_file, source_code_extensions)
    logging.info(f"Done! Results are in {output_file}.")

if __name__ == '__main__':
    main()
