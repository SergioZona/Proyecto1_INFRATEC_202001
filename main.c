/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
Integrante 1 - Sergio Julian Zona Moreno (201914936) --- Correo: sj.zona@uniandes.edu.co
Integrante 2 - Diego Felipe Carvajal Lombo (201911910) --- Correo: df.carjaval@uniandes.edu.co
Integrante 3 - Andres Takashi Bravo Yaguchi (201911714) --- Correo: at.bravo@uniandes.edu.co
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
	int tamanio;
	unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(Datos * archivoEnBinario, char *);
void convertirABinario(Datos * archivo, Datos * archivoEnBinario);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
	FILE *file;
	int n;

	file = fopen(nombreArchivo, "rb");

	if (!file)
	{
		printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	n = ftell(file);
	fseek(file, 0, SEEK_SET);

	archivo->tamanio = n;
	archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));

	fread(archivo->informacion, sizeof(unsigned char), n, file);

	fclose(file);

	return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(Datos * archivoEnOctal, char *nombreArchivo)
{
	FILE *file;

	file = fopen(nombreArchivo, "wb");

	if (!file) {
		printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
 	fwrite(archivoEnOctal->informacion, sizeof(char), archivoEnOctal->tamanio, file);

	fclose(file);
}


// Esta funcion se encarga de convertir a binario cada uno de los caracteres que se
// encuentran en la estructura datosOct->informacion y asignar los nuevos valores a la estructura datosBin->informacion.
// Deben desarrollar esta funcion en su totalidad.
void convertirABinario(Datos * datosOct, Datos * datosBin)
{
	int valor=datosOct->tamanio; //Tamaño del arreglo del archivo octal.
	int numCeros=8-(3*valor%8); //Número de ceros para completar octetos.
	//Arreglo de caracteres que guardará la traducción a binario del archivo octal.
	char *arreglo = (unsigned char *)calloc((3*valor+numCeros), sizeof(unsigned char));
	//for que recorre de a 3 posiciones el arreglo por cada dígito octal leído. Guarda en estas posiciones según sea necesaria la traducción. (i.e) Si llega 7, guarda "111".
	for(int i=0; i<(3*valor);i=i+3)
	{
		int actual=datosOct->informacion[i/3] -'0';
		arreglo[i]=actual==0?'0':actual==1?'0':actual==2?'0':actual==3?'0':actual==4?'1':actual==5?'1':actual==6?'1':'1';
		arreglo[i+1]=actual==0?'0':actual==1?'0':actual==2?'1':actual==3?'1':actual==4?'0':actual==5?'0':actual==6?'1':'1';
		arreglo[i+2]=actual==0?'0':actual==1?'1':actual==2?'0':actual==3?'1':actual==4?'0':actual==5?'1':actual==6?'0':'1';
	}
	//Número de ceros al final de la cadena para completar octetos.
	for(int i=0; i<numCeros;++i)
    {
        arreglo[(3*valor)+i]=('0');
    }
	//for que transforma octetos binarios en caracteres. Realizo operador OR entre bits y busca en la tabla ascii el valor correspondiente. Recorre de a 8 porque son octetos. Finalmente agrega el valor a la información.
	for(int i=0; i<(3*valor+numCeros);i=i+8)
	{	
		char caracter='\0';
		if(arreglo[i]=='1')
		{
			caracter=128;
		}
		if(arreglo[i+1]=='1')
		{
			caracter=caracter^(64);
		}
		if(arreglo[i+2]=='1')
		{
			caracter=caracter^(32);
		}
		if(arreglo[i+3]=='1')
		{
			caracter=caracter^(16);
		}
		if(arreglo[i+4]=='1')
		{
			caracter=caracter^(8);
		}
		if(arreglo[i+5]=='1')
		{
			caracter=caracter^(4);
		}
		if(arreglo[i+6]=='1')
		{
			caracter=caracter^(2);
		}
		if(arreglo[i+7]=='1')
		{
			caracter=caracter^(1);
		}
		datosBin->informacion[i/8]=caracter;
	}
	//TODO: COMPLETAR EL DESARROLLO DE LA FUNCION.
}

//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC (ISIS-1304)");

	// Declaracion de todas las variables necesarias.
	int tamanio;
	int tamanioRepBinario;
	char nombreArchivo[200];
	char nombreArchivoBinario[200];
	Datos * archivoOctal = (Datos *)malloc(sizeof(Datos));
	Datos * archivoEnBinario = (Datos *)malloc(sizeof(Datos));

	printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
	scanf("%s", nombreArchivo);
	tamanio = readFile(archivoOctal, nombreArchivo);
	printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
	tamanioRepBinario = ((tamanio * 3) / 8) + (((tamanio*3) % 8 == 0)? 0 : 1);
	archivoEnBinario->informacion = (unsigned char *)calloc(tamanioRepBinario, sizeof(unsigned char));
	archivoEnBinario->tamanio = tamanioRepBinario;
	printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
	scanf("%s", nombreArchivoBinario);
	convertirABinario(archivoOctal, archivoEnBinario);
	writeFile(archivoEnBinario, nombreArchivoBinario);
	printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
	printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoBinario);

	// Terminar
	system("PAUSE");
	return 0;
}

