//Encuentra el punto nemo. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define max_lat 500
#define max_lng 744

//Define funciones
int I(int lat, int lng);
float radio(int lat_p, int lng_p, int lat, int lng);
float menor_radio(int *mapa, int lat_p, int lng_p);
int rdm(int centro);
int *MH(int *mapa);

//Funciones
int I(int lat, int lng){
	int i;
	i=lat*max_lng+lng;
	return i;
}

float radio(int lat_p, int lng_p, int lat, int lng){
	float x2;
	float y2;
	float R;
	x2=pow((lng_p-lng),2);
	y2=pow((lat_p-lat),2);
	R=sqrt(x2+y2);
	return R;
}

float menor_radio(int *mapa, int lat_p, int lng_p){
	int i;
	int j;
	//int lat_p=rand() % max_lat;
	//int lng_p=rand() % max_lng;
	float R1=1000.0;

	//if(lat_p>=500 || lng_p>=744){
	//	printf("%s\n", "Coordenada fuera de rango");
	//}
	//else{
		for(i=0;i<max_lat;i++){
			for(j=0;j<max_lng;j++){
				if(mapa[I(i,j)]==1){
					float R2;
					R2=radio(lat_p, lng_p, i, j);
						if(R2<R1){
							R1=R2;
						}
				}
			}
		}
	//}
	return R1;
}

int rdm(int centro){
	int x;
	int max=centro+300;
	int min=centro-300;
	x=(((max-min)*((float) rand()/RAND_MAX))+min);
	return x;
}

int *MH(int *mapa){
	
	int *Nemo;
	Nemo=malloc(2*sizeof(int));

	int n_iterations=2000;
	int lat_0=390;
	int lng_0=100;	

	int *LAT;
	LAT=malloc(n_iterations*sizeof(int));

	int *LNG;
	LNG=malloc(n_iterations*sizeof(int));

	float *R;
	R=malloc(n_iterations*sizeof(float));

	LAT[0]=lat_0;
	LNG[0]=lng_0;

	//Loop de Metropolis-Hasting
	int i;
	for(i=1;i<n_iterations;i++){
		int lat_prime = rdm(lat_0);
		lat_prime=lat_prime%max_lat;
		int lng_prime = rdm(lng_0);
		lng_prime=lng_prime%max_lng;
		if(lat_prime<0){
			lat_prime=-lat_prime;
		}
		if(lng_prime<0){
			lng_prime=-lng_prime;
		}
		//printf("%d\n", lat_prime);
		//printf("%d\n", lng_prime);
		float alpha=menor_radio(mapa, lat_prime, lng_prime)/menor_radio(mapa, lat_0, lng_0);
		if(alpha>=1.0){
			LAT[i]=lat_prime;
			LNG[i]=lng_prime;
		}
		else{
			float beta =(float) rand()/RAND_MAX;
			if(beta<=alpha){
				LAT[i]=lat_prime;
				LNG[i]=lng_prime;
			}
			else{
				LAT[i]=LAT[i-1];
				LNG[i]=LNG[i-1];
			}
		}
	}
	
	//Promedio 
	int LAT_NEMO=0;
	int LNG_NEMO=0;
	int c;
	for(c=0;c<n_iterations;c++){
		LAT_NEMO=LAT_NEMO+LAT[c];
		LNG_NEMO=LNG_NEMO+LNG[c];
	}
	
	Nemo[0]=LAT_NEMO/n_iterations;
	Nemo[1]=LNG_NEMO/n_iterations;

	return Nemo;
}

//Main
int main(void){

	//Lee archivo
	FILE *in;
	in=fopen("map_data.txt","r");
	//Contadores para leer
	int i=0;
	int j=0;
	//seed
	srand((unsigned)time(NULL));

	//Delimiter
	int len=2000;
	char datos[len];
	char *dato_I;
	const char *delimiter;
	delimiter = " ";

	//Matriz donde se guardan los datos leidos
	int *mapa;
	mapa=malloc(max_lat*max_lng*sizeof(int));

	
	while(fgets(datos, len ,in)){
		dato_I=strtok(datos, delimiter);
			while(dato_I != NULL){
				mapa[I(i,j)]=atoi(dato_I);
				j++;
				dato_I=strtok(NULL, delimiter);
			}
		i++;
		j=0;
	}

	fclose(in);	

	//Prueba de lectura de datos
	//int c;
	//int d;
	//for(c=0;c<max_lat;c++){
	//	for(d=0;d<max_lng;d++){
	//		printf("dato (%d,%d): %d\n",c,d, mapa[I(c,d)]);
	//	}
	//}

	printf("%d\n", MH(mapa)[0]);
	printf("%d\n", MH(mapa)[1]);

	//Se escribe un archivo con los datos
	FILE *out;
	int c; //Contador para tiempo
	int n; //Contador para planeta
	char resultados[200]="coordNemo.csv";

	out=fopen(resultados, "w");
	if(!out){
		printf("problems opening the file %s\n", resultados);
		exit(1);
	} 

	//Se escriben las coordenadas del punto Nemo(indices en el mapa).
		fprintf(out, "%d, %d\n", MH(mapa)[0], MH(mapa)[1]);


	return 0;
}


















