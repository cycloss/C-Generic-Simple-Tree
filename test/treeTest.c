#include "../src/tree.h"
#include <stdio.h>

#define len(x) sizeof(x) / sizeof(x[0])

void* printStringNode(treeNode* node) {
    char* str = (char*)node->valuep;
    puts(str);
    return NULL;
}

int main() {

    treeNode* root = createNode(&"Beverages");

    char* rootChildren[] = { "Hot", "Cold" };
    char* grandChildren[][2] = { { "Coffee", "Tea" }, { "Juice", "Cola" } };
    for (int i = 0; i < len(rootChildren); i++) {
        treeNode* tn = addValAsNode(root, rootChildren[i]);
        for (int j = 0; j < len(grandChildren[i]); j++) {
            addValAsNode(tn, grandChildren[i][j]);
        }
    }

    puts("Performing depth first traversal:");
    depthFirstTraverse(root, printStringNode);

    puts("Performing level order traversal:");
    levelOrderTraverse(root, printStringNode);

    char* searchVal = "Tea";
    printf("Searching for value: %s\n", searchVal);
    searchTree(root, searchVal, stringComparator) ? puts("Found value") : puts("Failed to find value");

    char* searchVal2 = "Beer";
    printf("Searching for value: %s\n", searchVal2);
    searchTree(root, searchVal2, stringComparator) ? puts("Found value") : puts("Failed to find value");

    freeTree(root, false);
}