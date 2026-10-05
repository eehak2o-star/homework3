#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, int data, int *count)
{
    if (root == NULL) {
        root = malloc(sizeof(Node));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    (*count)++;

    if (data < root->data)
        root->left = insert(root->left, data, count);
    else
        root->right = insert(root->right, data, count);

    return root;
}

int search_array(int array[], int key, int *count)
{
    int i;

    *count = 0;

    for (i = 0; i < 100; i++) {
        (*count)++;

        if (array[i] == key)
            return 1;
    }

    return 0;
}

int search_bst(Node *root, int key, int *count)
{
    *count = 0;

    while (root != NULL) {
        (*count)++;

        if (key == root->data)
            return 1;

        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return 0;
}

void free_tree(Node *root)
{
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    int array[100];
    int used[1001] = {0};
    int search[50];

    Node *root = NULL;

    int create_count = 0;
    int array_count = 0;
    int bst_count = 0;

    int i, n;

    srand(time(NULL));

    printf("Generated Data\n");

    for (i = 0; i < 100; ) {
        n = rand() % 1001;

        if (used[n] == 0) {
            used[n] = 1;
            array[i] = n;

            printf("%d ", n);

            root = insert(root, n, &create_count);

            i++;
        }
    }

    printf("\n\nBST Creation Comparisons : %d\n", create_count);

    printf("\nSearch Results\n");

    for (i = 0; i < 50; i++) {
        int a, b;
        int result1, result2;

        search[i] = rand() % 1001;

        result1 = search_array(array, search[i], &a);
        result2 = search_bst(root, search[i], &b);

        array_count += a;
        bst_count += b;

        printf("Search Key : %d\n", search[i]);
        printf("Sequential Search : %s  Comparisons : %d\n",
               result1 ? "Found" : "Not Found", a);
        printf("BST Search        : %s  Comparisons : %d\n\n",
               result2 ? "Found" : "Not Found", b);
    }

    printf("Number of searches : 50\n\n");

    printf("Sequential Search Total comparisons : %d\n", array_count);
    printf("Sequential Search Average           : %.2f\n",
           array_count / 50.0);

    printf("\nBST Search Total comparisons        : %d\n", bst_count);
    printf("BST Search Average                  : %.2f\n",
           bst_count / 50.0);

    printf("\nBST Creation + Search comparisons   : %d\n",
           create_count + bst_count);

    free_tree(root);

    return 0;
}
