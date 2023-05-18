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

	//sqlite3_open("../c/hoteles.sqlite", &db);

	//crearTablas(db, stmt, f);

	cout << "\n ======================================\n "
			   "\t RESERVA DE HOTELES\n "
			   "======================================\n" << endl;


	int seguir = 1;
	int iniciarSesion = 0;

	/* CARGA DE DATOS DESDE LA BD */

	int numHoteles = 0;
	int numClientes = 0;
	int numReservas = 0;
	int contadorReservas =0;

	Hotel* hoteles = new Hotel[50];
	Cliente* clientes = new Cliente[30];
	TipoHab *tiposHabitacion = new TipoHab[3];
	Reserva* reservas = new Reserva[50];

	char* usuario = new char[20];
	char* contrasena = new char[20];
	int telf = 0;
	char* email = new char[50];

	TipoHab tipo1(1,"Presencial",200);
	tiposHabitacion[0]=tipo1;
	Cliente c(1, "test", "test@gmail.com", 111111111, "test");
	Habitacion *habitaciones = new Habitacion[2];
	Habitacion habitacion1(1,&tipo1,0);
	habitaciones[0]=habitacion1;
	Hotel hotel(1,"hotel1","malaga",1,0,habitaciones);
	hoteles[0]=hotel;
	numHoteles++;
	clientes[0] = c;
	numClientes++;

	cout << "\n\n -------------------------------------------\n"
					"Introduzca la operacion que quiera realizar: \n"
					"1. Iniciar sesion.\n"
					"2. Registrar cliente.\n"
					"3. Salir.\n\n";

			int opcion;
			scanf("%d", &opcion);

			switch (opcion)
			{
				case 1:
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
					break;
				case 2:
					Cliente registrarCliente;
					cout << "Introduzca un usuario:\n";
					scanf("%s", usuario);
					registrarCliente.setNombre(usuario);
					cout << "Introduzca un email:\n";
					scanf("%s", email);
					registrarCliente.setEmail(email);
					cout << "Introduzca el numero de telefono:\n";
					scanf("%d", &telf);
					registrarCliente.setTelf(telf);
					cout << "Introduzca la contrasena:\n";
					scanf("%s", contrasena);
					registrarCliente.setContrasena(contrasena);
					clientes[numClientes] = registrarCliente;
					numClientes++;
					break;
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

				if (hotelSeleccionado <= numHoteles)
				{
					int seguir2 = 1;

					while (seguir2)
					{
						cout << "\n\nIntroduzca la operacion que quiera realizar: \n"
								"1. Ver habitaciones.\n"
								"2. Reservar una habitacion.\n"
								"3. Salir.\n\n";

						scanf("%d", &opcion);

						switch (opcion)
						{
							case 1:
								hoteles[hotelSeleccionado-1].visualizarHabitacionesHotel();
								break;

							case 2:
								// Reservar

								if (hoteles[hotelSeleccionado-1].getNumHabActuales() < hoteles[hotelSeleccionado-1].getNumHabTotales())
								{
									cout << "\nIntroduzca el numero de ocupantes (max 5): ";
									int ocupantes;
									scanf("%d", &ocupantes);

									if (ocupantes < 6 && ocupantes > 0)
									{
										// Realizar reserva
										Reserva* nuevaReserva = new Reserva(clientes->encontrarCliente(clientes, numClientes, usuario), &hoteles[hotelSeleccionado-1], hoteles[hotelSeleccionado-1].getHabitaciones()[hoteles[hotelSeleccionado-1].getNumHabActuales()].getNumHabitacion());

										reservas[numReservas] = *nuevaReserva;

										numReservas++;

										hoteles[hotelSeleccionado-1].setNumHabActuales(hoteles[hotelSeleccionado-1].getNumHabActuales()+1);

										cout << "\nHabitacion numero " << hoteles[hotelSeleccionado-1].getNumHabActuales() << " reservada con exito.\n" << endl;;


									}
									else
									{
										cout << "\nNumero de ocupantes incorrecto." << endl;
									}
								}
								else
								{
									cout << "\nEl hotel seleccionado esta completamente ocupado" << endl;
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
				// Ver tus reservas

				//Reserva* pruebaReserva = new Reserva(&c,&hoteles[0],1);
				//reservas[numReservas]= *pruebaReserva;

				contadorReservas = 0;
				for (int i = 0;i < numReservas; i++) {
					if (strcmp(reservas[i].getCliente()->getNombre(), usuario) == 0) {
						contadorReservas++;
						reservas[i].imprimirReserva();
					}
				}
				if(contadorReservas==0){
					cout<<"\nNo se han encontrado reservas a su nombre\n"<<endl;
				}
				break;

			case 3:
				seguir = 0;

		}
	}

	return 0;
}

