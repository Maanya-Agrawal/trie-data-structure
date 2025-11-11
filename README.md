# Trie Data Structure in C

This project implements a **Trie (Prefix Tree)** data structure in **C**, supporting the following operations:

- Insertion of words  
- Word search  
- Prefix search  
- Deletion of words  
- Visual display of the Trie structure using tree branches (├──, └──)

## Features
- User input for dynamic word insertion and deletion.
- Clear hierarchical visualization of Trie nodes in the terminal.
- Demonstrates efficient string storage and retrieval.

## How to Run
1. Open Terminal and navigate to the folder containing the file.
2. Compile the program:
   ```bash
   gcc trieNew.c -o trie
   ```
3. Run the executable:
   ```bash
   ./trie
   ```
4. Follow the menu to insert, search, delete, or display the Trie.

## Sample Output
```
(root)
├── c
│   └── a
│       ├── n ●
│       ├── r
│       │   └── d ●
│       └── t ●
└── d
    └── o
        ├── g ●
        └── n
            └── e ●
```

## About Trie
A **Trie (Prefix Tree)** is a tree-based data structure used for storing strings where each node represents a character.  
It allows efficient **prefix-based searching**, making it ideal for autocomplete, spell-checking, and dictionary systems.
