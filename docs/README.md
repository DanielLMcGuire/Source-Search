# Source Search 
Source Search is a C++ application designed to scan source code files for specified words, providing contextual lines around each match. Originally written in Python by a friend and ported to C++ by me, this tool is useful for developers and analysts looking to quickly identify specific terms within large codebases.

### [Download](https://daniellmcguire.github.io/Source-Search-Download/)

## Features

- **Search Words**: Specify a list of words to search for within source code files.
- **Contextual Output**: Includes lines around each match to provide context.
- **File Type Filtering**: Search within specific file extensions. [Available File Extensions](https://github.com/DanielLMcGuire/Source-Scanner/blob/main/src/extensions.hpp) (add more by building from source)
- **Customizable Output**: Results can be written to a specified file or split into multiple files if the output exceeds a line limit.

## Installation

Download the latest release from the [Releases](https://github.com/DanielLMcGuire/Source-Scanner/releases) page on GitHub. Follow the Install Instuctions.

## Usage

```bash
./sourcesearch <searchWordsFile> [<outputFile> <directory>]
```

### Arguments

- `searchWordsFile`: A file containing words to search for, one per line.
- `outputFile`: (Optional) The name of the output file. Defaults to `lines.txt`.
- `directory`: (Optional) The directory to search within. Defaults to the current directory.

### Options

- `--version`: Displays the version of the program.
- `--help`: Shows the help message.

### Example

To search for words listed in `words.txt` within the current directory and save the output to `results.txt`:

```bash
./sourcesearch words.txt results.txt .
```

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, feel free to open an issue or submit a pull request.

### To Do

- Implement multi-threading for faster searching.
- Improve file type filtering based on content rather than extension.
- Enhance the user interface and command-line options.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
