#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

int *popAux;
int *populacao;
int num_cid, tamanhoPopulacao;
float probCruz = 0.6f;

void desliza(int *indAux, int pc1, int pc2){
	int i=0, j=0, k=0, first=0, encontrado=0;
//	int *indAux;
//	indAux = (int*)malloc(num_cid*sizeof(int));	
	cout << "inicio" << endl;
	for(i=pc2; i!=pc2-1; i++){
		i %= num_cid;
		cout << "i = " << i << endl;		
		if(indAux[i]==-1){
			first = indAux[0];
			if(i>=pc2){
				j=0;
			}else{
				j=i; 
			}
			while(j<pc2-1){
				indAux[j] = indAux[j+1];
				j++;
			}
			indAux[pc2 - 1] = -1;
	//		if(!encontrado){
				for(j=pc2; j<num_cid; j++){
					if(indAux[j]==-1){
						for(k=j; k<num_cid; k++)
							indAux[k] = indAux[k+1];
						j = num_cid; //deve sair do loop do j
						encontrado = 1;
					}
				}
	//		}
			if(first!=-1 && i>=pc2){
				indAux[num_cid - 1] = first;
			}
		}
		
		for(j=0; j<num_cid; j++){
			cout << indAux[j] << " ";
		}cout << endl;
	}
	cout << "fim" << endl;
// 	free(indAux);
}

void cruzamentoOX(){
    int i=0, j=0, ind1=0, ind2=0, posInd1=0, posInd2=0, pc1=0, pc2=0, pcAux=0;
	int *indAux1, *indAux2;
	indAux1 = (int*)malloc(num_cid*sizeof(int));
	indAux2 = (int*)malloc(num_cid*sizeof(int));
	ind1 = 0;
	ind2 = 1;
	pc1 = 4; //rand() % num_cid;
    pcAux = 7; //rand() % num_cid;
    if(pc1 < pcAux)
       pc2 = pcAux;
    else{
       pc2 = pc1;
       pc1 = pcAux;
    }
	posInd1 = ind1*num_cid;
	posInd2 = ind2*num_cid;
	for(i=0; i<num_cid; i++){
		indAux1[i] = popAux[posInd1 + i];
		indAux2[i] = popAux[posInd2 + i];
	}
//////////////////////////////
	//marcar (-1) em indAux1 e 2.
	for(i=0; i<num_cid; i++){
		for(j=pc1; j<pc2; j++){
			if(indAux1[i]==popAux[posInd2 + j]){
				indAux1[i] = -1;
			}
			if(indAux2[i]==popAux[posInd1 + j]){
				indAux2[i] = -1;
			}
		}
	}
//////////////////////////////
	desliza(indAux1, pc1, pc2);
	desliza(indAux2, pc1, pc2);

	for(i=0; i<num_cid; i++){
		popAux[posInd1 + i] = indAux1[i];
		popAux[posInd2 + i] = indAux2[i];
	}
}

int main(){
num_cid = 10;
tamanhoPopulacao = 2;
populacao = (int*)calloc(tamanhoPopulacao*num_cid, sizeof(int));
popAux = (int*)calloc(tamanhoPopulacao*num_cid, sizeof(int));
populacao[0*num_cid + 0] = 1;
populacao[0*num_cid + 1] = 2;
populacao[0*num_cid + 2] = 3;
populacao[0*num_cid + 3] = 4;
populacao[0*num_cid + 4] = 5;
populacao[0*num_cid + 5] = 6;
populacao[0*num_cid + 6] = 7;
populacao[0*num_cid + 7] = 8;
populacao[0*num_cid + 8] = 9;
populacao[0*num_cid + 9] = 0;

populacao[1*num_cid + 0] = 8;
populacao[1*num_cid + 1] = 1;
populacao[1*num_cid + 2] = 6;
populacao[1*num_cid + 3] = 5;
populacao[1*num_cid + 4] = 0;
populacao[1*num_cid + 5] = 3;
populacao[1*num_cid + 6] = 9;
populacao[1*num_cid + 7] = 2;
populacao[1*num_cid + 8] = 7;
populacao[1*num_cid + 9] = 4;


for(int i=0; i<tamanhoPopulacao; i++){
        for(int j = 0; j < num_cid; j++){
            *(popAux + (i*num_cid) + j) = *(populacao + (i*num_cid) + j);
        }
    }

cruzamentoOX();

printf("ind1 = ");
for(int i=0; i<num_cid; i++){
	printf("%i ", popAux[i]);
}printf("\n");
printf("ind2 = ");
for(int i=0; i<num_cid; i++){
	printf("%i ", popAux[num_cid + i]);
}printf("\n");
return 0;
}
