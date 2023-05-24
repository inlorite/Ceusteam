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

	Admin a = {1, "admin", "admin"};
	admins[0] = a;
	numAdmins++;

	Cliente c = {1, "Pedro", "pedro@gmail.com", 688445673, "pedro123"};
	clientes[0] = c;
	numClientes++;

	Habitacion* habitaciones = malloc(sizeof(Habitacion) * 30);
	int numHabitaciones = 0;

	Habitacion hab1 = {1, tiposHabitacion[0], 0};
	habitaciones[0] = hab1;
	numHabitaciones++;
	Habitacion hab2 = {2, tiposHabitacion[1], 0};
	habitaciones[1] = hab2;
	numHabitaciones++;
	Habitacion hab3 = {3, tiposHabitacion[2], 0};
	habitaciones[2] = hab3;
	numHabitaciones++;
	Habitacion hab4 = {4, tiposHabitacion[0], 0};
	habitaciones[3] = hab4;
	numHabitaciones++;
	Habitacion hab5 = {5, tiposHabitacion[1], 0};
	habitaciones[4] = hab5;
	numHabitaciones++;
	Habitacion hab6 = {6, tiposHabitacion[2], 0};
	habitaciones[5] = hab6;
	numHabitaciones++;
	Habitacion hab7 = {7, tiposHabitacion[0], 0};
	habitaciones[6] = hab7;
	numHabitaciones++;
	Habitacion hab8 = {8, tiposHabitacion[1], 0};
	habitaciones[7] = hab8;
	numHabitaciones++;
	Habitacion hab9 = {9, tiposHabitacion[2], 0};
	habitaciones[8] = hab9;
	numHabitaciones++;
	Habitacion hab10 = {10, tiposHabitacion[0], 0};
	habitaciones[9] = hab10;
	numHabitaciones++;
	Habitacion hab11 = {11, tiposHabitacion[1], 0};
	habitaciones[10] = hab11;
	numHabitaciones++;
	Habitacion hab12 = {12, tiposHabitacion[2], 0};
	habitaciones[11] = hab12;
	numHabitaciones++;
	Habitacion hab13 = {13, tiposHabitacion[0], 0};
	habitaciones[12] = hab13;
	numHabitaciones++;
	Habitacion hab14 = {14, tiposHabitacion[1], 0};
	habitaciones[13] = hab14;
	numHabitaciones++;
	Habitacion hab15 = {15, tiposHabitacion[2], 0};
	habitaciones[14] = hab15;
	numHabitaciones++;
	Habitacion hab16 = {16, tiposHabitacion[0], 0};
	habitaciones[15] = hab16;
	numHabitaciones++;
	Habitacion hab17 = {17, tiposHabitacion[1], 0};
	habitaciones[16] = hab17;
	numHabitaciones++;
	Habitacion hab18 = {18, tiposHabitacion[2], 0};
	habitaciones[17] = hab18;
	numHabitaciones++;
	Habitacion hab19 = {19, tiposHabitacion[0], 0};
	habitaciones[18] = hab19;
	numHabitaciones++;
	Habitacion hab20 = {20, tiposHabitacion[1], 0};
	habitaciones[19] = hab20;
	numHabitaciones++;
	Habitacion hab21 = {21, tiposHabitacion[2], 0};
	habitaciones[20] = hab21;
	numHabitaciones++;
	Habitacion hab22 = {22, tiposHabitacion[0], 0};
	habitaciones[21] = hab22;
	numHabitaciones++;
	Habitacion hab23 = {23, tiposHabitacion[1], 0};
	habitaciones[22] = hab23;
	numHabitaciones++;
	Habitacion hab24 = {24, tiposHabitacion[2], 0};
	habitaciones[23] = hab24;
	numHabitaciones++;
	Habitacion hab25 = {25, tiposHabitacion[0], 0};
	habitaciones[24] = hab25;
	numHabitaciones++;
	Habitacion hab26 = {26, tiposHabitacion[1], 0};
	habitaciones[25] = hab26;
	numHabitaciones++;
	Habitacion hab27 = {27, tiposHabitacion[2], 0};
	habitaciones[26] = hab27;
	numHabitaciones++;
	Habitacion hab28 = {28, tiposHabitacion[0], 0};
	habitaciones[27] = hab28;
	numHabitaciones++;
	Habitacion hab29 = {29, tiposHabitacion[1], 0};
	habitaciones[28] = hab29;
	numHabitaciones++;
	Habitacion hab30 = {30, tiposHabitacion[2], 0};
	habitaciones[29] = hab30;
	numHabitaciones++;

	Hotel h1 = {1, "NH Bilbao", "Bilbao", 70, 30, habitaciones};
	hoteles[0] = h1;
	idHotel++;
	Hotel h2 = {2, "Melia Bilbao", "Bilbao", 100, 30, habitaciones};
	hoteles[1] = h2;
	idHotel++;
	Hotel h3 = {3, "Hotel Palace", "Madrid", 200, 30, habitaciones};
	hoteles[2] = h3;
	idHotel++;
	Hotel h4 = {4, "Hotel Ritz", "Madrid", 30, 30, habitaciones};
	hoteles[3] = h4;
	idHotel++;
	Hotel h5 = {5, "NH Barcelona", "Barcelona", 70, 30, habitaciones};
	hoteles[4] = h5;
	idHotel++;
	Hotel h6 = {6, "Melia Barcelona", "Barcelona", 100, 30, habitaciones};
	hoteles[5] = h6;
	idHotel++;
	Hotel h7 = {7, "Hotel Inglaterra", "Sevilla", 65, 30, habitaciones};
	hoteles[6] = h7;
	idHotel++;
	Hotel h8 = {8, "Hotel Alfonso XII", "Sevilla", 120, 30, habitaciones};
	hoteles[7] = h8;
	idHotel++;
	Hotel h9 = {9, "Hotel Marbella club", "Marbella", 50, 30, habitaciones};
	hoteles[8] = h9;
	idHotel++;
	Hotel h10 = {10, "Hotel Formentor", "Mallorca", 85, 30, habitaciones};
	hoteles[9] = h10;
	idHotel++;
	Hotel h11 = {11, "Eurostars Hotel", "Santander", 30, 30, habitaciones};
	hoteles[10] = h11;
	idHotel++;
	Hotel h12 = {12, "Hotel Maria Cristina", "SanSebastian", 130, 30, habitaciones};
	hoteles[11] = h12;
	idHotel++;


	Empleado e = {1, "Fran", &hoteles[0]};
	empleados[0] = e;
	numEmpleados++;
	Empleado e1 = {2, "Pepe", &hoteles[1]};
	empleados[1] = e1;
	numEmpleados++;



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
