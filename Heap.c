#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"

//�� �ʱ�ȭ �Լ�
void Init_Heap(TreeNode* root) {
    root->size = 0;
}

//�޸� ���� �Լ�
void destroy_heap(TreeNode* h) {
    free(h);
}

//���� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty_heap(TreeNode* h) {
    return (h->size == 0);

}

//���� ������ �ִ��� Ȯ���ϴ� �Լ�
int is_full_heap(TreeNode* h) {
    return (h->size == (MAX_SIZE - 1));

}

//���� ��� ��� �Լ�
void Print_Heap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]);
    }
    printf("\n");
}


// �ִ� �� ��� �߰� �Լ�
int InsertMaxHeap(TreeNode* root, int value, int Step) {
    if (root->size >= MAX_SIZE) {
        printf("�� ���� ��\n");
        return 0;
    }

    int index = root->size;
    root->data[index] = value;
    root->size++;

    int move = 0;
    if (Step) {
        Print_Heap(root);
    }

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (root->data[parent] < root->data[index]) {
            int temp = root->data[parent];
            root->data[parent] = root->data[index];
            root->data[index] = temp;
            index = parent;
            move++;

            if (Step) {

                Print_Heap(root);
            }
        }
        else {
            break;
        }
    }


    return move;
}

// �ִ� �� ��� ���� �Լ�
int DeleteMaxHeap(TreeNode* root) {
    if (root->size == 0) {

        printf("�� �������\n");
        return 0;
    }

    root->data[0] = root->data[root->size - 1];
    root->size--;

    int index = 0;
    int moves = 0;
    Print_Heap(root);

    while (index * 2 + 1 < root->size) {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int largerChild = leftChild;

        if (rightChild < root->size && root->data[rightChild] > root->data[leftChild]) {
            largerChild = rightChild;
        }

        if (root->data[index] < root->data[largerChild]) {
            int temp = root->data[index];
            root->data[index] = root->data[largerChild];
            root->data[largerChild] = temp;

            index = largerChild;
            moves++;

            Print_Heap(root);
        }
        else {
            break;
        }
    }


    return moves;
}

//�� Ʈ���� ������ ����ϴ� �Լ�
void display_heap(TreeNode* root) {
    if (root->size == 0) {
        printf("�� �������.\n");
        return;
    }

    int level = 0;
    int count = 1;
    int index = 0;

    printf("Ʈ�� ������ ��� \n");
    while (index < root->size) {
        printf("[%d] ", level + 1);

        for (int i = 0; i < count && index < root->size; i++) {
            printf("%d ", root->data[index]);
            index++;
        }
        printf("\n");

        level++;
        count *= 2;
    }
}


//�� Ʈ���� �����ϴ� �Լ�
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    Init_Heap(root);

    for (int i = 0; i < size; i++) {
        InsertMaxHeap(root, inputData[i], 0);
    }

    return root;
}

void BuildMaxHeap(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        int child = i - 1;
        while (child > 0) {
            int parent = (child - 1) / 2;
            // �ڽ��� �θ𺸴� ũ�� ��ȯ
            if (inputData[child] > inputData[parent]) {
                swap(&inputData[child], &inputData[parent]);
            }
            child = parent;
        }

        // ���� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BuildMaxHeapAndSort(int arr[], int n) {
    // �ִ� ���� ����
    BuildMaxHeap(arr, n);

    // �ϳ��� ��Ҹ� ������ ���鼭 ����
    for (int i = n - 1; i > 0; i--) {
        // ���� ��Ʈ(�ִ� ��)�� �迭�� ������ �̵�
		swap(&arr[0], &arr[i]);

        resortHeap(arr, i, 0);

        for (int j = 0; j < i; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}
