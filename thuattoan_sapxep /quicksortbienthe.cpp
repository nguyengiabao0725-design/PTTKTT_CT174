#include <stdio.h>

typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;

void Swap(recordtype *x, recordtype *y){
	recordtype temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int FindPivot(recordtype a[], int i, int j){
    int min = i;
    int k;
    for(k = i + 1; k <= j; k++){
        if(a[k].key < a[min].key)
            min = k;
    }
    return min;
}
// phan hoach mang
int Partition(recordtype a[], int i, int j, keytype pivot){
    int L, R;

    // dua pivot v? d?u
    int pivotindex = FindPivot(a, i, j);
    Swap(&a[pivotindex], &a[i]);

    pivot = a[i].key;

    L = i + 1;
    R = j;

    while(L <= R){
        while(L <= j && a[L].key <= pivot) L++;
        while(a[R].key > pivot) R--;

        if(L < R)
            Swap(&a[L], &a[R]);
    }

    // dua pivot v? dúng v? trí
    Swap(&a[i], &a[R]);

    return R;
}

void QuickSort_bienthe(recordtype a[], int i, int j){
    keytype pivot;
    int pivotindex, k;

    if(i < j){
        pivotindex = FindPivot(a, i, j);
        pivot = a[pivotindex].key;

        k = Partition(a, i, j, pivot);

        QuickSort_bienthe(a, i, k - 1);
        QuickSort_bienthe(a, k + 1, j);
    }
}

void Read_Data(recordtype a[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if(f != NULL)
	while(!feof(f)){
		fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
		i++;
	} else printf("Loi mo file\n");
	fclose(f);
	*n=i;
}

void Print_Data(recordtype a[], int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].otherfields);
}

int main(){
	recordtype a[100];
	int n;
	Read_Data(a, &n);
	printf("Du lieu ban dau:\n");
	Print_Data(a,n);
	
	QuickSort_bienthe(a, 0, n-1);
	printf("Ket qua sau khi chay quicksort bien the:\n");
	Print_Data(a,n);
	return 0;
}
