#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

int *popAux;
int *populacao;
float *notas;
int num_cid, tamanhoPopulacao;

void quick(float *nota, int* populacao, int ini, int end)
{
    int i = ini, f = end, u;
    float pivo, aux;
    int iaux[num_cid];
    pivo = nota[(ini+end)/2];
    do
    {
        while (nota[i]>pivo) i++;
        while (nota[f]<pivo) f--;
        if (i<=f)
        {
            aux = nota[f];
            for(u = 0; u < num_cid; u++)
                *(iaux+u) = *(populacao + f*num_cid + u);
            nota[f] = nota[i];
            for(u = 0; u < num_cid; u++)
                *(populacao + f*num_cid + u) = *(populacao + i*num_cid + u);
            nota[i] = aux;
            for(u = 0; u < num_cid; u++)
                *(populacao + i*num_cid + u) = *(iaux+u);
            i++; f--;
        }
    }while(f > i);
    if (f>ini) quick(nota, populacao, ini, f);
    if (i<end) quick(nota, populacao, i, end);
}


int main(){
num_cid = 10;
tamanhoPopulacao = 3;
populacao = (int*)calloc(tamanhoPopulacao*num_cid, sizeof(int));
popAux = (int*)calloc(tamanhoPopulacao*num_cid, sizeof(int));
notas = (float*)calloc(tamanhoPopulacao, sizeof(float));
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

populacao[2*num_cid + 0] = 9;
populacao[2*num_cid + 1] = 8;
populacao[2*num_cid + 2] = 7;
populacao[2*num_cid + 3] = 6;
populacao[2*num_cid + 4] = 5;
populacao[2*num_cid + 5] = 4;
populacao[2*num_cid + 6] = 3;
populacao[2*num_cid + 7] = 2;
populacao[2*num_cid + 8] = 1;
populacao[2*num_cid + 9] = 0;

notas[0] = 10.0f;
notas[1] = 8.0f;
notas[2] = 9.0f;

quick(notas, populacao, 0, tamanhoPopulacao-1);

printf("ind1 = ");
for(int i=0; i<num_cid; i++){
	printf("%i ", populacao[i]);
}printf(" -> nota = %f\n", notas[0]);
printf("ind2 = ");
for(int i=0; i<num_cid; i++){
	printf("%i ", populacao[num_cid + i]);
}printf(" -> nota = %f\n", notas[1]);
printf("ind3 = ");
for(int i=0; i<num_cid; i++){
	printf("%i ", populacao[2*num_cid + i]);
}printf(" -> nota = %f\n", notas[2]);
return 0;
}
