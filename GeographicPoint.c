//Encuentra el punto nemo. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define max_lat 500
#define max_lng 744

//Define funciones
int I(int lat, int lng);
float radio(int lat_p, int lng_p, int lat, int lng);
float menor_radio(int *mapa);


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

float menor_radio(int *mapa){
	int i;
	int j;
	int lat_p=rand() % max_lat;
	int lng_p=rand() % max_lng;
	float R1=1000.0;
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
	return R1;
}

//Main
int main(void){

	//Lee archivo
	FILE *in;
	in=fopen("map_data.txt","r");
	//Contadores para leer
	int i=0;
	int j=0;

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
				printf("%d\n", j);
			}
		//printf("%d\n", i);
		i++;
		j=0;
	}

	fclose(in);	

	//Prueba de lectura de datos
	int c;
	int d;
	for(c=0;c<max_lat;c++){
		for(d=0;d<max_lng;d++){
			printf("dato (%d,%d): %d\n",c,d, mapa[I(c,d)]);
		}
	}

	return 0;
}


















