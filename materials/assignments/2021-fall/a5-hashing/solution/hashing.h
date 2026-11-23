// Assignment 5 (2021) · hash table for ints and up-to-4-character strings in IntSLLists.
#pragma once

void insertIntoHashTable(int input);
void insertIntoHashTable(const char* input);
bool searchInHashTable(int input);
bool searchInHashTable(const char* input);
void printHashTable();
void clearHashTable();                  // added for testing
int encodeString(const char* input);    // "AAA" -> 656565, -1 if it cannot be encoded
