#include <stdio.h>
#include <stdlib.h>
#include "admin.h"

#define RUTAA "../files/BinarioAdmins.dat"

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioAdmin(Admin* a, int numAdmins)
{
	FILE *file = fopen(RUTAA, "rb");

	fread(a, sizeof(Admin), numAdmins, file);

	printf("\nDatos cargados desde: %s\n", RUTAA);
}

void escribirBinarioAdmin(Admin* a, int numAdmins)
{
	FILE *file = fopen(RUTAA, "wb");

	fwrite(a, sizeof(Admin), numAdmins, file);

	fclose(file);

	printf("\nDatos guardados en: %s\n", RUTAA);
}

/* ------------------
 * FUNCIONES
 * ------------------
*/

void imprimirAdmin(Admin a)
{
	printf("ID: %d, Nombre: %s\n", a.id, a.nombre);
}

void crearAdmin(Admin* arrayAdmins, int* numAdmins)
{
	Admin* a = malloc(sizeof(Admin));
	a->id = *numAdmins + 1;

	printf("Introduzca el nombre: ");
	scanf("%s", a->nombre);
	printf("Introduzca una contrasena: ");
	scanf("%s", a->contrasena);

	arrayAdmins[*numAdmins] = *a;
	(*numAdmins)++;
}

void modificarAdmin(Admin* arrayAdmins, int* numAdmins)
{
	int idAdmin, opcion;

	printf("Listado de Admins:\n\n");
	for (int i = 0; i < *numAdmins; ++i) {
		printf("- ID: %d, Nombre: %s\n", arrayAdmins[i].id, arrayAdmins[i].nombre);
	}

	printf("\nIntroduce el ID del Admin a modificar: ");
	scanf("%d", &idAdmin);

	printf("\n\n1. Modificar nombre\n");
	printf("2. Modificar contrasena\n");
	scanf("%d", &opcion);

	switch (opcion) {
		case 1:
			printf("Introduce el nuevo nombre: ");
			scanf("%s", arrayAdmins[idAdmin-1].nombre);
			return;

		case 2:
			printf("Introduce la nueva contrasena: ");
			scanf("%s", arrayAdmins[idAdmin-1].contrasena);
			return;
	}

}

void borrarAdmin(Admin* arrayAdmins, int* numAdmins)
{
	int idAdmin;

	visualizarEmpleados(arrayAdmins, numAdmins);

	printf("\nIntroduzca el ID del Admin a borrar: ");
	scanf("%d", &idAdmin);

	// Buscar el Admin con el número introducido
	for (int i = 0; i < *numAdmins; i++) {
		if (arrayAdmins[i].id == idAdmin) {
			// Eliminar el Admin y desplazar los demás hacia arriba
			(*numAdmins)--;
			for (; i < *numAdmins; i++) {
				arrayAdmins[i] = arrayAdmins[i + 1];
				arrayAdmins[i].id--;
			}
			printf("Admin eliminado con exito.\n");
			return;
		}
	}

	printf("El Admin no existe.\n");
}

void consultarAdmin(Admin* arrayAdmins, int* numAdmins)
{
	int idAdmin;

	printf("Listado de Admins:\n\n");
	for (int i = 0; i < *numAdmins; ++i) {
		printf("- ID: %d, Nombre: %s\n", arrayAdmins[i].id, arrayAdmins[i].nombre);
	}

	printf("\nSelecciona el id del Admin que quieres consultar: ");
	scanf("%d", &idAdmin);

	if (idAdmin-1 > *numAdmins) {
		printf("\nNo hay ningun Admin con ese ID.");
		return;
	}

	imprimirAdmin(arrayAdmins[idAdmin-1]);
}
