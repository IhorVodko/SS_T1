#include <iostream>
#include "List.h"


const static int COMMAND_LENGTH = 10;

void CLInterface();

int main() {
    CLInterface();
    return 0;
}

void CLInterface() {
    char** headNode = NULL;
    printf("\nDo you want to initialize a list and continue the program? Type: y/n\n");
    char com;
    scanf("%c", &com);
    if (com == 'y') {
//        printf("Enter a first string to initialize a list:\n");
//        char str[COMMAND_LENGTH];
//        scanf(" %s", str);
        StringListInit(&headNode);
        printf("Type \"p\" to print a list.\n");
        printf("Type \"a\" to add a string.\n");
        printf("Type \"r\" to remove all occurrences of a string in a list.\n");
        printf("Type \"s\" to get a list size.\n");
        printf("Type \"i\" to get the index position of the first occurrence of a string in the list.\n");
        printf("Type \"repl\" to replace every occurrence of the \"before\", in each of the string "
               "list's strings, with \"after\".\n");
        printf("Type \"rd\" to remove duplicate strings from the list.\n");
        printf("Type \"sor\" to sort the list of strings in ascending order by ASCII codes.\n");
        printf("Type \"d\" to destroy the list.\n");
        printf("Type \"q\" to exit.\n\n");
        char comm[COMMAND_LENGTH];
        do {
            printf("Enter a command: \n");
            scanf(" %s", &comm);
            if (!strcmp(comm, "p")) {
                StrListPrint(headNode);
            } else if (!strcmp(comm, "a")) {
                printf("Type a string to add:\n");
                char str[COMMAND_LENGTH];
                scanf(" %s", str);
                StringListAdd(headNode, str);
            } else if (!strcmp(comm, "r")) {
                printf("Type a string to remove:\n");
                char str[COMMAND_LENGTH];
                scanf(" %s", str);
                StringListRemove(&headNode, str);
            } else if (!strcmp(comm, "s")) {
                printf("List size is: %d\n", StringListSize(headNode));
            } else if (!strcmp(comm, "i")) {
                printf("Type a string to search for:\n");
                char str[COMMAND_LENGTH];
                scanf(" %s", str);
                printf("%d\n", StringListIndexOf(headNode, str));
            } else if (!strcmp(comm, "repl")) {
                printf("Type a string to be replaced\n");
                char before[COMMAND_LENGTH];
                scanf(" %s", before);
                printf("Type a string to replace a string above\n");
                char after[COMMAND_LENGTH];
                scanf(" %s", after);
                StringListReplaceInStrings(headNode, before, after);
            } else if (!strcmp(comm, "rd")) {
                StringListRemoveDuplicates(headNode);
            } else if (!strcmp(comm, "sor")) {
                StringListSort(headNode);
            } else if (!strcmp(comm, "d")) {
                StringListDestroy(&headNode);
            } else if (!strcmp(comm, "init")) {
//                printf("Enter a first string to initialize a list:\n");
//                char str[COMMAND_LENGTH];
//                scanf(" %s", str);
                StringListInit(&headNode);
            } else if (!strcmp(comm, "q")) {

            } else {
                printf("Command not found.\n");
            }
        } while (strcmp(comm, "q"));
    } else if (com == 'n') {
        printf("The program has been finished.\n");
    }
}
