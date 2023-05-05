#include "hotel.h"

#ifndef OBJECTS_CLIENTE_H_
#define OBJECTS_CLIENTE_H_

/* ------------------
 * ESTRUCTURAS
 * ------------------
*/

typedef struct
{
	int id;
	char nombre[20];
	char email[20];
	int numTelf;
	char contrasena[20];
} Cliente;

typedef struct
{
	Cliente* cliente;
	Hotel* hotel;
	int numHabitacion;
} Reserva;

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioCliente(Cliente* c, int numClientes);

void escribirBinarioCliente(Cliente* c, int numClientes);

void leerBinarioReserva(Reserva* r, int numReserva, Cliente* c, Hotel* h);

void escribirBinarioReserva(Reserva* r, int numReserva);

/* ------------------
 * FUNCIONES
 * ------------------
*/

void imprimirCliente(Cliente c);

void crearCliente(Cliente* arrayClientes, int* numClientes);

void modificarCliente(Cliente* arrayClientes, int* numClientes);

void borrarCliente(Cliente* arrayClientes, int* numClientes);

void consultarCliente(Cliente* arrayClientes, int* numClientes);

void anadirReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes, Hotel* h, int* numHoteles);

void borrarReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes, Hotel* h, int* numHoteles);

void consultarReserva(Reserva* arrayReservas, int* numReservas, Cliente* c, int* numClientes);

#endif
