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
	int seguir3 = 1;
	int iniciarSesion = 0;

	/* CARGA DE DATOS DESDE LA BD */

	int numHoteles = 0;
	int numClientes = 0;
	int numReservas = 0;
	int contadorReservas =0;
	int reservaSeleccionada;

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
	Habitacion habitacion2(2,&tipo1,0);
	habitaciones[0]=habitacion1;
	habitaciones[1]=habitacion2;
	Hotel hotel(1,"hotel1","malaga",2,0,habitaciones);
	hoteles[0]=hotel;
	numHoteles++;
	clientes[0] = c;
	numClientes++;



	while (seguir == 1)
	{
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
					cout << "\nIntroduzca un usuario:\n";
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

					if (iniciarSesion == 0)
						cout << "\nDatos erroneos." << endl;
				}
				seguir = 0;
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
				seguir = 0;
				break;
		}

		cout << "Input incorrecto." << endl;
	}

	seguir = 1;


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
								cout << "\n--- HABITACIONES DE " << hoteles[hotelSeleccionado-1].getNombre() << " ---" << endl;
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
										int numHabitacionReserva;

										for (int i = 0; i < hoteles[hotelSeleccionado-1].getNumHabTotales(); ++i) {
											if (hoteles[hotelSeleccionado-1].getHabitaciones()[i].estaLibre())
											{
												numHabitacionReserva = hoteles[hotelSeleccionado-1].getHabitaciones()[i].getNumHabitacion();
												break;
											}
										}

										Reserva* nuevaReserva = new Reserva(clientes->encontrarCliente(clientes, numClientes, usuario), &hoteles[hotelSeleccionado-1], numHabitacionReserva);

										reservas[numReservas] = *nuevaReserva;

										numReservas++;

										hoteles[hotelSeleccionado-1].getHabitaciones()[numHabitacionReserva-1].setOcupantes(ocupantes);

										cout<<"Num ocupantes: "<<hoteles[hotelSeleccionado-1].getHabitaciones()[0].getOcupantes();
										cout<<"Num ocupantes: "<<habitaciones[1].getOcupantes();

										hoteles[hotelSeleccionado-1].setNumHabActuales(hoteles[hotelSeleccionado-1].getNumHabActuales()+1);

										cout << "\nHabitacion numero " << numHabitacionReserva << " reservada con exito.\n" << endl;


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
						cout<<i+1<<". ";
						reservas[i].imprimirReserva();
					}
				}
				if(contadorReservas==0){
					cout<<"\nNo se han encontrado reservas a su nombre\n"<<endl;
				}


				seguir3 = 1;
				while (seguir3){
					cout << "\n\nIntroduzca la operacion que quiera realizar: \n"
						 "1. Eliminar reserva.\n"
						 "2. Salir.\n\n";

						scanf("%d", &opcion);

						switch (opcion)
						{
							case 1:

								cout<<"Selecciona el numero de reserva: ";
								scanf("%d", &reservaSeleccionada);
								hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getHabitaciones()[reservas[reservaSeleccionada-1].getNumHabitacion()-1].setOcupantes(0);
								hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].setNumHabActuales(hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getNumHabActuales()-1);
								cout<<"Num ocupantes: "<<hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getHabitaciones()[reservas[reservaSeleccionada-1].getNumHabitacion()-1].getOcupantes()<<endl;
								reservas[reservaSeleccionada-1].eliminarReserva();

								for (int i = reservaSeleccionada-1; i < numReservas-1; i++) {
									reservas[i]=reservas[i+1];
								}
								numReservas--;
								break;

							case 2:
								seguir3 = 0;



						}
					}
					break;

			case 3:
				seguir = 0;

		}
	}

	return 0;
}

