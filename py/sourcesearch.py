import os
import logging

# Setup logging
logging.basicConfig(filename='processing.log', level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')

def load_curse_words(file_path):
    """Load curse words from a file and return a set of words."""
    with open(file_path, 'r') as file:
        return {line.strip().lower() for line in file if line.strip()}

def find_curse_words_in_file(file_path, curse_words):
    """Find and return lines from a file that contain any of the curse words."""
    matching_lines = []
    try:
        with open(file_path, 'r', errors='ignore') as file:
            for line in file:
                lower_line = line.lower()
                if any(curse_word in lower_line.split() for curse_word in curse_words):
                    matching_lines.append(f"{file_path}: {line.strip()}")
    except Exception as e:
        logging.error(f"Error processing file {file_path}: {e}")
    return matching_lines

def search_directory(directory, curse_words, output_file, extensions):
    """Search through files in a directory for curse words and write results to output file."""
    with open(output_file, 'w') as outfile:
        for root, _, files in os.walk(directory):
            for file_name in files:
                if file_name.lower().endswith(extensions):
                    file_path = os.path.join(root, file_name)
                    logging.info(f"Processing {file_path}...")
                    matching_lines = find_curse_words_in_file(file_path, curse_words)
                    if matching_lines:
                        outfile.write("\n".join(matching_lines) + "\n")
                    # Optionally flush periodically if dealing with very large files
                    # outfile.flush()

def main():
    curse_words_file = 'words.txt'
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

    curse_words = load_curse_words(curse_words_file)
    search_directory(directory, curse_words, output_file, source_code_extensions)
    logging.info(f"Done! Results are in {output_file}.")

if __name__ == '__main__':
    main()
