/* mkinput.c */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "mkinput.h"

/*
int main(int argc,char *argv[]){
    int *array;
    int size,mode;

    if(argc<3){
        printf("mkinput <size> <mode>\nmode: 0:asc 1:desc 2:shuffle\n");
        return -1;
    }

    size = atoi(argv[1]);
    mode = atoi(argv[2]);
    array = (int *)malloc(size * sizeof(int));

    mkinput(array,size,mode);

    for(int i=0;i<size;i++){
        printf("%d\n",array[i]);
    }
    return 0;
}
*/

void mkinput(int array[],int size,int mode){
    int i,j,tmp;
    LARGE_INTEGER seed;

    if(mode == 1){ // 降順
        for(i=0;i<size;i++) array[i] = size-i-1;
    }else if(mode == 2){ // randのせいで質の悪いシャッフル
        QueryPerformanceCounter(&seed);
        srand((unsigned int)seed.LowPart);
        for(i=0;i<size;i++) array[i] = i;
        for(i=0;i<size;i++){
            j = rand()%size;
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }else{ // 1か2以外の時は昇順にしておく
        for(i=0;i<size;i++) array[i] = i;
    }
}

int check(int array[],int size){
    for(int i=0;i<size;i++){
        if(array[i] != i) return 0;
    }
    return 1;
}
