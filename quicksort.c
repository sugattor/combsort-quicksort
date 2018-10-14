// quicksort.c
#include <stdio.h>
#include <Windows.h>
#include "mkinput.h"

void quicksort(int array[],int left,int right);

int main(int argc,char *argv[]){
    int *array;
    int size,mode,n;
    LARGE_INTEGER freq,begin,end;
    double time = 0.0;

    if(argc<4){
        printf("quicksort <size> <mode> <N>\nmode: 0:asc 1:desc 2:shuffle\n");
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
        quicksort(array,0,size-1);
        QueryPerformanceCounter(&end);
        // for(int i=0;i<size;i++) printf("%d\n",array[i]);
        
        time += ((double)(end.QuadPart - begin.QuadPart)) / ((double)freq.QuadPart);
        if(!check(array,size)) printf("sort check error\n");
    }
    printf("%.8f",time/(double)n);
    return 0;
}

int median(int x, int y, int z){
    if(x < y){
        if(y < z){
            return y;
        }else if(z < x){
            return x;
        }else{
            return z;
        }
    }else{
        if(z < y){
            return y;
        }else if(x < z){
            return x;
        }else{
            return z;
        }
    }
}

void quicksort(int array[],int left,int right){
    int l,r,p,tmp;
    l = left;
    r = right;
    p = median(array[l],array[((l+r)/2)],array[r]);
    
    while(1){
        while(array[l] < p) l++;
        while(array[r] > p) r--;
        if(l >= r) break;
        
        tmp = array[l];
        array[l] = array[r];
        array[r] = tmp;

        l++;r--;
    }

    if(left < l-1) quicksort(array,left,l-1);
    if(r+1 < right) quicksort(array,r+1,right);
}
