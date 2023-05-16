#include <iostream>
#include "objects/Hotel.h"
#include "objects/Cliente.h"
#include "objects/Empleado.h"
#include "objects/Reserva.h"

using namespace std;

int main(void) {
	cout << "Programa hecho en cpp" << endl;

	cout << "\n ======================================\n "
			   "\t RESERVA DE HOTELES\n "
			   "======================================\n" << endl;

	int seguir = 1;

	/* CARGA DE DATOS DESDE LA BD */

	int numHoteles = 0;
	int numClientes = 0;
	int numReservas = 0;

	Hotel* hotel = new Hotel[50];
	Cliente* clientes = new Cliente[30];
	TipoHab *tiposHabitacion = new TipoHab[3];
	Reserva* reservas = new Reserva[50];

	while (seguir)
	{
		cout << "\n\n -------------------------------------------\n"
				"Introduzca la operacion que quiera realizar: \n"
				"1. Visualizacion de la informacion de los hoteles. \n"
				"2. Reserva de habitaciones dentro de los hoteles.\n"
				"3. Salir\n\n";

		int opcion;
		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				cout << "\n----------- HOTELES -----------\n" << endl;

				for (int i = 0; i < numHoteles; ++i) {
					hotel[i].imprimirHotel();
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
