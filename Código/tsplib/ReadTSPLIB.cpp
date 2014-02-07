#include "../programa.h"

void encerra(string str){
	cout << "arquivo TSPLIB em formato " << str << ", ainda, nao suportado!" << endl;
	for(int i=0; i<num_cid; i++){
		cities[i].longitude = i;
		cities[i].latitude = i;
	}
	exit(1);
}

void setCities(const char* filename){//
    int ch=0, i1=0, numCoord;
    FILE *f;
    char str[256];
    cities = (city*)malloc(num_cid*sizeof(city));
    assert (cities);
    f = fopen(filename, "r");
    if (f == NULL) {printf("nao pode abrir o arquivo %s\n", filename); exit(-1);}

	do{
		fscanf(f, "%s", str);
		if(strcmp(str, "TYPE:") == 0 || strcmp(str, "TYPE :") == 0){
			fscanf(f, "%s", str);
			if(strcmp(str, "TSP") != 0){
				cout << "Tipo " << str << " ainda nao e suportado!" << endl;
        		exit(-1);
			}
		}else if(string::npos != ((string)str).find("DIMENSION")){
			fscanf(f, "%d\n", &num_cid);
			if(strcmp(edge_weight_type, ":")==0) fscanf(f, "%s\n", edge_weight_type);
		}else if(string::npos != ((string)str).find("EDGE_WEIGHT_TYPE")){
			fscanf(f, "%s\n", edge_weight_type);
			if(strcmp(edge_weight_type, ":")==0) fscanf(f, "%s\n", edge_weight_type);
		}else if (string::npos != ((string)str).find("EOF")) {
        	cout << "arquivo em formato incorreto" << endl;
        	exit(-1);
    	}
	}while(strcmp(str, "NODE_COORD_SECTION") != 0);   
	

	if(strcmp(edge_weight_type, "EUC_2D") == 0 || strcmp(edge_weight_type, "MAX_2D") == 0 || strcmp(edge_weight_type, "MAN_2D") == 0 || strcmp(edge_weight_type, "CEIL_2D") == 0 || strcmp(edge_weight_type, "ATT") == 0){
		while (i1 < num_cid){
        	fscanf(f, "%s", str);
        	i1 = atoi(str);
        	fscanf(f, "%s", str);
        	cities[i1-1].longitude = atof(str);
        	fscanf(f, "%s", str);
        	cities[i1-1].latitude = atof(str);
    	}
	}else if(strcmp(edge_weight_type, "EUC_3D") == 0 || strcmp(edge_weight_type, "MAX_3D") == 0 || strcmp(edge_weight_type, "MAN_3D") == 0){
		while (i1 < num_cid){
        	fscanf(f, "%s", str);
        	i1 = atoi(str);
        	fscanf(f, "%s", str);
        	cities[i1-1].longitude = atof(str);
        	fscanf(f, "%s", str);
        	cities[i1-1].latitude = atof(str);
			fscanf(f, "%s", str);
        	cities[i1-1].profundidade = atof(str);
    	}
	}else if(strcmp(edge_weight_type, "GEO") == 0){
		float x=0.0f, y=0.0f, min=0.0f;
		int deg=0;
		while (i1 < num_cid){
        	fscanf(f, "%s", str);
        	i1 = atoi(str);
        	fscanf(f, "%s", str);
			x = atof(str);
			deg = (int)x;
			min = x - deg;
			cities[i1-1].latitude = M_PI * (deg + 5.0f * min / 3.0f ) / 180.0f;
			fscanf(f, "%s", str);
        	y = atof(str);
			deg = (int)y;
			min = y - deg;
			cities[i1-1].longitude = M_PI * (deg + 5.0f * min / 3.0f ) / 180.0f;
    	}
	}else if(strcmp(edge_weight_type, "EXPLICIT") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "XRAY1") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "XRAY2") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "SPECIAL") == 0){
		encerra(edge_weight_type);
	}else{
		cout << "arquivo em formato incorreto" << endl;
        encerra(edge_weight_type);
	}

    fscanf(f, "%s", str);
    if (strcmp(str, "EOF") != 0 && strcmp(str, "-1") != 0) {
        printf("'EOF' nao encontrado\n");
        falha=true;
    }
    fclose(f);
}

void setDistancias(){
	int i=0, j=0;
    distancias = (float*)calloc(num_cid*num_cid, sizeof(float));
    if(strcmp(edge_weight_type, "EUC_2D") == 0){
		for(i=0; i<num_cid; i++){
      	  	for(j=0; j<num_cid; j++){
        	    distancias[i*num_cid + j] = sqrt(pow(cities[i].longitude - cities[j].longitude, 2.0f) + pow(cities[i].latitude - cities[j].latitude, 2.0f));
        	}
    	}
	}else if(strcmp(edge_weight_type, "MAX_2D") == 0){
		float xd=0.0f, yd=0.0f;		
		for(i=0; i<num_cid; i++){
      	  	for(j=0; j<num_cid; j++){
				xd = abs(cities[i].longitude - cities[j].longitude);
				yd = abs(cities[i].latitude -cities[j].latitude);
        	    distancias[i*num_cid + j] = max( xd, yd );
        	}
    	}
	}else if(strcmp(edge_weight_type, "MAN_2D") == 0){
		float xd=0.0f, yd=0.0f;		
		for(i=0; i<num_cid; i++){
      	  for(j=0; j<num_cid; j++){
				xd = abs(cities[i].longitude - cities[j].longitude);
				yd = abs(cities[i].latitude -cities[j].latitude);
				distancias[i*num_cid + j] = (int)( xd + yd );
        	}
    	}
	}else if(strcmp(edge_weight_type, "CEIL_2D") == 0){
		for(i=0; i<num_cid; i++){
      	  	for(j=0; j<num_cid; j++){
        	    distancias[i*num_cid + j] = ceil(sqrt(pow(cities[i].longitude - cities[j].longitude, 2.0f) + pow(cities[i].latitude - cities[j].latitude, 2.0f)));
        	}
    	}
	}else if(strcmp(edge_weight_type, "EUC_3D") == 0){
		for(i=0; i<num_cid; i++){
      	  	for(j=0; j<num_cid; j++){
        	    distancias[i*num_cid + j] = sqrt(pow(cities[i].longitude - cities[j].longitude, 2.0f) + pow(cities[i].latitude - cities[j].latitude, 2.0f) + pow(cities[i].profundidade - cities[j].profundidade, 2.0f));
			}
    	}
	}else if(strcmp(edge_weight_type, "MAX_3D") == 0){
		float xd=0.0f, yd=0.0f, zd=0.0f;		
		for(i=0; i<num_cid; i++){
      	  for(j=0; j<num_cid; j++){
				xd = abs(cities[i].longitude - cities[j].longitude);
				yd = abs(cities[i].latitude -cities[j].latitude);
				zd = abs(cities[i].profundidade -cities[j].profundidade);
        	    distancias[i*num_cid + j] = max( max(xd, yd), zd );
        	}
    	}
	}else if(strcmp(edge_weight_type, "MAN_3D") == 0){
		float xd=0.0f, yd=0.0f, zd=0.0f;		
		for(i=0; i<num_cid; i++){
      	  for(j=0; j<num_cid; j++){
				xd = abs(cities[i].longitude - cities[j].longitude);
				yd = abs(cities[i].latitude -cities[j].latitude);
				zd = abs(cities[i].profundidade -cities[j].profundidade);
        	    distancias[i*num_cid + j] = (int)( xd + yd + zd );
        	}
    	}
	}else if(strcmp(edge_weight_type, "GEO") == 0){
		float RRR = 6378.388f, q1=0.0f, q2=0.0f, q3=0.0f;
		for(i=0; i<num_cid; i++){
			for(j=0; j<num_cid; j++){
				q1 = cos(cities[i].longitude - cities[j].longitude);
				q2 = cos(cities[i].latitude - cities[j].latitude);
				q3 = cos(cities[i].latitude + cities[j].latitude);
				distancias[i*num_cid + j] = floor( RRR * acos( 0.5f * ((1.0f + q1) * q2 - (1.0f - q1) * q3) ) + 1.0f);
			}
		}
		
	}else if(strcmp(edge_weight_type, "ATT") == 0){
		float xd=0.0f, yd=0.0f, rij=0.0f;
		int tij=0;		
		for(i=0; i<num_cid; i++){
      	  	for(j=0; j<num_cid; j++){
				xd = cities[i].longitude - cities[j].longitude;
				yd = cities[i].latitude - cities[j].latitude;
				rij = sqrt( pow(xd, 2.0f) + pow(yd, 2.0f) / 10.0f);
				tij = (int)rij;
				if(tij < rij)
        	    	distancias[i*num_cid + j] = tij + 1;
				else 
					distancias[i*num_cid + j] = tij;
        	}
    	}
	}else if(strcmp(edge_weight_type, "EXPLICIT") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "XRAY1") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "XRAY2") == 0){
		encerra(edge_weight_type);
	}else if(strcmp(edge_weight_type, "SPECIAL") == 0){
		encerra(edge_weight_type);
	}
    
}

void setIndOtimo(const char* filename, int* opt){
	int i1=0;
    FILE *f;
    char str[256];
    f = fopen(filename, "r");
    if (f == NULL) {printf("nao pode abrir o arquivo %s\n", filename); exit(-1);}

	do{ fscanf(f, "%s", str); }while(strcmp(str, "TOUR_SECTION") != 0);   

	while (i1 < num_cid){
       	fscanf(f, "%s", str);
       	opt[i1] = atoi(str);
		i1++;
    }

	fclose(f);
}
