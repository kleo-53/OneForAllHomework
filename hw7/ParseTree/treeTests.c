#include "treeTests.h"
#include "tree.h"

bool testSmallCase()
{
    bool isWorking = true;
    Tree* tree = createAndAdd("(- (+ -1 1) 2)", &isWorking);
    if (isEmpty(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    const int result = doCalculation(tree, &isWorking);
    deleteTree(tree);
    return result == -2 && isWorking;
}

bool testBigCase()
{
    bool isWorking = true;
    Tree* tree = createAndAdd("(-(/ (* 1 14) 2) (+ 10 (- 5 5) ) )", &isWorking);
    if (isEmpty(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    const int result = doCalculation(tree, &isWorking);
    deleteTree(tree);
    return result == -3 && isWorking;
}

bool testWithoutBracketsCase()
{
    bool isWorking = true;
    Tree* tree = createAndAdd("*-/ + * 12 10 1 11  1011 - 3 4", &isWorking);
    if (isEmpty(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    const int result = doCalculation(tree, &isWorking);
    deleteTree(tree);
    return result == 1000 && isWorking;
}

bool testIncorrectDividing()
{
    bool isWorking = true;
    Tree* tree = createAndAdd("/ 3 0", &isWorking);
    if (isEmpty(tree) || !isWorking)
    {
        deleteTree(tree);
        return false;
    }
    const int result = doCalculation(tree, &isWorking);
    deleteTree(tree);
    return !isWorking;
}