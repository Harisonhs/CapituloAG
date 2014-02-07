#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;

int num_cid; // Número de cidades
int *melhorInd;
bool falha=false;

typedef struct scity {
    float longitude;
    float latitude;
} city;

city* cities;

void setCities(const char* filename){//
    int ch=0, cit=0, i1=0;
    FILE *f;
    char str[256];
    cities = (city*)malloc(num_cid*sizeof(city));
    assert (cities);
    f = fopen(filename, "r");
    if (f == NULL) {printf("nao pode abrir o arquivo %s\n", filename); exit(-1);}

    do{ fscanf(f, "%s", str); }while(strcmp(str, "DIMENSION:") != 0);
    fscanf(f, "%d\n", &cit);

    ch = getc(f);  while ((ch != EOF) && (ch != '\n')) ch = getc(f);
    fscanf(f, "%s\n", str);
    if (strcmp(str, "NODE_COORD_SECTION") != 0) {
        printf("arquivo em formato incorreto\n");
        exit(-1);
    }

    while (i1 < num_cid){
        fscanf(f, "%s", str);
        i1 = atoi(str);
        fscanf(f, "%s", str);
        cities[i1-1].longitude = atof(str);
        fscanf(f, "%s", str);
        cities[i1-1].latitude = atof(str);
    }

    fscanf(f, "%s", str);
    if (strcmp(str, "EOF") != 0 && strcmp(str, "-1") != 0) {
        printf("'EOF' nao encontrado\n");
        falha=true;
    }
    fclose(f);
}

void setMelhorInd(int *melhorInd, const char* filename){
    int i1=0;
    FILE *f;
    char str[256];
    f = fopen(filename, "r");
    if (f == NULL) {printf("nao pode abrir o arquivo %s\n", filename); falha=true;}

    do{ fscanf(f, "%s", str); }while(strcmp(str, "TOUR_SECTION") != 0);

    while (i1 < num_cid){
        fscanf(f, "%s", str);
        melhorInd[i1] = atoi(str);
        i1++;
    }

    fclose(f);
}

void plotaIndividuo(int* melhorInd){
    if(!falha){
        int i;
        FILE *pop;
        pop = fopen ("Pop", "w");

        for(i=0; i < num_cid; i++){
            fprintf(pop, "%f %f\n", cities[melhorInd[i] - 1].longitude, cities[melhorInd[i] - 1].latitude);
        } fprintf(pop, "%f %f\n", cities[melhorInd[0] - 1].longitude, cities[melhorInd[0] - 1].latitude);
        fclose(pop);
    }
}

int main(int argc, char *argv[])
{
    num_cid = atoi(argv[1]);
    setCities(argv[2]);
    melhorInd = (int*)malloc(num_cid*sizeof(int));
    setMelhorInd(melhorInd, argv[3]);
    plotaIndividuo(melhorInd);
    free(melhorInd);
    return 0;
}
