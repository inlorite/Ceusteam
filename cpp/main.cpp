#include <iostream>
#include "string.h"
#include "objects/Hotel.h"
#include "objects/Cliente.h"
#include "objects/Empleado.h"
#include "objects/Reserva.h"

extern "C" {
	#include "../c/data/sql.h"
}

using namespace std;

int main(void) {
	cout << "Programa hecho en cpp" << endl;

	FILE* f;
	sqlite3 *db;
	sqlite3_stmt *stmt;

	sqlite3_open("../hoteles.sqlite", &db);

	crearTablas(db, stmt, f);

	cout << "\n ======================================\n "
			   "\t RESERVA DE HOTELES\n "
			   "======================================\n" << endl;


	int seguir = 1;
	int iniciarSesion = 0;

	/* CARGA DE DATOS DESDE LA BD */

	int numHoteles = 0;
	int numClientes = 0;
	int numReservas = 0;

	Hotel* hoteles = new Hotel[50];
	Cliente* clientes = new Cliente[30];
	TipoHab *tiposHabitacion = new TipoHab[3];
	Reserva* reservas = new Reserva[50];

	char* usuario = new char[20];
	char* contrasena = new char[20];

	Cliente c(1, "test", "test@gmail.com", 111111111, "test");
	clientes[0] = c;
	numClientes++;

	while (iniciarSesion == 0)
	{
		cout << "Introduzca un usuario:\n";
		scanf("%s", usuario);
		cout << "Introduzca la contrasena:\n";
		scanf("%s", contrasena);

		for (int i = 0; i < numClientes; ++i) {
			if (strcmp(clientes[i].getNombre(), usuario) == 0) {
				if (strcmp(clientes[i].getContrasena(), contrasena) == 0) {
					iniciarSesion = 1;
					break;
				}
			}
		}
	}


	while (seguir)
	{
		cout << "\n\n -------------------------------------------\n"
				"Introduzca la operacion que quiera realizar: \n"
				"1. Visualizar la informacion de los hoteles.\n"
				"2. Ver tus reservas.\n"
				"3. Salir.\n\n";

		int opcion;
		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				cout << "\n----------- HOTELES -----------\n" << endl;

				for (int i = 0; i < numHoteles; ++i) {
					hoteles[i].imprimirHotel();
				}

				int hotelSeleccionado;
				cout << "\nIntroduzca el ID del hotel que quiera ver: ";
				scanf("%d", &hotelSeleccionado);

				if (hotelSeleccionado < numHoteles)
				{
					int seguir2 = 1;

					while (seguir2)
					{
						cout << "\n\nIntroduzca la operacion que quiera realizar: \n"
								"1. Ver habitaciones.\n"
								"2. Reservar una habitacion.\n"
								"3. Salir.\n\n";

						scanf("%d", &opcion);

						switch (hotelSeleccionado)
						{
							case 1:
								hoteles[hotelSeleccionado-1].visualizarHabitacionesHotel();
								break;

							case 2:
								// Reservar
								int habSeleccionada;
								cout << "\nIntroduzca el número de habitacion que quiera reservar: ";
								scanf("%d", &habSeleccionada);

								if (habSeleccionada < hoteles[hotelSeleccionado-1].getNumHabTotales())
								{
									if (hoteles[hotelSeleccionado-1].getHabitaciones()[habSeleccionada].estaLibre())
									{
										cout << "\nIntroduzca el número de ocupantes (max 5): ";
										int ocupantes;
										scanf("%d", &ocupantes);

										if (ocupantes < 6 && ocupantes > 0)
										{
											// Realizar reserva
										}
									}
								}
								else
								{
									cout << "\nLa habitacion seleccionada esta ocupada o no existe" << endl;
								}

								break;

							case 3:
								seguir2 = 0;
								break;
						}
					}
				}
				else
				{
					cout << "\nEl hotel con ID " << opcion << " no existe.";
				}

				break;

			case 2:
				//
				break;

			case 3:
				seguir = 0;

		}
	}

	return 0;
}
