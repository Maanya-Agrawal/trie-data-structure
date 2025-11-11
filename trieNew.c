#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

// Function to create a new Trie node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Insert a word into the Trie
void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index])
            curr->children[index] = createNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

// Check if a node has children
bool hasChildren(struct TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i])
            return true;
    return false;
}

// Display the Trie in a proper tree-like structure
void displayTrie(struct TrieNode* root, char* prefix, bool* isLast, int level) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            // Print indentation based on tree level
            for (int j = 0; j < level; j++) {
                if (isLast[j])
                    printf("    ");
                else
                    printf("│   ");
            }

            // Find if this child is the last one
            bool lastChild = true;
            for (int k = i + 1; k < ALPHABET_SIZE; k++) {
                if (root->children[k]) {
                    lastChild = false;
                    break;
                }
            }

            printf("%s── %c", lastChild ? "└" : "├", i + 'a');
            if (root->children[i]->isEndOfWord)
                printf(" ●");
            printf("\n");

            isLast[level] = lastChild;
            displayTrie(root->children[i], prefix, isLast, level + 1);
        }
    }
}

// Search for a word in the Trie
bool search(struct TrieNode* root, const char* word) {
    struct TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index])
            return false;
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

// Check if a prefix exists
bool startsWith(struct TrieNode* root, const char* prefix) {
    struct TrieNode* curr = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (!curr->children[index])
            return false;
        curr = curr->children[index];
    }
    return true;
}

// Check if node is empty
bool isEmpty(struct TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i])
            return false;
    return true;
}

// Delete a word from the Trie
struct TrieNode* deleteWord(struct TrieNode* root, const char* word, int depth) {
    if (!root)
        return NULL;

    if (word[depth] == '\0') {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        if (isEmpty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = word[depth] - 'a';
    root->children[index] = deleteWord(root->children[index], word, depth + 1);

    if (isEmpty(root) && !root->isEndOfWord) {
        free(root);
        root = NULL;
    }
    return root;
}

// Menu-driven main function
int main() {
    struct TrieNode* root = createNode();
    int choice;
    char word[100];
    bool isLast[100] = {false};

    printf("=== TRIE OPERATIONS WITH TREE DISPLAY ===\n");
    printf("1. Insert a word\n2. Search a word\n3. Delete a word\n4. Prefix search\n5. Display Trie\n0. Exit\n");

    while (1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word to insert: ");
                scanf("%s", word);
                insert(root, word);
                printf("'%s' inserted successfully.\n", word);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);
                printf(search(root, word) ? "Word found in Trie.\n" : "Word not found.\n");
                break;

            case 3:
                printf("Enter word to delete: ");
                scanf("%s", word);
                root = deleteWord(root, word, 0);
                printf("'%s' deleted (if existed).\n", word);
                break;

            case 4:
                printf("Enter prefix to search: ");
                scanf("%s", word);
                printf(startsWith(root, word) ? "Prefix exists in Trie.\n" : "Prefix not found.\n");
                break;

            case 5:
                printf("\n=== Current Trie Structure ===\n(root)\n");
                displayTrie(root, word, isLast, 0);
                break;

            case 0:
                printf("Exiting... 👋\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
