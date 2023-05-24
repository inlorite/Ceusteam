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
	//////////// PROGRAMA PRINCIPAL ////////////

	FILE* f;
	sqlite3 *db;
	sqlite3_stmt *stmt;

	f = fopen("../logs.txt", "a");
	fprintf(f, "\n-+- Nueva ejecucion del programa -+-\n");
	sqlite3_open("../hoteles.sqlite", &db);

	/*
	borrarTablas(db, stmt, f);
	borrarTablasAdmin(db, stmt, f);
	crearTablas(db, stmt, f);
	crearTablasAdmin(db, stmt, f);
	*/

	Hotel* hoteles = malloc(sizeof(Hotel) * 50);
	Cliente* clientes = malloc(sizeof(Cliente) * 30);
	Empleado* empleados = malloc(sizeof(Empleado) * 20);
	TipoHab* tiposHabitacion = malloc(sizeof(TipoHab)*3);
	Reserva* reservas = malloc(sizeof(Reserva) * 50);
	Admin* admins = malloc(sizeof(Admin) * 10);

	int idHotel = 0;
	int numClientes = 0;
	int numEmpleados = 0;
	int numReservas = 0;
	int numAdmins = 0;
	int numTipoHabs = 0;
	int iniciarSesion = 0;
	int seguir;
	seguir = 1;

	/*
	TipoHab th1 = {1, "Presidencial", 300};
	tiposHabitacion[0] = th1;
	numTipoHabs++;
	TipoHab th2 = {2, "Suite", 150};
	tiposHabitacion[1] = th2;
	numTipoHabs++;
	TipoHab th3 = {3, "Estandar", 75};
	tiposHabitacion[2] = th3;
	numTipoHabs++;

	Admin a = {1, "test", "test"};
	admins[0] = a;
	numAdmins++;

	Cliente c = {1, "testcliente", "testcliente@gmail.com", 123456789, "contra123"};
	clientes[0] = c;
	numClientes++;

	Habitacion* habitaciones = malloc(sizeof(Habitacion) * 2);
	int numHabitaciones = 0;

	Habitacion hab1 = {1, tiposHabitacion[0], 2};
	habitaciones[0] = hab1;
	numHabitaciones++;
	Habitacion hab2 = {2, tiposHabitacion[1], 0};
	habitaciones[1] = hab2;
	numHabitaciones++;

	Hotel h = {1, "hotel1", "bilbao", 10, 2, habitaciones};
	hoteles[0] = h;
	idHotel++;

	Habitacion* habitaciones2 = malloc(sizeof(Habitacion) * 4);
	habitaciones2[0] = hab1;
	habitaciones2[1] = hab2;

	Habitacion hab3 = {3, tiposHabitacion[2], 0};
	habitaciones2[2] = hab3;
	Habitacion hab4 = {4, tiposHabitacion[1], 0};
	habitaciones2[3] = hab4;

	Hotel h2 = {2, "hotel2", "madrid", 8, 4, habitaciones2};
	hoteles[1] = h2;
	idHotel++;

	Empleado e = {1, "fran", &hoteles[0]};
	empleados[0] = e;
	numEmpleados++;

	Reserva r = {&clientes[0], &hoteles[0], 1};
	reservas[0] = r;
	numReservas++;

	Reserva r2 = {&clientes[0], &hoteles[1], 1};
	reservas[1] = r2;
	numReservas++;

	guardarDatos(db, stmt, hoteles, idHotel, tiposHabitacion, numTipoHabs, clientes, numClientes, reservas, numReservas, f);
	guardarDatosAdmin(db, stmt, empleados, numEmpleados, admins, numAdmins, f);
	*/

	cargarTiposHabitaciones(db, stmt, tiposHabitacion, &numTipoHabs, f);
	cargarHoteles(db, stmt, hoteles, &idHotel, tiposHabitacion, f);
	cargarHabitacionesHoteles(db, stmt, tiposHabitacion, hoteles, idHotel, f);
	cargarClientes(db, stmt, clientes, &numClientes, f);
	cargarReservas(db, stmt, reservas, &numReservas, clientes, hoteles, f);
	cargarAdmins(db, stmt, admins, &numAdmins, f);
	cargarEmpleados(db, stmt, empleados, &numEmpleados, hoteles, f);

	printf("%d\n", numAdmins);
	printf("admin: %s - %s\n", admins[0].nombre, admins[0].contrasena);

	printf("%d\n", idHotel);
	printf("hotel: %d - %s\n", hoteles[0].id, hoteles[0].nombre);

	printf("%d\n", numEmpleados);
	printf("empleado: %d - %s\n", empleados[0].hotel->id, empleados[0].nombre);

	printf("\n ======================================\n "
		   "\tGESTION DE HOTELES\n "
		   "=========================================\n");

	char* usuario = malloc(sizeof(char) * 50);
	char* contrasena = malloc(sizeof(char) * 50);

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
					visualizarHoteles(hoteles, idHotel);
					break;

				case 2:
					hoteles[idHotel]=*crearHotel(idHotel);
					idHotel++;

					break;

				case 3:
					if (idHotel == 0)
					{
						printf("\nActualmente no hay ningun hotel registrado.");
						break;
					}
					modificarHotel(hoteles,idHotel,tiposHabitacion);
					break;

				case 4:
					eliminarHotel(hoteles, &idHotel);
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
							anadirReserva(reservas, &numReservas, clientes, &numClientes, hoteles, &idHotel);
							break;

						case 2:
							borrarReserva(reservas, &numReservas, clientes, &numClientes, hoteles, &idHotel);
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
								crearEmpleado(empleados, &numEmpleados, hoteles, &idHotel);
								break;

							case 2:
								modificarEmpleado(empleados, &numEmpleados, hoteles, &idHotel);
								break;

							case 3:
								borrarEmpleado(empleados, &numEmpleados);
								break;

							case 4:
								consultarPlantilla(empleados, &numEmpleados, hoteles, &idHotel);
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

	borrarTablas(db, stmt, f);
	borrarTablasAdmin(db, stmt, f);
	crearTablas(db, stmt, f);
	crearTablasAdmin(db, stmt, f);

	guardarDatos(db, stmt, hoteles, idHotel, tiposHabitacion, numTipoHabs, clientes, numClientes, reservas, numReservas, f);
	guardarDatosAdmin(db, stmt, empleados, numEmpleados, admins, numAdmins, f);

	sqlite3_close(db);
	fclose(f);
}
