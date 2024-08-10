/*
 * file: extensions.hpp
 * Header: Extensions for Source Search (C++)
 *
 * Writer: Daniel McGuire
 *
 * Purpose: Provides Source Search with File Extensions.
 */
#ifndef SOURCEEXTENSIONS_H
#define SOURCEEXTENSIONS_H

#include <vector>
#include <string>

const std::vector<std::string> sourceCodeExtensions = { // Below are the extensions:
    "c", "cpp", "h", "hpp", "cc", "cxx", "hxx", // C and C++
    "java", "class", // Java
    "py", "pyc",     // Python
    "js", "jsx",     // JavaScript
    "ts", "tsx",     // TypeScript
    "rb",            // Ruby
    "php",           // PHP
    "go",            // Go
    "rs",            // Rust
    "swift",         // Swift
    "cs",            // C#
    "m", "mm",       // Objective-C, Objective-C++
    "kt", "kts",     // Kotlin
    "scala",         // Scala
    "sh", "bat",     // Shell scripts
    "pl", "pm",      // Perl
    "lua",           // Lua
    "r",             // R language
    "sql",           // SQL
    "html", "htm",   // HTML
    "css",           // CSS
    "xml",           // XML
    "json",          // JSON
    "yaml", "yml",   // YAML
    "dmcsc", "dmcini"// My Proprietary stuff.
};

#endif // SOURCEEXTENSIONS_H
