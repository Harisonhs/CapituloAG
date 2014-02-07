#include "ReadTSPLIB.h" //para setCities, setDistancias e setIndOtimo
#include "Graficos.h" //para plotagens
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h> //para função de tempo
#include <omp.h> //para OpenMP
#include <iostream> //para cout

using namespace std;

long gettime(timeval tempo1, timeval tempo2){
    long elapsed_mtime, elapsed_seconds, elapsed_useconds;
    elapsed_seconds  = tempo2.tv_sec  - tempo1.tv_sec;
    elapsed_useconds = tempo2.tv_usec - tempo1.tv_usec;
    elapsed_mtime = ((elapsed_seconds) * 1000 + elapsed_useconds/1000.0) + 0.5;
    return elapsed_mtime;
}

/*
Inicia população aleatória
*/
void iniciaPopulacao(int* pop, int popSize){
	int *aux, val=0;
	aux = (int*) malloc (cid*sizeof(int));
	for(int i=0; i<popSize; i++){
		for(int j=0; j<cid; j++)
			aux[j] = 0;
		for(int pos=0; pos < cid;){
			val = rand() % cid;
			if(aux[val]==0){
				pop[i*cid + val] = pos;
				aux[val] = 1;
				pos++;
			}
		}
	}
	free(aux);
}

/*
Retorna o menor dos indivíduos passados
*/
int menor(int ind1, int ind2, float* notas){
	if(notas[ind1] < notas[ind2]) return ind1;
	return ind2;
}

/*
Retorna o maior dos indivíduos passados
*/
int maior(int ind1, int ind2, float* notas){
	if(notas[ind1] > notas[ind2]) return ind1;
	return ind2;
}

/*
Retorna a posição do melhor indivíduo em notas
*/
int top1(int popSize, float* notas){
	int ind=0;
	for(int i=1; i<popSize; i++){
		ind = menor(ind, i, notas);
	}
	return ind;
}

/*
Retorna a posição do pior indivíduo em notas
*/
int ultimo(int popSize, float* notas){
	int ind=0;
	for(int i=1; i<popSize; i++){
		ind = maior(ind, i, notas);
	}
	return ind;
}

/*
Atribui a nota de cada indivíduo da população
*/
void avaliar(int* pop, float* notas, int popSize){
	float nota;	
	for(int i=0; i<popSize; i++){
		nota = 0.0f;
		for(int j=0; j<cid-1; j++)
			nota += distancias[pop[i*cid + j]*cid + pop[i*cid + j+1]];
		notas[i] = nota + distancias[pop[i*cid + cid-1]*cid + pop[i*cid]];
	}
}

void adaptaNotas(float* notas, float* novasNotas, int popSize){
    int i=0;
    float *f1, max=0.0f, min=0.0f, epson=0.0001f, taxa=0.0f, minf1=0.0f, maxf1=0.0f, media=0.0f, diff=0.0f;

    max = notas[ultimo(popSize, notas)];
    min = notas[top1(popSize, notas)];
    f1 = (float*)calloc(popSize, sizeof(float));
    for(i=0; i<popSize; i++){
        media += notas[i];
    }
    media /= popSize;
    for(i=0; i<popSize; i++){
        f1[i] = max - notas[i];
    }
    minf1 = f1[top1(popSize, f1)];
    maxf1 = f1[ultimo(popSize, f1)];
    diff = (maxf1==minf1)?epson:maxf1-minf1;
    for(i=0; i<popSize; i++){
        novasNotas[i] = (100.0f-taxa)*((f1[i]-minf1)/diff) + taxa;
    }
    free(f1);
//    cout << "max = " << max << ", media = " << media << ", min = " << notas[top1(popSize, notas)] << endl;
}

/*
Seleciona os indivíduos da população através do método da roleta ou torneio
*/
void seleciona(int* pop, int* popAux, float* notas, int popSize, int metSel){
	int ind=0, *sel;	
	float soma=0.0f, rnd=0.0f, total=0.0f, media=0.0f, *novasNotas;
	novasNotas = (float*)malloc(popSize*sizeof(float));
	sel = (int*)calloc(popSize, sizeof(int));
	if(metSel){ //roleta
		//adaptaNotas(notas, novasNotas, popSize);
		for(int i=0; i<popSize; i++){
			total+=notas[i];
		}
		
		for(int i=0; i<popSize; i++){
			rnd = ((float)rand()/RAND_MAX);
			ind = 0; soma=0.0f;
			do{
				soma += notas[ind]/total;
				ind++;
			}while(soma<rnd);
			if(ind==popSize) ind--;
			sel[ind]++;
			for(int j=0; j<cid; j++)
				popAux[i*cid + j] = pop[ind*cid + j];
		}
	}
	/*cout << "seleciona: " << endl;
	for(int i=0; i<popSize; i++)
		cout << "i = " << i << ", nota = " << notas[i] << ", novasNotas = " << novasNotas[i] << ", sel = " << sel[i] << endl;
	cout << endl;*/
	
	free(novasNotas);
	free(sel);
}

void crossoverPMX(int* popAux, float* notas, float pc, int popSize, int metSel){
	int cross=0, ind1=0, ind2=0, aux=0, pc1=0, pc2=0;
	bool sub=false;
	cross = ceil(pc * popSize);
	//cout << "cruzamento: " << endl;
	for(int i=0; i<cross; i++){
		ind1 = rand() % popSize;
		ind2 = rand() % popSize;
		pc1 = rand() % cid;
		pc2 = rand() % cid;
		/*cout << "ind1 = " << ind1 << ", ind2 = " << ind2 << ", pc1 = " << pc1 << ", pc2 = " << pc2 << endl;
		cout << "ind1 = ";
		for(int h=0; h<cid; h++){
			cout << popAux[ind1*cid + h] << " ";
		}cout << endl;
		
		cout << "ind2 = ";
		for(int h=0; h<cid; h++){
			cout << popAux[ind2*cid + h] << " ";
		}cout << endl;
		*/

		for(int j=pc1; j!=pc2; j++){	
			j %= cid;
			if(j==0 && pc2==0) break;
			aux = popAux[ind1*cid + j];
			popAux[ind1*cid + j] = popAux[ind2*cid + j];
			popAux[ind2*cid + j] = aux;
		}

		for(int j=pc2; j!=pc1; j++){	
			j %= cid;
			if(j==0 && pc1==0) break;
			for(int k=pc1; k!=pc2; k++){
				k %= cid;
				if(k==0 && pc2==0) break;
				if(popAux[ind1*cid + j]==popAux[ind1*cid + k]){
					popAux[ind1*cid + j] = popAux[ind2*cid + k];
					sub = true;
				}
				if(popAux[ind2*cid + j]==popAux[ind2*cid + k]){
					popAux[ind2*cid + j] = popAux[ind1*cid + k]; 
					sub = true;
				}
				if(sub) k = pc1-1;
				sub = false; 
			}
		}
		/*cout << "ind1 = ";
		for(int h=0; h<cid; h++){
			cout << popAux[ind1*cid + h] << " ";
		}cout << endl;
		
		cout << "ind2 = ";
		for(int h=0; h<cid; h++){
			cout << popAux[ind2*cid + h] << " ";
		}cout << endl;*/
	}
//	cout << "------------------" << endl;
}

void mutacao(int* popAux, float* notas, float pm, int popSize, int metSel){
	int mutacoes=0, cid1=0, cid2=0, aux=0, ind=0;
	float notaAux=0.0f;
	mutacoes = ceil(pm * popSize * cid);
//	cout << "mutacao: " << endl;
	for(int i=0; i<mutacoes; i++){
		ind = rand() % popSize;
		cid1 = rand() % cid;
		cid2 = rand() % cid;
//		cout << "ind = " << ind << ", cid1 = " << cid1 << ", cid2 = " << cid2 << endl;
		aux = popAux[ind*cid + cid1];
		popAux[ind*cid + cid1] = popAux[ind*cid + cid2];
		popAux[ind*cid + cid2] = aux;
	}
//	cout << "----------------" << endl;
}




/*
Algoritmo Genético Simples {
Definindo {
função desempenho
formação do indivíduo e tamanho da população
probabilidade dos operadores
}
Inicializar população aleatória
Enquanto não alcançar critério de convergência faça {
avaliar os indivíduos da população
executar seleção
executar cruzamento e mutação
}
}
*/

int main(int argc, char** argv){
	struct timeval tempoIni, tempoFim;
	gettimeofday(&tempoIni, NULL);
	float pc=0.0f, pm=0.0f, *notas;
	int popSize=0, maxGen=0, metSel=0, rnd=0, opt=0, *pop, *popAux;
	srand ( time(NULL) );
	setCities(argv[1], atof(argv[2]), atoi(argv[3]));
	pc = atof(argv[4]);
	pm = atof(argv[5]);
	popSize = atoi(argv[6]);
	maxGen = atoi(argv[7]);
	metSel = atoi(argv[8]);
	cout << "cid = " << cid << ", popSize = " << popSize << ", pc = " << pc  << ", pm = " << pm << ", maxGen = " << maxGen << endl;

	pop = (int*)malloc(popSize*cid*sizeof(int));
	popAux = (int*)malloc(popSize*cid*sizeof(int));
	notas = (float*)malloc(popSize*sizeof(float));

	iniciaPopulacao(pop, popSize);
	avaliar(pop, notas, popSize);
	for(int j=0; j<popSize; j++){
		for(int k=0; k<cid; k++){
			popAux[j*cid + k] = pop[j*cid + k];
		}
	}
	plotaEvolucao(1, 0, popSize, notas, 0);
					
	for(int i=0; i<maxGen; i++){
		//avaliar
		//selecionar
		//cruzar
		//mutar
		
		avaliar(pop, notas, popSize);
		seleciona(pop, popAux, notas, popSize, metSel);
		crossoverPMX(popAux, notas, pc, popSize, metSel);
		mutacao(popAux, notas, pm, popSize, metSel);
		
		rnd = rand()%popSize; //escolha aleatória de indivíduo para ser substituído pela elite
		opt = top1(popSize, notas); //melhor indivíduo de notas
		for(int j=0; j<cid; j++){
			popAux[rnd * cid + j] = pop[opt * cid + j];
		}

		for(int j=0; j<popSize; j++){
			for(int k=0; k<cid; k++){
				pop[j*cid + k] = popAux[j*cid + k];
			}
			notas[j] = notas[j];
		}
		plotaEvolucao(0, i+1, popSize, notas, 0);		
		if(i%50==0){
			//plotaEvolucao(0, i+1, popSize, notas, 0);		
		//	plotaNotas(i+1, popSize, notas);
		//	char as[32];
		//	gets(as);
		}
	}
	
	avaliar(pop, notas, popSize);
	opt = top1(popSize, notas);

	plotaEvolucao(0, maxGen, popSize, notas, 1);
	plotaIndividuo(pop, opt);

	cout << "melhor individuo: " << opt << ", com nota = " << notas[opt] << endl;
	cout << "trajeto: ";
	for(int i=0; i<cid; i++)
		cout << pop[opt*cid + i] << " ";
	cout << endl;
	
	gettimeofday(&tempoFim, NULL);
	cout << "Tempo exec = " << gettime(tempoIni, tempoFim) << endl;

	free(pop);
	free(popAux);
	free(notas);
	return 0;
}

/*
Para imprimir indivíduos e notas, além de apresentar o melhor:
cout << endl;
	for(int i=0; i<popSize; i++){
		cout << "pop[" << i << "] = ";
		for(int j=0; j<cid; j++)
			cout << pop[i*cid + j] << " ";
		cout << endl;	
	}
	cout << endl;
	for(int i=0; i<popSize; i++)
		cout << "nota[" << i << "] = " << notas[i] << endl;
	cout << "melhor = " << top1(popSize, notas) << endl;
*/
