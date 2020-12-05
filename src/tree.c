#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void fatalError(char* message) {
    printf("Fatal error: %s\n", message);
    exit(1);
}

treeNode* createNode(void* valuep) {
    treeNode* tn = malloc(sizeof(treeNode));
    linkedList* l = createList();
    if (tn && l) {
        *tn = (treeNode) { valuep, l };
        return tn;
    } else {
        return NULL;
    }
}

treeNode* addValAsNode(treeNode* parentNode, void* newNodeValue) {
    treeNode* newNode = createNode(newNodeValue);
    if (newNode && appendToList(parentNode->_children, newNode)) {
        return newNode;
    } else {
        return NULL;
    }
}

void freeTree(treeNode* root, bool freeNodeValues) {
    int childCount = getListSize(root->_children);
    for (int i = 0; i < childCount; i++) {
        treeNode* child = (treeNode*)getValueAt(root->_children, i);
        freeTree(child, freeNodeValues);
    }
    freeList(root->_children, freeNodeValues);
    free(root);
}

void depthFirstTraverse(treeNode* root, void* (*iterator)(treeNode*)) {
    iterator(root);
    int childCount = getListSize(root->_children);
    for (int i = 0; i < childCount; i++) {
        treeNode* child = (treeNode*)getValueAt(root->_children, i);
        depthFirstTraverse(child, iterator);
    }
}

void levelOrderTraverse(treeNode* root, void* (*iterator)(treeNode*)) {

    queue* q = createQueue();
    if (!q) {
        fatalError("Failed to create queue");
    }

    enqueue(q, root);

    for (treeNode* tn = (treeNode*)dequeue(q); tn; tn = (treeNode*)dequeue(q)) {
        iterator(tn);
        for (node* n = tn->_children->head; n; n = n->next) {
            enqueue(q, n->value);
        }
    }
}

static void searchTreeHelper(treeNode* root, void* searchVal, bool (*comparator)(void*, void*), void** result) {

    if (comparator(root->valuep, searchVal)) {
        *result = root->valuep;
    } else if (*result) {
        return;
    }

    for (node* n = root->_children->head; n; n = n->next) {
        treeNode* child = (treeNode*)n->value;
        searchTreeHelper(child, searchVal, comparator, result);
    }
}

void* searchTree(treeNode* root, void* searchVal, bool (*comparator)(void*, void*)) {
    void* res = NULL;
    searchTreeHelper(root, searchVal, comparator, &res);
    return res;
}
