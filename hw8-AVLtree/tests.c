#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "AVLtree.h"

bool testAddAndInCase()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, "cdef", "root", &isWorking);
    addValue(tree, "bcd", "rootLSon", &isWorking);
    addValue(tree, "rs", "rootRSon", &isWorking);
    addValue(tree, "aaaa", "LLSon", &isWorking);
    addValue(tree, "bdder", "LRSon", &isWorking);
    addValue(tree, "hgv", "RLSon", &isWorking);
    addValue(tree, "zzzzzz", "RRSon", &isWorking);
    addValue(tree, "efg", "RLL", &isWorking);
    addValue(tree, "ddddddd", "root", &isWorking);
    if (!isWorking || !inTree(tree, "hgv", &isWorking) || inTree(tree, "aaab", &isWorking))
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, "ddddddd", "RLLL", &isWorking);
    if (!isBalanced(tree) || !isWorking || !inTree(tree, "ddddddd", &isWorking))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}

bool testDeleteAndInCase()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, "cdef", "root", &isWorking);
    addValue(tree, "bcd", "rootLSon", &isWorking);
    addValue(tree, "rs", "rootRSon", &isWorking);
    addValue(tree, "aaaa", "LLSon", &isWorking);
    addValue(tree, "bdder", "LRSon", &isWorking);
    addValue(tree, "hgv", "RLSon", &isWorking);
    addValue(tree, "zzzzzz", "RRSon", &isWorking);
    addValue(tree, "efg", "RLL", &isWorking);
    addValue(tree, "ddddddd", "root", &isWorking);
    if (!isBalanced(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    bool result = true;
    deleteValue(tree, "ddddddd", &isWorking, &result);
    result = true;
    deleteValue(tree, "hgv", &isWorking, &result);
    result = true;
    deleteValue(tree, "bcd", &isWorking, &result);
    if (!isBalanced(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    result = true;
    deleteValue(tree, "cdef", &isWorking, &result);
    result = true;
    deleteValue(tree, "rs", &isWorking, &result);
    if (!isWorking || inTree(tree, "hgv", &isWorking) || !inTree(tree, "efg", &isWorking) ||
        !inTree(tree, "bdder", &isWorking) || inTree(tree, "cdef", &isWorking) ||
        !inTree(tree, "aaaa", &isWorking) || !inTree(tree, "zzzzzz", &isWorking) || inTree(tree, "bcd", &isWorking))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}

bool testGetValueCase()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, "cdef", "root", &isWorking);
    addValue(tree, "bcd", "rootLSon", &isWorking);
    addValue(tree, "rs", "rootRSon", &isWorking);
    addValue(tree, "aaaa", "LLSon", &isWorking);
    addValue(tree, "bdder", "LRSon", &isWorking);
    addValue(tree, "hgv", "RLSon", &isWorking);
    addValue(tree, "zzzzzz", "RRSon", &isWorking);
    addValue(tree, "efg", "RLL", &isWorking);
    addValue(tree, "ddddddd", "root", &isWorking);
    char* value = getValue(tree, "rs", &isWorking);
    if (!isWorking || value == NULL || strcmp("rootRSon", value) != 0)
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, "ddddddd", "RLLL", &isWorking);
    char* value2 = getValue(tree, "ddddddd", &isWorking);
    char* value3 = getValue(tree, "abracadabra", &isWorking);
    if (!isBalanced(tree) || !isWorking || value2 == NULL || strcmp("RLLL", value2) != 0 || !inTree(tree, "ddddddd", &isWorking) || value3 != NULL)
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}

bool testLeftRotation()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, "aaa", "1", &isWorking);
    addValue(tree, "bbb", "2", &isWorking);
    addValue(tree, "ccc", "3", &isWorking);
    addValue(tree, "ddd", "4", &isWorking);
    addValue(tree, "eee", "5", &isWorking);
    addValue(tree, "fff", "6", &isWorking);
    if (!isWorking)
    {
        deleteTree(tree);
        return false;
    }
    if (!isBalanced(tree))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}

bool testRightRotation()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, "fff", "6", &isWorking);
    addValue(tree, "eee", "5", &isWorking);
    addValue(tree, "ddd", "4", &isWorking);
    addValue(tree, "ccc", "3", &isWorking);
    addValue(tree, "bbb", "2", &isWorking);
    addValue(tree, "aaa", "1", &isWorking);
    if (!isWorking)
    {
        deleteTree(tree);
        return false;
    }
    if (!isBalanced(tree))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}