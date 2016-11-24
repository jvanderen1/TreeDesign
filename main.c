/*******************************************************************************************************************************************
 * Joshua Van Deren
 * General Programming
 * Program Tree_Design
 *
 * Program to print out a binary tree given a level-order traversal and in-order traversal.
 *
 * In level-order:
 *  1) The FIRST node is the root
 *  2) The LAST node is the deepest node
 *
 * Key terms:
 *  level: height from top-most node down to the deepest node (also known as simply "height").
 *  parentLayer: set of nodes in the level above the next set of nodes 1 level below.
 *  childLayer: set of nodes in the level below the next set of nodes 1 level above.
 *  elder node: ancestors of a specific node, connected by edges.
 *  siblings: nodes of the same parent.
 *  relatives: nodes of the same childLayer.
 *  Thabit Number: set of numbers that follow a sequence defined as the closed form function: T(n) = 3 * 2 ^ n - 1
 *
 *  *** NOTE: Certain combinations are impossible to have. Will print out INCORRECTLY. ***
 *   (i.e. level-order: LSFD, in-order: FDLS)
 */

/******************* #include DIRECTIVES **************************************************************************************************/
#include <stdio.h>
#include <string.h> /* Used for strlen(). */
#include <math.h>   /* Used for pow(). */

/******************* #define DIRECTIVES ***************************************************************************************************/
#define CHARACTERS_IN_ALPHABET 28 /* 2 extra integers added for the return character and NULL terminator. */

/******************************************************************************************************************************************/

int checkUserInput(char inOrder[], char levelOrder[]);

void deepestNodeLevelCheck(char *inOrder, char *levelOrder, int inOrderDeepestNodeLocation, int *levelNumbers, int *levelOrderCheck, size_t nodes);

void printOutTree(char inOrder[], char levelOrder[], int levelNumber);
void checkLayers(char inOrder[], char levelOrder[], int level, int *levelOrderNodeIndex, int *potentialLevelOrderSubTreeIndex, int inverseLevel, char *parentLayer);
void printLayers(char childLayer[], int level, int numberOfNodesInParentLayer);

char checkForLeftSubTree(char inOrder[], int inOrderNodeIndex, char potentialSubTree);
char checkForRightSubTree(char inOrder[], int inOrderNodeIndex, char potentialSubTree);

int main(void) {
    char inOrder[CHARACTERS_IN_ALPHABET], levelOrder[CHARACTERS_IN_ALPHABET];
    char root, deepestNode;
    size_t nodes;
    int inOrderRootIndex = 0, inOrderDeepestNodeIndex = 0;
    int levelOrderCheck;
    int levels = 1;
    int returnValue;

    /****** Ask for user input *****************************/

    do {
        printf("Please, only enter capital letters from the alphabet for the traversal.\n");
        printf("Also, no duplicate characters allowed.\n\n");

        printf("Enter the sequence of level-order traversal: ");
        fgets(levelOrder, CHARACTERS_IN_ALPHABET, stdin);

        printf("Enter the sequence of in-order traversal: ");
        fgets(inOrder, CHARACTERS_IN_ALPHABET, stdin);

        returnValue = checkUserInput(inOrder, levelOrder);

        if (returnValue < 0)
            printf("INCORRECT input. Try again.\n");
    } while (returnValue < 0);

    /*******************************************************/

    nodes = (size_t)returnValue;

    inOrder[nodes] = '\0';     /* Sets inOrder and levelOrder null terminator. */
    levelOrder[nodes] = '\0';

    root = levelOrder[0];                 /* The root will ALWAYS be at the start of the level-order traversal. */
    deepestNode = levelOrder[nodes - 1];  /* The deepest node will ALWAYS be at the end of the level-order traversal. */

    /******* Locate specific nodes ********************************************/

    while (root != inOrder[inOrderRootIndex])               /* Locates the root within the in-order traversal. */
        inOrderRootIndex++;

    while (deepestNode != inOrder[inOrderDeepestNodeIndex]) /* Locates the deepest node within the in-order traversal. */
        inOrderDeepestNodeIndex++;

    /******* Determines how to find the height ********************************/

    if (nodes == 0)                               /* No nodes were entered. */
        printf("No nodes were entered.\n");

    else if (nodes == 1)                          /* Only 1 node was entered. */
        printf("\n\n%c\n\n", levelOrder[0]);

    else                                          /* Deepest node is to the LEFT or RIGHT of the root within the in-order traversal. */
    {
        levelOrderCheck = (int)nodes - 2;
        deepestNodeLevelCheck(inOrder, levelOrder, inOrderDeepestNodeIndex, &levels, &levelOrderCheck, nodes);
        printOutTree(inOrder, levelOrder, levels);
    }
    
    return 0;
}

void deepestNodeLevelCheck(char *inOrder, char *levelOrder, int inOrderDeepestNodeLocation, int *levelNumbers, int *levelOrderCheck, size_t nodes) {
/***** Checks the left and right subtrees levels of the deepest node. *********************************************************************/
    int leftinOrderNodeChecking = inOrderDeepestNodeLocation - 1;  /* Possible parent trees are ALWAYS to the left or right of the deepest node. */
    int rightinOrderNodeChecking = inOrderDeepestNodeLocation + 1;
    int levelOrderRootIndex = 0; /* The root will ALWAYS be located at the beginning of the level order traversal. */
    char checkArray[nodes + 1];
    int checkNode = 0;

    strncpy(checkArray, inOrder, nodes + 1);

    while ((*levelOrderCheck) != levelOrderRootIndex) /* Checks level order between the root and the deepest node. */
    {
        if (checkArray[leftinOrderNodeChecking] == levelOrder[*levelOrderCheck])       /* Left parent/elder node was found. */
        {
            checkArray[leftinOrderNodeChecking] = '#';
            leftinOrderNodeChecking--;  /* Possible left elder node now moved to the left 1 from the deepest node within inOrder. */
            (*levelNumbers)++;
        }

        else if (checkArray[rightinOrderNodeChecking] == levelOrder[*levelOrderCheck]) /* Right parent/elder node was found. */
        {
            checkArray[rightinOrderNodeChecking] = '#';
            rightinOrderNodeChecking++; /* Possible right elder node now moved to the right 1 from the deepest node within inOrder. */
            (*levelNumbers)++;
        }

        else /* Neither parent/elder was found, and node will be skipped over during later checking. */
        {
            while (checkArray[checkNode] != levelOrder[*levelOrderCheck])
                checkNode++;

            checkArray[checkNode] = '#';
            checkNode = 0;
        }

        while (checkArray[leftinOrderNodeChecking] == '#')
            leftinOrderNodeChecking--;

        while (checkArray[rightinOrderNodeChecking] == '#')
            rightinOrderNodeChecking++;

        (*levelOrderCheck)--;
    }
}

int checkUserInput(char inOrder[], char levelOrder[])
/***** Checks to make sure that the user input is correct for a possible in-order and level-order traversal. ******************************/
{
    int checkIndex1, checkIndex2;
    int characterCount = 0;
    int inOrderArraySize = (int)strlen(inOrder) - 1;
    int levelOrderArraySize = (int)strlen(levelOrder) - 1;

    if (inOrderArraySize != levelOrderArraySize)
        return -1;

    for (checkIndex1 = 0; checkIndex1 < inOrderArraySize; checkIndex1++)
    {
        for (checkIndex2 = 0; checkIndex2 < levelOrderArraySize; checkIndex2++)
            if (inOrder[checkIndex1] == levelOrder[checkIndex2])
                characterCount += 1;

        if (characterCount < 1)       /* A character from inOrder is missing from levelOrder. */
            return -2;

        else if (characterCount > 1)  /* Multiple characters from inOrder are in levelOrder. */
            return -3;

        characterCount = 0;
    }

    for (checkIndex1 = 0; checkIndex1 < levelOrderArraySize; checkIndex1++)
    {
        for (checkIndex2 = 0; checkIndex2 < inOrderArraySize; checkIndex2++)
            if (inOrder[checkIndex1] == levelOrder[checkIndex2])
                characterCount += 1;

        if (characterCount < 1)      /* A character from levelOrder is missing from inOrder. */
            return -4;

        else if (characterCount > 1) /* Multiple characters from levelOrder are in inOrder. */
            return -5;

        characterCount = 0;
    }

    for (checkIndex1 = 0; checkIndex1 < inOrderArraySize; checkIndex1++)
        if (inOrder[checkIndex1] < 'A' || inOrder[checkIndex1] > 'Z')       /* A character outside the alphabet (capital) was entered in inOrder. */
            return -6;

    for (checkIndex2 = 0; checkIndex2 < inOrderArraySize; checkIndex2++)
        if (levelOrder[checkIndex2] < 'A' || levelOrder[checkIndex2] > 'Z') /* A character outside the alphabet (capital) was entered in levelOrder. */
            return -7;

    return inOrderArraySize;
}

char checkForLeftSubTree(char inOrder[], int inOrderNodeIndex, char potentialSubTree) {
/***** Checks to find potential left subtrees. ********************************************************************************************/
    int inOrderCheckForSubTree = inOrderNodeIndex - 1;

    while ((inOrderCheckForSubTree >= 0) && (inOrder[inOrderCheckForSubTree] != '#')) {
        if (inOrder[inOrderCheckForSubTree] == potentialSubTree)
            return inOrder[inOrderCheckForSubTree];   /* Sub-tree was found (returns character). */

        inOrderCheckForSubTree--;
    }

    return '#';                                       /* No sub-tree was found (returns '#'). */
}

char checkForRightSubTree(char inOrder[], int inOrderNodeIndex, char potentialSubTree) {
/***** Checks to find potential right subtrees. *******************************************************************************************/
    int inOrderCheckForSubTree = inOrderNodeIndex + 1;

    while ((inOrder[inOrderCheckForSubTree] != '\0') && (inOrder[inOrderCheckForSubTree] != '#')) {
        if (inOrder[inOrderCheckForSubTree] == potentialSubTree)
            return inOrder[inOrderCheckForSubTree];   /* Sub-tree was found (returns character). */

        inOrderCheckForSubTree++;
    }

    return '#';                                       /* No sub-tree was found (returns '#'). */
}

void printLayers(char childLayer[], int level, int numberOfNodesInParentLayer)
/***** Prints out subtrees of all parent nodes. *******************************************************************************************/
{
    int checkNode;
    int branchIteration;
    int inbetweenSpaceIteration;
    int spaceIteration;

    int topLeftSpaces = 3 * (int)pow(2, level) - 1;     /* Spaces follow a Thabit Number sequence (3 * 2^n - 1). */
    int branchSpaces = 3 * (int)pow(2, level - 1) - 1;

    if (branchSpaces < 1) /* Thabit Number DOES NOT apply to the last level. */
        branchSpaces = 1;

    for (branchIteration = 1; branchIteration <= branchSpaces; branchIteration++)
    {
        for (spaceIteration = 1; spaceIteration <= (topLeftSpaces - branchIteration); spaceIteration++) /* Prints out left-most spaces. */
            printf(" ");


        for (checkNode = 0; checkNode < numberOfNodesInParentLayer; checkNode++)
        {
            if (childLayer[2 * checkNode] != '#')    /* Print out '/' if left node exists. */
                printf("/");

            else                                     /* Don't print out anything if left node doesn't exist. */
                printf(" ");

            for (inbetweenSpaceIteration = 1; inbetweenSpaceIteration <= (2 * branchIteration) - 1; inbetweenSpaceIteration++) /* Prints out spaces between sibling branches. */
                printf(" ");

            if (childLayer[2 * checkNode + 1] != '#') /* Print out '\' if right node exists. */
                printf("\\");

            else                                      /* Don't print out anything if right node doesn't exist. */
                printf(" ");

            if (checkNode + 1 != numberOfNodesInParentLayer) /* Prints out spaces between relative branches. */
                for (inbetweenSpaceIteration = 1; inbetweenSpaceIteration <= (2 * topLeftSpaces) - 2 * branchIteration + 1; inbetweenSpaceIteration++)
                    printf(" ");
        }

        printf("\n");
    }

    if (branchSpaces > 1) /* Do this if not on the last level. */
    {
        for (spaceIteration = 1; spaceIteration <= branchSpaces; spaceIteration++) /* Prints out left-most spaces. */
            printf(" ");

        for (checkNode = 0; checkNode < numberOfNodesInParentLayer; checkNode++)
        {
            if (childLayer[2 * checkNode] != '#')             /* Print out left node if exists. */
                printf("%c", childLayer[2 * checkNode]);

            else                                              /* Don't print out anything if left node doesn't exist. */
                printf(" ");

            for (inbetweenSpaceIteration = 1; inbetweenSpaceIteration <= topLeftSpaces; inbetweenSpaceIteration++) /* Prints out spaces between sibling nodes. */
                printf(" ");

            if (childLayer[2 * checkNode + 1] != '#')         /* Print out right node if exists. */
                printf("%c", childLayer[2 * checkNode + 1]);

            else                                              /* Don't print out anything if right node doesn't exist. */
                printf(" ");

            if (checkNode + 1 != numberOfNodesInParentLayer)  /* Prints out spaces between relative nodes. */
                for (inbetweenSpaceIteration = 1; inbetweenSpaceIteration <= topLeftSpaces; inbetweenSpaceIteration++)
                    printf(" ");
        }
    }

    else /* Do this if on last level. */
    {
        for (checkNode = 0; checkNode < numberOfNodesInParentLayer; checkNode++)
        {
            if (childLayer[2 * checkNode] != '#')             /* Print out left node if exists. */
                printf("%c", childLayer[2 * checkNode]);

            else                                              /* Don't print out anything if left node doesn't exist. */
                printf(" ");

            for (inbetweenSpaceIteration = 1; inbetweenSpaceIteration <= 3; inbetweenSpaceIteration++) /* Prints out spaces between sibling nodes. */
                printf(" ");

            if (childLayer[2 * checkNode + 1] != '#')         /* Print out right node if exists. */
                printf("%c", childLayer[2 * checkNode + 1]);

            else                                              /* Don't print out anything if right node doesn't exist. */
                printf(" ");

            if (checkNode + 1 != numberOfNodesInParentLayer)
                printf(" ");                                  /* Prints out space between relative nodes (and won't print last node's space). */
        }
    }

    printf("\n");
}

void checkLayers(char inOrder[], char levelOrder[], int level, int *levelOrderNodeIndex, int *potentialLevelOrderSubTreeIndex, int inverseLevel, char *parentLayer)
/***** Will produce an array for the parent and child nodes and figure out which nodes are empty. ******************************************
****** These arrays will be used to determine which nodes are empty and which ones are not. ***********************************************/
{
    int numberOfNodesInParentLayer = (int) pow(2, inverseLevel); /* There will ALWAYS be 2^n nodes for the parent, where n = inverse level. */
    int numberOfNodesInChildLayer = 2 * numberOfNodesInParentLayer; /* There will ALWAYS be 2 * p nodes for the children, where p = number of parents in parent layer. */
    char childLayer[numberOfNodesInChildLayer]; /* Creates array for all children to be stored. */

    int checkNode;
    int inOrderNodeIndex = 0; /* Used to find in-order node location. */

    for (checkNode = 0; checkNode < numberOfNodesInParentLayer; checkNode++) {

        if (parentLayer[checkNode] == '#') {       /* If parent is empty, make children empty too. */
            childLayer[2 * checkNode] = '#';
            childLayer[2 * checkNode + 1] = '#';
        }

        else {
            while (inOrder[inOrderNodeIndex] != parentLayer[checkNode]) /* Locate node within inOrder. */
                inOrderNodeIndex++;

            inOrder[inOrderNodeIndex] = '#';                  /* Replace node with '#' for algorithmic purposes. */

            childLayer[2 * checkNode] = checkForLeftSubTree(inOrder, inOrderNodeIndex, levelOrder[*potentialLevelOrderSubTreeIndex]);        /* Checks left sub tree. */

            if (childLayer[2 * checkNode] != '#')             /* If the left sub tree exists, start moving on. */
                (*potentialLevelOrderSubTreeIndex)++;

            childLayer[(2 * checkNode) + 1] = checkForRightSubTree(inOrder, inOrderNodeIndex, levelOrder[*potentialLevelOrderSubTreeIndex]); /* Checks right sub tree. */

            if (childLayer[(2 * checkNode) + 1] != '#')
                (*potentialLevelOrderSubTreeIndex)++;

            inOrderNodeIndex = 0;      /* Resets inOrderNodeIndex back to 0. */
            (*levelOrderNodeIndex)++;  /* Moves forward to find next node in level-order. */
        }
    }

    /****** Actual printing here ******************************/

    printLayers(childLayer, level, numberOfNodesInParentLayer);

    /**********************************************************/

    if (level > 0) /* Function is RECURSIVE; will continue until levels drop to 0. */
        checkLayers(inOrder, levelOrder, level - 1, levelOrderNodeIndex, potentialLevelOrderSubTreeIndex, inverseLevel + 1, childLayer);
}

void printOutTree(char inOrder[], char levelOrder[], int levelNumber)
/****** Prints out the root of the tree and prepares to use the checkLayers() function. ***************************************************/
{
    char initialCharToBePassed; /* Passes in an array to the function checkLayers(). */
    int levelOrderNodeIndex = 1;
    int potentialSubTreeIndex = 1;

    int spaceIteration;
    int leftSpaces = 3 * (int)pow(2, levelNumber - 1) - 1; /* Number of left spaces will be a Thabit Number. */

    printf("\n\n");

    for (spaceIteration = 1; spaceIteration <= leftSpaces; spaceIteration++) /* Prints out spaces for the root. */
        printf(" ");

    printf("%c\n", levelOrder[0]); /* Prints out root. */

    initialCharToBePassed = levelOrder[0]; /* Converts root into an array for checkLayers(). */

    checkLayers(inOrder, levelOrder, levelNumber - 1, &levelOrderNodeIndex, &potentialSubTreeIndex, 0, &initialCharToBePassed);

    printf("\n\n");
}
