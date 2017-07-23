//Encuentra el punto nemo. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//Define funciones
//float menor_radio();
int I(int lat, int lng);

//Funciones
int I(int lat, int lng){
	int i;
	i=lat*744+lng;
	return i;
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
	int len=10;
	char datos[len];
	char *dato_I;
	const char *delimiter;
	delimiter = " ,-.";

	//Matriz donde se guardan los datos leidos
	int *mapa;
	mapa=malloc(744*500*sizeof(int));

	
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
	for(c=0;c<500;c++){
		for(d=0;d<744;d++){
			printf("dato (%d,%d): %d\n",c,d, mapa[I(c,d)]);
		}
	}

	return 0;
}


















