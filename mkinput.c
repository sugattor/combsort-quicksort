// mkinput.c
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "mkinput.h"

void mkinput(int array[], int size, int mode) {
	int i, j, tmp;
	LARGE_INTEGER seed;

	if (mode == 1) { // 降順
		for (i = 0; i<size; i++) array[i] = size - i - 1;
	}
	else if (mode == 2) { // シャッフル
		QueryPerformanceCounter(&seed);
		srand((unsigned int)seed.LowPart);
		for (i = 0; i<size; i++) array[i] = i;
		for (i = 0; i<size; i++) {
			j = rand() % size;
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	else { // 1か2以外の時は昇順にしておく
		for (i = 0; i<size; i++) array[i] = i;
	}
}

int check(int array[], int size) {
	for (int i = 0; i<size; i++) {
		if (array[i] != i) return 0;
	}
	return 1;
}
