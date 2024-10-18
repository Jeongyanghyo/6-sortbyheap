#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

main() {
	int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86  };
	int size = sizeof(inputData) / sizeof(int);

	printf("<Sort>\n");
	BuildMaxHeapAndSort(inputData, size);

	printf("\nSorted Arrray:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", inputData[i]);
	}

	printf("\n");
	return 0;
}