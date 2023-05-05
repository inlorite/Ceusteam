#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objects/hotel.h"
#include "objects/cliente.h"
#include "objects/empleado.h"
#include "objects/admin.h"
#include "data/sqlite3.h"
#include "data/sql.h"
#include <string.h>

int main(void)
{
	FILE* f;
	sqlite3 *db;
	sqlite3_stmt *stmt;

	f = fopen("../logs.txt", "a");
	fprintf(f, "\n-+- Nueva ejecucion del programa -+-\n");
	sqlite3_open("../hoteles.sqlite", &db);

	crearTablas(db, stmt, f);

	Hotel* hotel = malloc(sizeof(Hotel) * 50);
	Cliente* clientes = malloc(sizeof(Cliente) * 30);
	Empleado* empleados = malloc(sizeof(Empleado) * 20);
	TipoHab *tiposHabitacion = malloc(sizeof(TipoHab)*3);
	Reserva* reservas = malloc(sizeof(Reserva) * 50);
	Admin* admins = malloc(sizeof(Admin) * 10);

	tiposHabitacion[0].id=1;strcpy(tiposHabitacion[0].tipo,"Presidencial");tiposHabitacion[0].precio=300;
	tiposHabitacion[1].id=2;strcpy(tiposHabitacion[1].tipo,"Suite");tiposHabitacion[1].precio=150;
	tiposHabitacion[2].id=3;strcpy(tiposHabitacion[2].tipo,"Estandar");tiposHabitacion[2].precio=75;

	int idHotel = 0;
	int numClientes = 0;
	int numEmpleados = 0;
	int numReservas = 0;
	int numAdmins = 0;
	int iniciarSesion = 0;
	int seguir;
	seguir = 1;

	Admin a = {1, "test", "test"};
	admins[0] = a;
	numAdmins++;

	printf("\n ======================================\n "
		   "\tGESTION DE HOTELES\n "
		   "=========================================\n");

	char* usuario = malloc(sizeof(char) * 20);
	char* contrasena = malloc(sizeof(char) * 20);

	printf("Introduzca un usuario:\n");
	scanf("%s", usuario);
	printf("Introduzca la contrasena:\n");
	scanf("%s", contrasena);

	for (int i = 0; i < numAdmins; ++i) {
		if (strcmp(admins[i].nombre, usuario) == 0) {
			if (strcmp(admins[i].contrasena, contrasena) == 0) {
				iniciarSesion = 1;
				break;
			}
		}
	}

	if (iniciarSesion == 1) {
		while(seguir==1)
		{
			int seguir2 = 1;
			int opcion;
			printf("\n\n -------------------------------------------\n"
					"Introduzca la operacion que quiera realizar: \n"
					"1. Visualizacion de la informacion de los hoteles. \n"
					"2. Anadir nuevos hoteles. \n"
					"3. Modificar los hoteles ya existentes. \n"
					"4. Borrar los hoteles ya existentes.\n"
					"5. Reserva de habitaciones dentro de los hoteles.\n"
					"6. Gestion de clientes.\n"
					"7. Gestion de empleados.\n"
					"8. Salir\n\n");
			scanf ("%d", &opcion);

			switch (opcion)
			{
				case 1:
					visualizarHoteles(hotel, idHotel);
					break;

				case 2:
					hotel[idHotel]=*crearHotel(idHotel);
					idHotel++;

					break;

				case 3:
					if (idHotel == 0)
					{
						printf("\nActualmente no hay ningun hotel registrado.");
						break;
					}
					modificarHotel(hotel,idHotel,tiposHabitacion);
					break;

				case 4:
					eliminarHotel(hotel, &idHotel);
					break;

				case 5:
					printf("\n\n -------------------------------------------\n"
							"Introduzca la operacion que quiera realizar: \n"
							"1. Anadir reserva \n"
							"2. Borrar reserva \n"
							"3. Consultar reservas \n"
							"4. Salir\n\n");
					scanf ("%d", &opcion);
					switch (opcion)
					{
						case 1:
							anadirReserva(reservas, &numReservas, clientes, &numClientes, hotel, &idHotel);
							break;

						case 2:
							borrarReserva(reservas, &numReservas, clientes, &numClientes, hotel, &idHotel);
							break;

						case 3:
							consultarReserva(reservas, &numReservas, clientes, &numClientes);
							break;

						case 4:
							seguir2 = 0;
					}
					break;

				case 6:
					while(seguir2==1)
					{
						int opcion;
						printf("\n\n -------------------------------------------\n"
								"Introduzca la operacion que quiera realizar: \n"
								"1. Crear cliente \n"
								"2. Modificar cliente \n"
								"3. Borrar cliente \n"
								"4. Consultar cliente \n"
								"5. Salir\n\n");
						scanf ("%d", &opcion);
						switch (opcion)
						{
							case 1:
								crearCliente(clientes, &numClientes);
								break;

							case 2:
								modificarCliente(clientes, &numClientes);
								break;

							case 3:
								borrarCliente(clientes, &numClientes);
								break;

							case 4:
								consultarCliente(clientes, &numClientes);
								break;

							case 5:
								seguir2 = 0;
						}
					}
					break;

				case 7:
					while(seguir2==1)
					{
						int opcion;
						printf("\n\n -------------------------------------------\n"
								"Introduzca la operacion que quiera realizar: \n"
								"1. Crear empleado \n"
								"2. Modificar empleado \n"
								"3. Borrar empleado \n"
								"4. Consultar empleado \n"
								"5. Salir\n\n");
						scanf ("%d", &opcion);
						switch (opcion)
						{
							case 1:
								crearEmpleado(empleados, &numEmpleados, hotel, &idHotel);
								break;

							case 2:
								modificarEmpleado(empleados, &numEmpleados, hotel, &idHotel);
								break;

							case 3:
								borrarEmpleado(empleados, &numEmpleados);
								break;

							case 4:
								consultarPlantilla(empleados, &numEmpleados, hotel, &idHotel);
								break;

							case 5:
								seguir2 = 0;
						}
					}
					break;

				case 8:
					seguir=0;
			}
		}
	} else {
		printf("\nEl usuario o la contrasena son incorrectos.");
	}

	sqlite3_close(db);
	fclose(f);
}
