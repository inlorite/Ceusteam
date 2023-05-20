#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleado.h"

#define RUTA "../files/BinarioEmpleados.dat"

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h)
{
	FILE *file;

	file = fopen(RUTA, "rb");

	int auxId;

	// Read
	for (int i = 0; i < *numEmpleados; ++i) {
		fread(&arrayEmpleados[i].id, sizeof(int), 1, file);
		fread(arrayEmpleados[i].nombre, sizeof(char) * 20, 1, file);
		fread(&auxId, sizeof(int), 1, file);
		arrayEmpleados[i].hotel = &h[auxId-1];
	}

	fclose(file);
}

void escribirBinarioEmpleado(Empleado* arrayEmpleados, int* numEmpleados)
{
	FILE *file;

	file = fopen(RUTA, "wb");

	// Write
	for (int i = 0; i < *numEmpleados; ++i) {
		fwrite(&arrayEmpleados[i].id, sizeof(int), 1, file);
		fwrite(arrayEmpleados[i].nombre, sizeof(char) * 20, 1, file);
		fwrite(&arrayEmpleados[i].hotel->id, sizeof(int), 1, file);
	}

	fclose(file);
}

/* ------------------
 * FUNCIONES
 * ------------------
*/

void crearEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel)
{
	char nombre[50];
	int idHotel;

	for (int i = 0; i < *numHotel; ++i)
		printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("\n\nIntroduzca el nombre: ");
	scanf("%s", nombre);
	printf("Introduzca el ID del hotel donde trabaja: ");
	scanf("%d", &idHotel);

	if (idHotel > *numHotel)
	{
		printf("\nNo hay ningun hotel con ese ID.");
		return;
	}

	arrayEmpleados[*numEmpleados].id = *numEmpleados + 1;
	arrayEmpleados[*numEmpleados].nombre = malloc(sizeof(char) * strlen(nombre)+1);
	strcpy(arrayEmpleados[*numEmpleados].nombre, nombre);
	arrayEmpleados[*numEmpleados].hotel = recuperarHotel(h, idHotel, *numHotel);

	(*numEmpleados)++;
}

void modificarEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel)
{
	int num_empleado, opcion, idHotel;

	visualizarEmpleados(arrayEmpleados, numEmpleados);

	printf("\n\nIntroduzca el ID del empleado a modificar: ");
	scanf("%d", &num_empleado);

	if (num_empleado-1 > *numEmpleados)
	{
		printf("No existe ningun empleado con ese ID.");
		return;
	}

	// Buscar el empleado con el número introducido
	for (int i = 0; i < *numEmpleados; i++) {
		if (arrayEmpleados[i].id == num_empleado) {
			// Mostrar el menú de opciones
			printf("\n1. Modificar nombre del empleado\n");
			printf("2. Modificar hotel del empleado\n");
			printf("\nSeleccione una opcion: ");
			scanf("%d", &opcion);

			switch (opcion) {
				case 1:
					// Modificar el nombre del empleado
					printf("\n\nIntroduzca el nuevo nombre del empleado: ");
					char nombre[50];
					scanf("%s", nombre);
					arrayEmpleados[i].nombre = malloc(sizeof(char) * strlen(nombre)+1);
					strcpy(arrayEmpleados[i].nombre, nombre);
					printf("Nombre del empleado modificado con exito.\n");
					return;
				case 2:
					// Modificar el hotel
					printf("\n\nIntroduzca el ID del nuevo hotel: ");
					scanf("%d", &idHotel);

					if (idHotel > *numHotel)
					{
						printf("\nNo hay ningun hotel con ese ID.");
						return;
					}

					arrayEmpleados[i].hotel = recuperarHotel(h, idHotel, *numHotel);
					return;
			}
		}
	}
}

void borrarEmpleado(Empleado* arrayEmpleados, int* numEmpleados)
{
	int idEmpleado;

	visualizarEmpleados(arrayEmpleados, numEmpleados);

	printf("\nIntroduzca el ID del empleado a borrar: ");
	scanf("%d", &idEmpleado);

	// Buscar el empleado con el número introducido
	for (int i = 0; i < *numEmpleados; i++) {
		if (arrayEmpleados[i].id == idEmpleado) {
			// Eliminar el empleado y desplazar los demás hacia arriba
			(*numEmpleados)--;
			for (; i < *numEmpleados; i++) {
				arrayEmpleados[i] = arrayEmpleados[i + 1];
				arrayEmpleados[i].id--;
			}
			printf("Empleado eliminado con exito.\n");
			return;
		}
	}

	printf("El empleado no existe.\n");
}

void consultarPlantilla(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel)
{
	int idHotel;

	for (int i = 0; i < *numHotel; ++i)
		printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("\n\nSeleccione el ID del hotel cuya plantilla quiera consultar: ");
	scanf("%d", &idHotel);

	if (idHotel-1 > *numHotel || idHotel == 0) {
		printf("\nNo hay ningun hotel con ese ID.");
		return;
	}

	printf("\n[EMPLEADOS EN PLANTILLA]\n"
			"------------------------\n");
	for (int i = 0; i < *numEmpleados; ++i) {
		if (arrayEmpleados[i].hotel->id == idHotel-1)
			printf("ID: %d, Nombre: %s\n", arrayEmpleados[i].id, arrayEmpleados[i].nombre);
	}
}

void visualizarEmpleados(Empleado* arrayEmpleados, int* numEmpleados)
{
	printf("\n[LISTA DE EMPLEADOS]\n"
			"---------------------\n");

	for (int i = 0; i < *numEmpleados; ++i) {
		printf("ID: %d, Nombre: %s | Hotel: %d, %s\n", arrayEmpleados[i].id, arrayEmpleados[i].nombre, arrayEmpleados[i].hotel->id, arrayEmpleados[i].hotel->nombre);
	}
}
