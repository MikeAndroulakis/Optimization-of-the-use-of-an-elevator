#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void){
	int i;
	int nrid;
	int nst;
	int cost;
	scanf("%d %d",&nrid,&nst);
	int *dests;
	dests=(int*)malloc(nrid*sizeof(int));
	for(i=0;i<nrid;i++){
		scanf("%d",&dests[i]);
	}
	cost=solve(nrid,nst,dests);
	printf("Cost is: %d",cost);
	free(dests);
}
