#include "list.h"

//NodeData = 0, so we can check for data using *headNode;
enum Node {NodeData, NodePrev, NodeNext, NodeSize};
#define DataNullTerminator 1

//initializes list
void StringListInit(char*** headNode,  char* str) {
    *headNode = (char**) malloc(NodeSize * sizeof(char*));
    if (*headNode) {
        size_t sizeOfStr = StrLen(str);
        size_t sizeOfStrMemory = (sizeOfStr + DataNullTerminator) * sizeof(char);
        //write str to NodeData
        (*headNode)[NodeData] = (char*) malloc(sizeOfStrMemory * sizeof(char));
        for (size_t i = 0; i <  sizeOfStrMemory; ++i) {
            (*headNode)[NodeData][i] = str[i];
        }
        (*headNode)[NodeData][sizeOfStr] = '\0';
    }
    //if NodeData takes str successful, create prev and next pointers
    if ((*headNode)[NodeData]) {
        ((*headNode)[NodePrev]) = NULL;
        (*headNode)[NodeNext] = NULL;
    }
    printf("List has been initialized.\n\n");
}

//destroy list and set pointer to NULL
//bug: when one node breaks
void StringListDestroy(char*** headNode) {
    if (!*headNode) {
        printf("List is already destroyed.\n");
        return;
    }
    //if only one node in a list
    if(!(*headNode)[NodeNext]) {
        char** currentNode = (char**) (*headNode);
        free(currentNode[NodeData]);
        currentNode[NodeData] = NULL;
        free(*currentNode);
        currentNode = NULL;
    } else {
        char** currentNode = (char**) (*headNode)[NodeNext];
        char** currentNodePrev = (char**) currentNode[NodePrev];
        //while three and more nodes in a list
        while (currentNode[NodeNext]) {
            free(currentNodePrev[NodeData]);
            currentNodePrev[NodeData] = NULL;
            currentNodePrev[NodeNext] = NULL;
            free(*currentNodePrev);
            currentNodePrev = NULL;
            currentNode = (char**) currentNode[NodeNext];
            currentNodePrev = (char**) currentNode[NodePrev];
        }
        //free memory and null the last node
        free(currentNode[NodeData]);
        currentNode[NodeData] = NULL;
        free(*currentNode);
        currentNode = NULL;
    }
    //to make !heaNode == TRUE
    *headNode = NULL;
    printf("List has been destroyed.\n");
}

//returns the number of items in the list
size_t StringListSize( char** headNode) {
    if (!headNode) {
        printf("List needs to be initialized.\n");
        return 0;
    }
    size_t listSize = 0;
    char** currentNode = headNode;
    //iterate through a list
    while (currentNode) {
        currentNode = (char**) currentNode[NodeNext];
        ++listSize;
    }
    currentNode = NULL;
    return listSize;
}

//inserts value at the end of the list
void StringListAdd(char** headNode, String str) {
    if (!headNode) {
        printf("List needs to be initialized.\n");
        return;
    }
    char** currentNode = headNode;
    //go to a last node
    while (currentNode[NodeNext]) {
        currentNode = (char**) currentNode[NodeNext];
    }
    //create a new node and allocate memory
    char** newNode = (char**) malloc(NodeSize * sizeof(char*));
    if (newNode) {
        currentNode[NodeNext] = (char*) newNode;
        for (size_t nodeIter = 0; nodeIter < NodeSize; ++nodeIter) {
            newNode[nodeIter] = (char*) malloc(sizeof(int));
        }
        size_t sizeOfStr = StrLen(str);
        size_t sizeOfStrMemory = (sizeOfStr + DataNullTerminator) * sizeof(char);
        newNode[NodeData] = (char*) realloc(newNode[NodeData], sizeOfStrMemory);
        for (size_t i = 0; i <  sizeOfStrMemory; ++i) {
            newNode[NodeData][i] = str[i];
        }
        newNode[NodeData][sizeOfStr] = '\0';
        //link a new node
        newNode[NodePrev] = (char*) currentNode;
        newNode[NodeNext] = NULL;
        currentNode = NULL;
        printf("A string has been added.\n");
    }
}

//removes all occurrences of str in the list
void StringListRemove(char*** headNode, String str) {
    if (!*headNode) {
        printf("List needs to be initialized.\n");
        return;
    }
    int removedCount = 0;
    //check for an end of a list
    while (*headNode) {
        const size_t stringInListFirst = 0;
        const size_t stringInListLast = StringListSize(*headNode) - 1;
        size_t listIter = 0;
        char **currentNode = *headNode;
        //search for a string in nodes
        while ((listIter <= stringInListLast) && StrComp(currentNode[NodeData], str)) {
            currentNode = (char**) currentNode[NodeNext];
            ++listIter;
        }
        if (listIter > stringInListLast) {
            if (removedCount == 0) {
                printf("The string not found.\n");
            }
            else {
                printf("The String has been removed successfully.\n");
            }
            return;
        } else if (listIter == stringInListFirst) {
            //if string in a first node, move head to next
            char** currentNodeNext = (char**) currentNode[NodeNext];
            *headNode = currentNodeNext;
            currentNodeNext = NULL;
        } else if (listIter == stringInListLast) {
            //if string in a last node, delink last node
            char** currentNodePrev = (char**) currentNode[NodePrev];
            currentNodePrev[NodeNext] = NULL;
            currentNodePrev = NULL;
        } else {
            //if string is in the inside node, delink this node and link the neighboring nodes
            char** currentNodePrev = (char**) currentNode[NodePrev];
            char** currentNodeNext = (char**) currentNode[NodeNext];
            currentNodePrev[NodeNext] = (char*) currentNodeNext;
            currentNodeNext[NodePrev] = (char*) currentNodePrev;
        }
        //free memory and null the node with a string to be removed
        free(currentNode[NodeData]);
        currentNode[NodeData] = NULL;
        currentNode[NodePrev] = NULL;
        currentNode[NodeNext] = NULL;
        free(*currentNode);
        currentNode = NULL;
        removedCount++;
    }
    printf("A string has been removed.\n");
}

//returns the index position of the first occurrence of str in the list
int StringListIndexOf(char** headNode, char* str) {
    if (!headNode) {
        printf("List needs to be initialized");
        return -1;
    }
    //compare listIter and listSize to check if str is not in a list
    size_t listIter = 0;
    size_t listSize = StringListSize(headNode);
    char** currentNode = headNode;
    //iterate through a list
    while (currentNode && StrComp(currentNode[NodeData], str)) {
        currentNode = (char**) currentNode[NodeNext];
        ++listIter;
    }
    currentNode = NULL;
//    printf("%d", listIter);
    return (listIter < listSize) ? listIter : -1;
}

//removes duplicate entries from the list
void StringListRemoveDuplicates(char** headNode) {
    if (!headNode) {
        printf("List needs to be initialized\n");
        return;
    }
    //pointer to be used for an outer loop
    char** headNodeOuter = headNode;
    //pointer to be used for an inner loop
    char** headNodeInner = headNode;
    //three pointers to remove a node with str and link a list again
    char** nodeRemove = NULL;
    char** nodeRemovePrev = NULL;
    char** nodeRemoveNext = NULL;
    int duplicatesCount = 0;
    while (headNodeOuter) {
        while(headNodeInner) {
            if (headNodeOuter != headNodeInner && !StrComp(headNodeOuter[NodeData], headNodeInner[NodeData])) {
                nodeRemove = headNodeInner;
                nodeRemovePrev = (char**) headNodeInner[NodePrev];
                nodeRemoveNext = (char**) headNodeInner[NodeNext];
                headNodeInner = (char**) headNodeInner[NodeNext];
                //if node to be removed is not a first node
                if(nodeRemovePrev) {
                    nodeRemovePrev[NodeNext] = (char*) nodeRemoveNext;
                }
                //if node to be removed is not a last node
                if(nodeRemoveNext) {
                    nodeRemoveNext[NodePrev] = (char*) nodeRemovePrev;
                }
                //free memory and null a node to be removed
                nodeRemove[NodePrev] = NULL;
                nodeRemove[NodeNext] = NULL;
                free(nodeRemove[NodeData]);
                nodeRemove[NodeData] = NULL;
                free(nodeRemove);   //*
                duplicatesCount++;
            }
            // go to the next inner iteration
            else {
                headNodeInner = (char**) headNodeInner[NodeNext];
            }
        }
        //go to the next outer iteration
        headNodeInner = headNode;
        headNodeOuter = (char**) headNodeOuter[NodeNext];
    }
    //null all axillary pointers
    headNodeOuter = NULL;
    headNodeInner = NULL;
    nodeRemove = NULL;
    nodeRemovePrev = NULL;
    nodeRemoveNext = NULL;
    if (duplicatesCount == 0) {
        printf("No duplicates found.\n");
    } else {
        printf("All duplicates have been removed.\n");
    }
}

//replaces every occurrence of the "before", in each of the string list's strings, with "after"
void StringListReplaceInStrings(char** headNode, char* before, char* after) {
    if (!headNode) {
        printf("List needs to be initialized\n");
        return;
    }
    char** currentNode = headNode;
    size_t sizeOfStr = StrLen(after);
    size_t sizeOfMemoryAllocate = (sizeOfStr + DataNullTerminator) * sizeof(char);
    int replacementCount = 0;
    //iterate through a list, looking for a str to be replaced
    while(currentNode) {
        //if found an str to be replaced
        if (!StrComp(currentNode[NodeData], before)) {
            //reallocate memory for a new str
            currentNode[NodeData] = (char*) realloc( currentNode[NodeData],sizeOfMemoryAllocate * sizeof(char));
            //verify memory reallocation was successful
            if (currentNode[NodeData]) {
                //write a new str instead of an old str
                for (size_t i=0; i < sizeOfMemoryAllocate; ++i ) {
                    currentNode[NodeData][i] = after[i];
                }
                currentNode[NodeData][sizeOfStr] = '\0';
            }
            ++replacementCount;
        }
        //if str not found move to a next node
        currentNode = (char**)currentNode[NodeNext];
    }
    currentNode = NULL;
    printf("A sting has been replaced %d times.\n", replacementCount);
}

//sorts the list of strings in ascending order
//algo: bubble sort; time complexity O(n^2), space complexity O(1)
void StringListSort(char** headNode) {
    if (!headNode) {
        printf("List needs to be initialized.\n");
        return;
    }
    char** currentNode = NULL;
    char** currentNodeNext = NULL;
    char** lastNode = NULL;
    //if swappedCount is 0 then a list is sorted
    int swappedCount;
    do {
        swappedCount = 0;
        currentNode = headNode;
        //iterate through a list
        while (currentNode[NodeNext] != (char*) lastNode) {
            currentNodeNext = (char**) currentNode[NodeNext];
            //check weather two adjacent elements are in ascending order, if no - swap
            if (StrComp(currentNode[NodeData], currentNodeNext[NodeData]) > 0) {
                char* NodeSwap = currentNode[NodeData];
                currentNode[NodeData] = currentNodeNext[NodeData];
                currentNodeNext[NodeData] = NodeSwap;
                swappedCount = 1;
            }
            currentNode = currentNodeNext;
        }
        lastNode = currentNode;
    } while(swappedCount);
    printf("A list has been sorted in ascending order.\n");
}

//returns string length
int StrLen(const char* str) {
    const char *s;
    for (s = str; *s; ++s) {
    }
    return (s - str);
}

//compare strings, returns ASCII dif between code numbers; 0 if match
int StrComp(const char* str1, const char* str2) {
    while(*str1) {
        if (*str1 != *str2) {
            break;
        }
        str1++;
        str2++;
    }
    return (*(const unsigned char*)str1 - *(const unsigned char*)str2);
}

//print list
void StrListPrint(char** headNode) {
    if (!headNode) {
        printf("Nothing to print, initialize a list to add a string.\n");
        return;
    }
    size_t sizeOfList = StringListSize(headNode);
    char** currentNode = headNode;
    for (size_t i = 0; i < sizeOfList; ++i) {
        printf("%s | ", currentNode[NodeData]);
        currentNode = (char**) currentNode[NodeNext];
    }
    currentNode = NULL;
    printf("\n");
}
