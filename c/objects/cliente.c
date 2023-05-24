#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

#define RUTAC "../files/BinarioClientes.dat"
#define RUTAR "../files/BinarioReservas.dat"

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioCliente(Cliente* c, int numClientes)
{
	FILE *file = fopen(RUTAC, "rb");

	fread(c, sizeof(Cliente), numClientes, file);

	printf("\nDatos cargados desde: %s\n", RUTAC);
}

void escribirBinarioCliente(Cliente* c, int numClientes)
{
	FILE *file = fopen(RUTAC, "wb");

	fwrite(c, sizeof(Cliente), numClientes, file);

	fclose(file);

	printf("\nDatos guardados en: %s\n", RUTAC);
}

void leerBinarioReserva(Reserva* r, int numReserva, Cliente* c, Hotel* h)
{
	FILE *file = fopen(RUTAR, "rb");

	int idCliente, idHotel, numHabitacion;

	for (int i = 0; i < numReserva; ++i) {
		fread(&idCliente, sizeof(int), 1, file);
		fread(&idHotel, sizeof(int), 1, file);
		fread(&numHabitacion, sizeof(int), 1, file);

		r[i].cliente = &c[idCliente-1];
		r[i].hotel = &h[idHotel-1];
		r[i].numHabitacion = numHabitacion;
	}

	printf("\nDatos cargados desde: %s\n", RUTAR);
}

void escribirBinarioReserva(Reserva* r, int numReserva)
{
	FILE *file = fopen(RUTAR, "wb");

	for (int i = 0; i < numReserva; ++i) {
		fwrite(&r[i].cliente->id, sizeof(int), 1, file);
		fwrite(&r[i].hotel->id, sizeof(int), 1, file);
		fwrite(&r[i].numHabitacion, sizeof(int), 1, file);
	}

	printf("\nDatos cargados desde: %s\n", RUTAR);
}

/* ------------------
 * FUNCIONES
 * ------------------
*/

void imprimirCliente(Cliente c)
{
	printf("ID: %d, Nombre: %s, Email: %s, Telf: %d\n", c.id, c.nombre, c.email, c.numTelf);
}

void crearCliente(Cliente* arrayClientes, int* numClientes)
{
	Cliente* c = malloc(sizeof(Cliente));
	char nombre[50];
	char email[50];
	char contrasena[50];
	c->id = *numClientes + 1;

	printf("Introduzca el nombre: ");
	scanf("%s", nombre);
	c->nombre = malloc(sizeof(char) * strlen(nombre)+1);
	strcpy(c->nombre, nombre);
	printf("Introduzca el email: ");
	scanf("%s", email);
	c->email = malloc(sizeof(char) * strlen(email)+1);
	strcpy(c->email, email);
	printf("Introduzca el numero de telefono: ");
	scanf("%d", &c->numTelf);
	printf("Introduzca una contrasena: ");
	scanf("%s", contrasena);
	c->contrasena = malloc(sizeof(char) * strlen(contrasena)+1);
	strcpy(c->contrasena, contrasena);

	arrayClientes[*numClientes] = *c;
	(*numClientes)++;
}

void modificarCliente(Cliente* arrayClientes, int* numClientes)
{
	int idCliente, opcion;

	printf("Listado de clientes:\n\n");
	for (int i = 0; i < *numClientes; ++i) {
		printf("- ID: %d, Nombre: %s\n", arrayClientes[i].id, arrayClientes[i].nombre);
	}

	printf("\nIntroduce el ID del cliente a modificar: ");
	scanf("%d", &idCliente);

	printf("\n\n1. Modificar nombre\n");
	printf("2. Modificar email\n");
	printf("3. Modificar numero de telefono\n");
	printf("4. Modificar contrasena\n");
	scanf("%d", &opcion);

	switch (opcion) {
		case 1:
			printf("Introduce el nuevo nombre: ");
			char nombre[50];
			scanf("%s", nombre);
			arrayClientes[idCliente-1].nombre = malloc(sizeof(char) * strlen(nombre)+1);
			strcpy(arrayClientes[idCliente-1].nombre, nombre);
			return;

		case 2:
			printf("Introduce el nuevo email: ");
			char email[50];
			scanf("%s", email);
			arrayClientes[idCliente-1].email = malloc(sizeof(char) * strlen(email)+1);
			strcpy(arrayClientes[idCliente-1].email, email);
			return;

		case 3:
			printf("Introduce el nuevo numero de telefono: ");
			scanf("%d", &arrayClientes[idCliente-1].numTelf);
			return;

		case 4:
			printf("Introduce la nueva contrasena: ");
			char contrasena[50];
			scanf("%s", contrasena);
			arrayClientes[idCliente-1].contrasena = malloc(sizeof(char) * strlen(contrasena)+1);
			strcpy(arrayClientes[idCliente-1].contrasena, contrasena);
			return;
	}

}

void borrarCliente(Cliente* arrayClientes, int* numClientes)
{
	int idCliente;

	visualizarEmpleados(arrayClientes, numClientes);

	printf("\nIntroduzca el ID del cliente a borrar: ");
	scanf("%d", &idCliente);

	// Buscar el cliente con el número introducido
	for (int i = 0; i < *numClientes; i++) {
		if (arrayClientes[i].id == idCliente) {
			// Eliminar el cliente y desplazar los demás hacia arriba
			(*numClientes)--;
			for (; i < *numClientes; i++) {
				arrayClientes[i] = arrayClientes[i + 1];
				arrayClientes[i].id--;
			}
			printf("Cliente eliminado con exito.\n");
			return;
		}
	}

	printf("El cliente no existe.\n");
}

void consultarCliente(Cliente* arrayClientes, int* numClientes)
{
	int idCliente;

	printf("Listado de clientes:\n\n");
	for (int i = 0; i < *numClientes; ++i) {
		printf("- ID: %d, Nombre: %s\n", arrayClientes[i].id, arrayClientes[i].nombre);
	}

	printf("\nSelecciona el id del cliente que quieres consultar: ");
	scanf("%d", &idCliente);

	if (idCliente-1 > *numClientes) {
		printf("\nNo hay ningun cliente con ese ID.");
		return;
	}

	imprimirCliente(arrayClientes[idCliente-1]);
}

void anadirReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes, Hotel* h, int* numHoteles)
{
	Reserva* r = malloc(sizeof(Reserva));

	int idCliente, idHotel;

	for (int i = 0; i < *numHoteles; ++i)
			printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("Introduzca el ID del cliente: ");
	scanf("%d", &idCliente);
	printf("Introduzca el ID del hotel: ");
	scanf("%d", &idHotel);
	printf("Introduzca el numero de habitación: ");
	scanf("%d", &r->numHabitacion);

	if (idCliente-1 > *numClientes || idHotel-1 > *numHoteles)
	{
		printf("Error al anadir la reserva.");
		return;
	}

	r->cliente = &c[idCliente-1];
	r->hotel = &h[idHotel-1];

	arrayReservas[*numReservas] = *r;
	(*numReservas)++;
}

void borrarReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes, Hotel* h, int* numHoteles)
{
	int idCliente, idHotel;

	for (int i = 0; i < *numHoteles; ++i)
			printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("Introduzca el ID del cliente: ");
	scanf("%d", &idCliente);
	printf("Introduzca el ID del hotel: ");
	scanf("%d", &idHotel);

	// Buscar la reserva con el número introducido
	for (int i = 0; i < *numReservas; i++) {
		if (arrayReservas[i].cliente->id == idCliente && arrayReservas[i].hotel->id == idHotel) {
			// Eliminar la reserva y desplazar los demás hacia arriba
			(*numReservas)--;
			for (; i < *numReservas; i++) {
				arrayReservas[i] = arrayReservas[i + 1];
			}
			printf("Reserva eliminada con exito.\n");
			return;
		}
	}

	printf("La reserva no existe.\n");
}

void consultarReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes)
{
	int idCliente;

	printf("Listado de clientes:\n\n");
	for (int i = 0; i < *numClientes; ++i) {
		printf("- ID: %d, Nombre: %s\n", c[i].id, c[i].nombre);
	}

	printf("\nSelecciona el ID del cliente cuyas reservas quieras consultar: ");
	scanf("%d", &idCliente);

	if (idCliente-1 > *numClientes) {
		printf("\nNo hay ningun cliente con ese ID.");
		return;
	}

	printf("\nRESERVAS DEL CLIENTE\n\n");
	for (int i = 0; i < *numReservas; ++i) {
		if (arrayReservas[i].cliente->id == idCliente)
		{
			printf("Hotel: %d, %s - Habitacion %d\n", arrayReservas[i].hotel->id, arrayReservas[i].hotel->nombre, arrayReservas[i].numHabitacion);
		}
	}
}
