# Trie-Based Autocomplete System

A C++ implementation of autocomplete/word suggestion using Trie data structure.

## Features
- Insert and search words efficiently
- Autocomplete suggestions (up to 5 words)
- Prefix-based word search
- File-based dictionary loading

## How to Run
1. Compile: `g++ main.cpp -o autocomplete`
2. Run: `./autocomplete`

## Usage
- The program loads words from `fileToRead.txt`
- Enter a prefix to get word suggestions

## Example
```
Enter the prefix: consider
---Suggestions---
consider considerability considerable considerableness considerably 
```

## Technologies
- C++ 11/14
- STL (Standard Template Library)
- Trie Data Structure
