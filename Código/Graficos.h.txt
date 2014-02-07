
/**
PRE-REQUISITO: ter incluído ReadTSPLIB.h antes deste cabeçalho
*/

/**
Grava as notas de todos indivíduos e executa script para geração de gráfico
*/
void plotaNotas(int geracao, int popSize, float* notas){
    int i;
    FILE *nts;
    nts = fopen ("Notas", "w");
    fprintf(nts, "Geracao %d\n", geracao);
    for(i=0; i < popSize; i++){
        fprintf(nts, "%d %f\n", i, notas[i]);
    }
    fclose(nts);
    i = system("./PlotaNotas.sh");
    if(i){
        cout << "system(\"./PlotaNotas.sh\") returned " << i << endl;
    }
}

/**
Grava as coordenadas de cada trecho do indivíduo. Ou seja, o trajeto do individuo ind
*/
void plotaIndividuo(int* populacao, int ind){
    int i;
    FILE *pop;
    pop = fopen ("Pop", "w");

    fprintf(pop, "Indivíduo\n");
    for(i=0; i < cid; i++){
        fprintf(pop, "%f %f\n", cities[populacao[ind*cid + i]].longitude, cities[populacao[ind*cid + i]].latitude);
    } fprintf(pop, "%f %f\n", cities[populacao[ind*cid]].longitude, cities[populacao[ind*cid]].latitude);
    fclose(pop);
    i = system("./PlotaPop.sh");
    if(i){
        cout << "system(\"./PlotaPop.sh\") returned " << i << endl;
    }
}

/**
Retorna o menor valor em notas
*/
float getMenorInd(float* notas, int popSize){
	float menor=notas[0];
	for(int i=1; i<popSize; i++){
		if(notas[i]<menor){
			menor = notas[i];
		}
	}
	return menor;
}

/**
Retorna o maior valor em notas
*/
float getMaiorInd(float* notas, int popSize){
	float maior=notas[0];
	for(int i=1; i<popSize; i++){
		if(notas[i]>maior){
			maior = notas[i];
		}
	}
	return maior;
}

/**
Grava o menor valor, a média e o maior valor em notas.
*/
void plotaEvolucao(int apaga, int gen, int popSize, float* notas, int plota){
    FILE *pop;
    if(apaga == 1){
        pop = fopen("Evolution", "w");
        fprintf(pop, " ");
        fclose(pop);
    }
    else{
        pop = fopen ("Evolution", "a");
        float media = 0.0f;
        for(int i=0; i<popSize; i++){
            media += notas[i];
        } 
        media /= popSize;
        fprintf(pop, "%d %f %f %f\n", gen, getMenorInd(notas, popSize), getMaiorInd(notas, popSize), media);
        fclose(pop);
        if(plota)
        	system("./PlotaEvolution.sh");
    }
}

