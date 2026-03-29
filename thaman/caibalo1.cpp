#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct{
	char TenDV[20];
	float TL, GT, DG;
	int PA;
}DV;

DV *ReadFromFile(float *W, int *n){
	FILE *f;
	f=fopen("CaiBalo1.txt", "r");
	fscanf(f, "%f", W);
		DV *dsdv;
		dsdv=(DV*)malloc(sizeof(DV));
		int i=0;
		while(!feof(f)){
			fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
			dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
			dsdv[i].PA = 0;
			i++;
			dsdv=(DV*)realloc(dsdv, sizeof(DV)*(i+1));
		}
		*n=i;
		fclose(f);
		return dsdv;
}

void Swap(DV *x, DV *y){
	DV temp;
	temp = *x;
	*x = *y;
	*y = temp;
}


void BubbleSort(DV *dsdv, int n){
	int i, j;
	for(i = 0; i <= n-2; i++)
		for(j = n-1; j>= i+1; j--){
			if(dsdv[j].DG > dsdv[j-1].DG)
				Swap(&dsdv[j], &dsdv[j-1]);
		}
}

void InDSDV(DV *dsdv, int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan THAM AN nhu sau:\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n", W);
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat   | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	for(i = 0; i<n; i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d     |\n",
		i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
		TongTL = TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT+dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for(i=0; i<n; i++){
		printf("%d,", dsdv[i].PA);
	}
	printf("%d)", dsdv[n-1].PA);
	printf("\nTong trong luong = %9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

void Greedy(DV *dsdv, int n, int W){
	int i;
	for(i = 0; i<n; i++){
		dsdv[i].PA = (W/dsdv[i].TL);
		W = W-dsdv[i].PA * dsdv[i].TL;
	}
}

main(){
	int n;
	float W;
	DV *dsdv;
	
	dsdv=ReadFromFile(&W, &n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,n ,W);
	InDSDV(dsdv, n, W);
	
	free(dsdv);
	return 0;
}
