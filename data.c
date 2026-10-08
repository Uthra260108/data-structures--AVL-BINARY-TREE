#include <stdio.h>

#include <stdlib.h>

#include <time.h>
 
#define N 4000

#define SEARCHES 50000

#define RANGE 10000
 
/* ============================================================

   LINKED LIST

   ============================================================ */
 
typedef struct ListNode {

    int data;

    struct ListNode *next;

} ListNode;
 
ListNode* insertList(ListNode *head, int value) {

    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
 
    if (newNode == NULL) {

        printf("Memory allocation failed!\n");

        exit(1);

    }
 
    newNode->data = value;

    newNode->next = head;
 
    return newNode;

}
 
int searchList(ListNode *head, int key) {

    ListNode *temp = head;
 
    while (temp != NULL) {

        if (temp->data == key)

            return 1;
 
        temp = temp->next;

    }
 
    return 0;

}
 
void freeList(ListNode *head) {

    ListNode *temp;
 
    while (head != NULL) {

        temp = head;

        head = head->next;

        free(temp);

    }

}
 
/* ============================================================

   BINARY SEARCH TREE

   ============================================================ */
 
typedef struct BSTNode {

    int data;

    struct BSTNode *left;

    struct BSTNode *right;

} BSTNode;
 
BSTNode* createBSTNode(int value) {

    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
 
    if (node == NULL) {

        printf("Memory allocation failed!\n");

        exit(1);

    }
 
    node->data = value;

    node->left = NULL;

    node->right = NULL;
 
    return node;

}
 
BSTNode* insertBST(BSTNode *root, int value) {

    if (root == NULL)

        return createBSTNode(value);
 
    if (value < root->data)

        root->left = insertBST(root->left, value);

    else if (value > root->data)

        root->right = insertBST(root->right, value);
 
    /* Duplicate values are ignored */
 
    return root;

}
 
int searchBST(BSTNode *root, int key) {

    while (root != NULL) {

        if (key == root->data)

            return 1;

        else if (key < root->data)

            root = root->left;

        else

            root = root->right;

    }
 
    return 0;

}
 
void freeBST(BSTNode *root) {

    if (root == NULL)

        return;
 
    freeBST(root->left);

    freeBST(root->right);
 
    free(root);

}
 
/* ============================================================

   AVL TREE

   ============================================================ */
 
typedef struct AVLNode {

    int data;

    int height;

    struct AVLNode *left;

    struct AVLNode *right;

} AVLNode;
 
int height(AVLNode *node) {

    if (node == NULL)

        return 0;
 
    return node->height;

}
 
int max(int a, int b) {

    return (a > b) ? a : b;

}
 
AVLNode* createAVLNode(int value) {

    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
 
    if (node == NULL) {

        printf("Memory allocation failed!\n");

        exit(1);

    }
 
    node->data = value;

    node->height = 1;

    node->left = NULL;

    node->right = NULL;
 
    return node;

}
 
AVLNode* rightRotate(AVLNode *y) {

    AVLNode *x = y->left;

    AVLNode *T2 = x->right;
 
    x->right = y;

    y->left = T2;
 
    y->height = 1 + max(height(y->left), height(y->right));

    x->height = 1 + max(height(x->left), height(x->right));
 
    return x;

}
 
AVLNode* leftRotate(AVLNode *x) {

    AVLNode *y = x->right;

    AVLNode *T2 = y->left;
 
    y->left = x;

    x->right = T2;
 
    x->height = 1 + max(height(x->left), height(x->right));

    y->height = 1 + max(height(y->left), height(y->right));
 
    return y;

}
 
int getBalance(AVLNode *node) {

    if (node == NULL)

        return 0;
 
    return height(node->left) - height(node->right);

}
 
AVLNode* insertAVL(AVLNode *node, int value) {

    int balance;
 
    if (node == NULL)

        return createAVLNode(value);
 
    if (value < node->data)

        node->left = insertAVL(node->left, value);

    else if (value > node->data)

        node->right = insertAVL(node->right, value);

    else

        return node;  /* Ignore duplicates */
 
    node->height = 1 + max(height(node->left),

                           height(node->right));
 
    balance = getBalance(node);
 
    /* Left Left Case */

    if (balance > 1 && value < node->left->data)

        return rightRotate(node);
 
    /* Right Right Case */

    if (balance < -1 && value > node->right->data)

        return leftRotate(node);
 
    /* Left Right Case */

    if (balance > 1 && value > node->left->data) {

        node->left = leftRotate(node->left);

        return rightRotate(node);

    }
 
    /* Right Left Case */

    if (balance < -1 && value < node->right->data) {

        node->right = rightRotate(node->right);

        return leftRotate(node);

    }
 
    return node;

}
 
int searchAVL(AVLNode *root, int key) {

    while (root != NULL) {

        if (key == root->data)

            return 1;

        else if (key < root->data)

            root = root->left;

        else

            root = root->right;

    }
 
    return 0;

}
 
void freeAVL(AVLNode *root) {

    if (root == NULL)

        return;
 
    freeAVL(root->left);

    freeAVL(root->right);
 
    free(root);

}
 
/* ============================================================

   ARRAY SEARCH FUNCTIONS

   ============================================================ */
 
/* Linear search for unsorted array */

int linearSearch(int arr[], int n, int key) {

    int i;
 
    for (i = 0; i < n; i++) {

        if (arr[i] == key)

            return 1;

    }
 
    return 0;

}
 
/* Binary search for sorted array */

int binarySearch(int arr[], int n, int key) {

    int low = 0;

    int high = n - 1;

    int mid;
 
    while (low <= high) {

        mid = low + (high - low) / 2;
 
        if (arr[mid] == key)

            return 1;

        else if (key < arr[mid])

            high = mid - 1;

        else

            low = mid + 1;

    }
 
    return 0;

}
 
/* ============================================================

   MAIN

   ============================================================ */
 
int main() {
 
    int arr[N];

    int sortedArr[N];

    int searchValues[SEARCHES];
 
    ListNode *head = NULL;
 
    BSTNode *bstRoot = NULL;

    AVLNode *avlRoot = NULL;
 
    int i;
 
    int unsuccessfulUnsorted = 0;

    int unsuccessfulSorted = 0;

    int unsuccessfulList = 0;

    int unsuccessfulBST = 0;

    int unsuccessfulAVL = 0;
 
    double averageUnsorted;

    double averageSorted;

    double averageList;

    double averageBST;

    double averageAVL;
 
    /* Seed random number generator */

    srand((unsigned int)time(NULL));
 
    /* --------------------------------------------------------

       Generate 4000 random integers

       -------------------------------------------------------- */
 
    for (i = 0; i < N; i++) {

        arr[i] = rand() % RANGE;

        sortedArr[i] = arr[i];

    }
 
    /* --------------------------------------------------------

       Sort the sorted array

       -------------------------------------------------------- */
 
    /* Simple qsort from C standard library */

    int compare(const void *a, const void *b) {

        return (*(int*)a - *(int*)b);

    }
 
    qsort(sortedArr, N, sizeof(int), compare);
 
    /* --------------------------------------------------------

       Build Linked List, BST and AVL Tree

       -------------------------------------------------------- */
 
    for (i = 0; i < N; i++) {
 
        /* Linked List */

        head = insertList(head, arr[i]);
 
        /* Binary Search Tree */

        bstRoot = insertBST(bstRoot, arr[i]);
 
        /* AVL Tree */

        avlRoot = insertAVL(avlRoot, arr[i]);

    }
 
    /* --------------------------------------------------------

       Generate 50,000 search values
 
       Values are also in range 0-9999.

       Therefore some searches will be successful and

       some will be unsuccessful.

       -------------------------------------------------------- */
 
    for (i = 0; i < SEARCHES; i++) {

        searchValues[i] = rand() % RANGE;

    }
 
    /* --------------------------------------------------------

       Perform searches

       -------------------------------------------------------- */
 
    for (i = 0; i < SEARCHES; i++) {
 
        int key = searchValues[i];
 
        /* Unsorted Array - Linear Search */

        if (!linearSearch(arr, N, key))

            unsuccessfulUnsorted++;
 
        /* Sorted Array - Binary Search */

        if (!binarySearch(sortedArr, N, key))

            unsuccessfulSorted++;
 
        /* Linked List - Linear Search */

        if (!searchList(head, key))

            unsuccessfulList++;
 
        /* Binary Search Tree */

        if (!searchBST(bstRoot, key))

            unsuccessfulBST++;
 
        /* AVL Tree */

        if (!searchAVL(avlRoot, key))

            unsuccessfulAVL++;

    }
 
    /* --------------------------------------------------------

       Calculate average unsuccessful searches
 
       Since 50,000 searches are performed, the average is:
 
       unsuccessful searches / total searches
 
       Multiplying by 100 gives percentage of unsuccessful

       searches.

       -------------------------------------------------------- */
 
    averageUnsorted =

        ((double)unsuccessfulUnsorted / SEARCHES) * 100.0;
 
    averageSorted =

        ((double)unsuccessfulSorted / SEARCHES) * 100.0;
 
    averageList =

        ((double)unsuccessfulList / SEARCHES) * 100.0;
 
    averageBST =

        ((double)unsuccessfulBST / SEARCHES) * 100.0;
 
    averageAVL =

        ((double)unsuccessfulAVL / SEARCHES) * 100.0;
 
    /* --------------------------------------------------------

       Print results

       -------------------------------------------------------- */
 
    printf("\n===============================================\n");

    printf(" SEARCH PERFORMANCE RESULTS\n");

    printf("===============================================\n");
 
    printf("Number of data elements : %d\n", N);

    printf("Number of searches      : %d\n", SEARCHES);

    printf("Value range             : 0 - %d\n", RANGE - 1);
 
    printf("\n-----------------------------------------------\n");

    printf("%-25s %-15s %-15s\n",

           "Data Structure",

           "Unsuccessful",

           "Percentage");
 
    printf("-----------------------------------------------\n");
 
    printf("%-25s %-15d %.2f%%\n",

           "Unsorted Array",

           unsuccessfulUnsorted,

           averageUnsorted);
 
    printf("%-25s %-15d %.2f%%\n",

           "Sorted Array",

           unsuccessfulSorted,

           averageSorted);
 
    printf("%-25s %-15d %.2f%%\n",

           "Linked List",

           unsuccessfulList,

           averageList);
 
    printf("%-25s %-15d %.2f%%\n",

           "Binary Search Tree",

           unsuccessfulBST,

           averageBST);
 
    printf("%-25s %-15d %.2f%%\n",

           "AVL Tree",

           unsuccessfulAVL,

           averageAVL);
 
    printf("-----------------------------------------------\n");
 
    /* --------------------------------------------------------

       Free allocated memory

       -------------------------------------------------------- */
 
    freeList(head);

    freeBST(bstRoot);

    freeAVL(avlRoot);
 
    return 0;

}

 
