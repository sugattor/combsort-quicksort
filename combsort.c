// combsort.c
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "mkinput.h"

void combsort(int array[],int size);

int main(int argc,char *argv[]){
    int *array;
    int size,mode,n;
    LARGE_INTEGER freq,begin,end;
    double time = 0.0;

    if(argc<4){
        printf("combsort <size> <mode> <N>\nmode: 0:asc 1:desc 2:shuffle\n");
        return -1;
    }

    size = atoi(argv[1]);
    mode = atoi(argv[2]);
    n = atoi(argv[3]);
    array = (int *)malloc(size * sizeof(int));
    QueryPerformanceFrequency(&freq); // 周波数取得

    for(int i=0;i<n;i++){// N回計測
        // 配列の作成
        mkinput(array,size,mode);

        // 計測開始
        QueryPerformanceCounter(&begin);
        combsort(array,size);
        QueryPerformanceCounter(&end);
        // for(int i=0;i<size;i++) printf("%d\n",array[i]);
        
        time += ((double)(end.QuadPart - begin.QuadPart)) / ((double)freq.QuadPart);
        if(!check(array,size)) printf("sort check error\n");
    }

    printf("%.8f",time/(double)n);
    return 0;
}

void combsort(int array[],int size){
    int gap = size;
    int swap = 1;
    int tmp;

    while(swap || gap > 1){
        if(gap > 1) gap = gap * 10 / 13; // 1/1.3
        if(gap == 9 || gap == 10) gap = 11; // Comb Sort 11
        swap = 0;

        for(int i=0;i < size-gap;i++){
            if(array[i] > array[i+gap]){
                tmp = array[i];
                array[i] = array[i+gap];
                array[i+gap] = tmp;
                swap = 1;
            }
        }
    }
}
