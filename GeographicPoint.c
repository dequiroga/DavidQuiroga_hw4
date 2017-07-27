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
	Nemo=malloc(3*sizeof(int));

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
		lat_prime=lat_prime%max_lat; //Para no salir del mapa
		int lng_prime = rdm(lng_0);
		lng_prime=lng_prime%max_lng; //Para no salir del mapa
		if(lat_prime<0){   
			lat_prime=-lat_prime;  //Para evitar negtivos
		}
		if(lng_prime<0){
			lng_prime=-lng_prime;  //Para evitar negativos
		}
		float alpha=exp(pow(menor_radio(mapa, lat_prime, lng_prime)-menor_radio(mapa, LAT[i-1], LNG[i-0]),2));
		if(alpha>=1.0){
			LAT[i]=lat_prime;
			LNG[i]=lng_prime;
			R[i]=menor_radio(mapa, lat_prime, lng_prime);
		}
		else{
			float beta =(float) rand()/RAND_MAX;
			if(beta<=alpha){
				LAT[i]=lat_prime;
				LNG[i]=lng_prime;
				R[i]=menor_radio(mapa, lat_prime, lng_prime);
			}
			else{
				LAT[i]=LAT[i-1];
				LNG[i]=LNG[i-1];
				R[i]=menor_radio(mapa, LAT[i-1], LNG[i-1]);
			}
		}
	}
	
	//Promedio 
	int k; //Indice maximo de latitud y longitud
	float R_max=0;
	int c;
	for(c=0;c<n_iterations;c++){
		if(R[c]>R_max){
			R_max=R[c];
			k=c;
		}
	}
	
	Nemo[0]=LAT[k];
	Nemo[1]=LNG[k];
	Nemo[2]=R_max;

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
	//seed para que el random de distinto
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

	//Coordenadas en latitud longitud
	float latitud;
	latitud=((MH(mapa)[0]*180.0)/-500.0)+90.0;

	float longitud;
	longitud=((MH(mapa)[1]*360.0)/744.0)-180.0;

	float RR;
	float radiox;
	RR=MH(mapa)[2];
	radiox=RR*360.0/744.0;
	float radioy;
	radioy=RR*180.0/500.0;

	//Imprime coordenadas
	printf("las coordenadas del punto más alejado son: %f, %f\n", longitud, latitud);

	//Se escribe un archivo con las coordenadas
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
		fprintf(out, "%f, %f, %f, %f\n", latitud, longitud, radiox, radioy);


	return 0;
}


















