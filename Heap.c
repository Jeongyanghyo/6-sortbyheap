#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"

//힙 초기화 함수
void Init_Heap(TreeNode* root) {
    root->size = 0;
}

//메모리 해제 함수
void destroy_heap(TreeNode* h) {
    free(h);
}

//힙이 비어있는지 확인하는 함수
int is_empty_heap(TreeNode* h) {
    return (h->size == 0);

}

//힙이 가득차 있는지 확인하는 함수
int is_full_heap(TreeNode* h) {
    return (h->size == (MAX_SIZE - 1));

}

//힙의 노드 출력 함수
void Print_Heap(TreeNode* root) {
    for (int i = 0; i < root->size; i++) {
        printf("%d ", root->data[i]);
    }
    printf("\n");
}


// 최대 값 노드 추가 함수
int InsertMaxHeap(TreeNode* root, int value, int Step) {
    if (root->size >= MAX_SIZE) {
        printf("힙 가득 참\n");
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

// 최대 값 노드 삭제 함수
int DeleteMaxHeap(TreeNode* root) {
    if (root->size == 0) {

        printf("힙 비어있음\n");
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

//힙 트리의 레벨별 출력하는 함수
void display_heap(TreeNode* root) {
    if (root->size == 0) {
        printf("힙 비어있음.\n");
        return;
    }

    int level = 0;
    int count = 1;
    int index = 0;

    printf("트리 레벨별 출력 \n");
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


//힙 트리를 생성하는 함수
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
            // 자식이 부모보다 크면 교환
            if (inputData[child] > inputData[parent]) {
                swap(&inputData[child], &inputData[parent]);
            }
            child = parent;
        }

        // 현재 상태 출력
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
    // 최대 힙을 생성
    BuildMaxHeap(arr, n);

    // 하나씩 요소를 힙에서 빼면서 정렬
    for (int i = n - 1; i > 0; i--) {
        // 현재 루트(최대 값)를 배열의 끝으로 이동
		swap(&arr[0], &arr[i]);

        resortHeap(arr, i, 0);

        for (int j = 0; j < i; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}
