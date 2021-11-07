#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* leftSon;
    struct Node* rightSon;
    struct Node* parent;
    int value;
} Node;

typedef enum Direction
{
    left,
    right
} Direction;

void attach(Node* parent, Node* child, Direction direction)
{
    if (direction == left)
        parent->leftSon = child;
    else
        parent->rightSon = child;
    if (child != NULL)
        child->parent = parent;
}

void zig(Node* x)
{
    Node* p = x->parent;
    if (x == p->leftSon) {
        Node*b = x->rightSon;
        attach(x, p, right);
        attach(p, b, left);
    }
    else
    {
        Node* b = x->leftSon;
        attach(x, p, left);
        attach(p, b, right);
    }
    x->parent= NULL;
}

void zigZig(Node* x)
{
    Node* grandGrandParent = x->parent->parent->parent;
    Node* g = x->parent->parent;
    Node* p = x->parent;
    if (x == p->leftSon)
    {
        Node* b = x->rightSon;
        Node* c = p->rightSon;
        attach(p, b, left);
        attach(g, c, left);
        attach(p, g, right);
        attach(x, p, right);
    }
    else
    {
        Node* b = x->leftSon;
        Node* c = p->leftSon;
        attach(p, b, right);
        attach(g, c, right);
        attach(p, g, left);
        attach(x, p, left);
    }
    x->parent = grandGrandParent;
    return;
}

void zigZag(Node* x)
{
    Node* grandGrandParent = x->parent->parent->parent;
    Node* g = x->parent->parent;
    Node* p = x->parent;
    Node* b = x->leftSon;
    Node* c = p->rightSon;
    if (x == p->leftSon)
    {
        attach(x, p, right);
        attach(x, g, left);
        attach(p, b, left);
        attach(g, c, right);
    }
    else
    {
        attach(x, p, left);
        attach(x, g, right);
        attach(p, b, right);
        attach(g, c, left);
    }
    x->parent = grandGrandParent;
    return;
}

Node* splay(Node* x)
{
    if (x->parent == NULL)
    {
        return x;
    }
    if (x->parent->parent == NULL)
    {
        zig(x);
        return x;
    }
    if ((x == x->parent->leftSon && x->parent->parent->leftSon == x->parent) 
        || (x == x->parent->rightSon && x->parent->parent->rightSon == x->parent))
    {
        zigZig(x);
    }
    else 
    {
        zigZag(x);
    }
    return splay(x);
}

Node* createTree()
{
    return NULL;
}

void deleteTreeRecursive(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTreeRecursive(root->leftSon);
    deleteTreeRecursive(root->rightSon);
    free(root);
}

void deleteTree(Node** root)
{
    deleteTreeRecursive(*root);
    *root = NULL;
}

Node* addNode(Node* root, int value)
{
    if (root == NULL)
    {
        Node* newRoot = calloc(1, sizeof(Node));
        newRoot->value = value;
        return newRoot;
    }
    Node* i = root;
    while (i != NULL)
    {
        if (value > i->value)
        {
            if (i->rightSon == NULL)
            {
                Node* newRoot = calloc(1, sizeof(Node));
                newRoot->value = value;
                i->rightSon = newRoot;
                newRoot->parent = i;
                return splay(newRoot);
            }
            i = i->rightSon;
        }
        else if (value == i->value)
        {
            return splay(i);
        }
        else
        {
            if (i->leftSon == NULL)
            {
                Node* newRoot = calloc(1, sizeof(Node));
                newRoot->value = value;
                i->leftSon = newRoot;
                newRoot->parent = i;
                return splay(newRoot);
            }
            i = i->leftSon;
        }
    }
    return root;
}

bool inTree(Node** root, int value)
{
    Node* i = *root;
    while (i != NULL)
    {
        if (value > i->value)
        {
            i = i->rightSon;
        }
        else if (value < i->value)
        {
            i = i->leftSon;
        }
        else
        {
            *root = splay(i);
            return true;
        }
    }
    return false;
}

int main()
{
    Node* ourTree = createTree();
    ourTree = addNode(ourTree, 1);
    ourTree = addNode(ourTree, 2);
    ourTree = addNode(ourTree, 3);
    ourTree = addNode(ourTree, 4);
    bool twoInTree = inTree(&ourTree, 2);
    bool fiveInTree = inTree(&ourTree, 5);
    deleteTree(&ourTree);
}