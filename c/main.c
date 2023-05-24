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

	cargarTiposHabitaciones(db, stmt, tiposHabitacion, &numTipoHabs, f);
	cargarHoteles(db, stmt, hoteles, &idHotel, tiposHabitacion, f);
	cargarHabitacionesHoteles(db, stmt, tiposHabitacion, hoteles, idHotel, f);
	cargarClientes(db, stmt, clientes, &numClientes, f);
	cargarReservas(db, stmt, reservas, &numReservas, clientes, hoteles, f);
	cargarAdmins(db, stmt, admins, &numAdmins, f);
	cargarEmpleados(db, stmt, empleados, &numEmpleados, hoteles, f);

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
