#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

int *popAux;
int *populacao;
int num_cid, tamanhoPopulacao;
float probCruz = 0.6f;

void cruzamentoPMX(){
    int i=0, j=0, ind1=0, ind2=0, pcAux=0, pc1=0, pc2=0, i1=0;
    for(i1=0; i1 < tamanhoPopulacao*probCruz; i1++){
            ind1 = 0; //rand()%tamanhoPopulacao;
            ind2 = 1; //rand()%tamanhoPopulacao;
        //printf("ind1 = %i e ind2 = %i\n", ind1, ind2);

        pc1 = 4; //rand() % num_cid;
        pcAux = 7; //rand() % num_cid;
        if(pc1 < pcAux)
            pc2 = pcAux;
        else{
            pc2 = pc1;
            pc1 = pcAux;
        }
        printf("pc1 = %i e pc2 = %i\n", pc1, pc2);
        for(i=0; i<num_cid; i++){
            if(i==pc1)
                i = pc2;
            *(popAux + (ind1*num_cid) + i) = *(populacao + (ind1*num_cid) + i);
            *(popAux + (ind2*num_cid) + i) = *(populacao + (ind2*num_cid) + i);
        }
        for(i=pc1; i<pc2; i++){
            *(popAux + (ind1*num_cid) + i) = *(populacao + (ind2*num_cid) + i);
            *(popAux + (ind2*num_cid) + i) = *(populacao + (ind1*num_cid) + i);
        }
        for(i=0; i<num_cid; i++){
            if(i==pc1)
                i = pc2;
            for(j=pc1; j<pc2; j++){
                if(*(popAux + (ind1*num_cid) + i) == *(popAux + (ind1*num_cid) + j)){
                    *(popAux + (ind1*num_cid) + i) = *(popAux + ind2*num_cid + j);
                    i--;
                    j=pc2;
                }
            }
        }
        for(i=0; i<num_cid; i++){
            if(i==pc1)
                i = pc2;
            for(j=pc1; j<pc2; j++){
                if(i!=j && *(popAux + ind2*num_cid + i) == *(popAux + ind2*num_cid + j)){
                    *(popAux + ind2*num_cid + i) = *(popAux + (ind1*num_cid) + j);
                    i--;
                    j=pc2;
                }
            }
        }
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
    

cruzamentoPMX();

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
