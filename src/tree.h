#include <queue.h>

typedef struct {
    void* valuep;
    linkedList* _children;
} treeNode;

treeNode* createNode(void* valuep);
treeNode* addValAsNode(treeNode* parentNode, void* newNodeValue);
void freeTree(treeNode* root, bool freeNodeValues);
void depthFirstTraverse(treeNode* root, void* (*iterator)(treeNode*));
void levelOrderTraverse(treeNode* root, void* (*iterator)(treeNode*));
void* searchTree(treeNode* root, void* searchVal, bool (*comparator)(void*, void*));