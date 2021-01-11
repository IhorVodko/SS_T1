#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

/*--------------------------user interface functions--------------------------*/
//initializes list
void StringListInit(char*** headNode, char* str);
//destroy list and set pointer to NULL
void StringListDestroy(char*** headNode);
//inserts value at the end of the list
void StringListAdd(char** headNode, String str);
//removes all occurrences of str in the list
void StringListRemove(char*** headNode, char* str);
//returns the number of items in the list
size_t StringListSize(char** headNode);
//returns the index position of the first occurrence of str in the list
int StringListIndexOf(char** headNode, char* str);
//removes duplicate entries from the list
void StringListRemoveDuplicates(char** headNode);
//replaces every occurrence of the "before", in each of the string list's strings, with "after"
void StringListReplaceInStrings(char** headNode, char* before, char* after);
//sorts the list of strings in ascending order
void StringListSort(char** headNode);
/*--------------------------utility functions--------------------------*/
//returns string length
int StrLen(const char* str);
//compare strings, if match returns 0, otherwise ASCII dif
int StrComp(const char* str1, const char* str2);
//print list
void StrListPrint(char** headNode);
