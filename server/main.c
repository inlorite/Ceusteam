// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <float.h>

#include "../c/objects/cliente.h"
#include "../c/objects/hotel.h"
#include "data/sqlite3.h"
#include "data/sql.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	FILE* f;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	f = fopen("../../c/logs.txt", "a");
	sqlite3_open("../../c/hoteles.sqlite", &db);

	Hotel* hoteles = malloc(sizeof(Hotel) * 50);
	Cliente* clientes = malloc(sizeof(Cliente) * 30);
	TipoHab* tiposHabitacion = malloc(sizeof(TipoHab)*3);
	Reserva* reservas = malloc(sizeof(Reserva) * 50);

	int idHotel = 0;
	int numClientes = 0;
	int numReservas = 0;
	int numTipoHabs = 0;

	cargarTiposHabitaciones(db, stmt, tiposHabitacion, &numTipoHabs, f);
	cargarHoteles(db, stmt, hoteles, &idHotel, tiposHabitacion, f);
	cargarHabitacionesHoteles(db, stmt, tiposHabitacion, hoteles, idHotel, f);
	cargarClientes(db, stmt, clientes, &numClientes, f);
	cargarReservas(db, stmt, reservas, &numReservas, clientes, hoteles, f);

	printf("numidhotel: %d\n", idHotel);
	printf("hotel: %d - %s\n", hoteles[0].id, hoteles[0].nombre);

	printf("numclientes: %d\n", numClientes);
	printf("cliente: %d - %s\n", clientes[0].id, clientes[0].nombre);

	printf("numreservas: %d\n", numReservas);
	printf("reserva0: %s - %s - %d\n", reservas[0].cliente->nombre, reservas[0].hotel->nombre, reservas[0].numHabitacion);

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[50], recvBuff[50];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	printf("Waiting for incoming commands from client... \n");
	do
	{
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

		printf("Command received: %s \n", recvBuff);


		// REGISTRAR CLIENTE
		if (strcmp(recvBuff, "REGISTRAR CLIENTE") == 0)
		{

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* nombre = malloc(sizeof(recvBuff)+1);
			strcpy(nombre, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* email = malloc(sizeof(recvBuff)+1);
			strcpy(email, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numTelf = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* contrasena = malloc(sizeof(recvBuff)+1);
			strcpy(contrasena, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int id = atoi(recvBuff);

			// GUARDAR CLIENTE EN LA BD
			insertarCliente(db, stmt, id, nombre, email, numTelf, contrasena, f);
		}


		// ANADIR RESERVA
		if (strcmp(recvBuff, "ANADIR RESERVA") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idCliente = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idHotel = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numHabitacion = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int ocupantes = atoi(recvBuff);
			printf("NUMERO OCUPANTES QUE ESTAMOS MIRANDO AHORA: %d", ocupantes);

			// ANADIR LA RESERVA EN LA BD
			insertarReserva(db, stmt, idCliente, idHotel, numHabitacion, f);

			// ACTUALIZAR HABITACION
			updateHabitacion(db, stmt, idHotel, numHabitacion, ocupantes, f);

			// ACTUALIZAR HOTEL
			//updateHotel(db, stmt, idHotel, hoteles[idHotel-1].numHabActuales, 1, f); // Incrementamos el atributo numHabActuales
		}


		// ELIMINAR RESERVA
		if (strcmp(recvBuff, "ELIMINAR RESERVA") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idCliente = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idHotel = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numHabitacion = atoi(recvBuff);

			// ELIMINAR LA RESERVA DE LA BD
			eliminarReserva(db, stmt, idCliente, idHotel, numHabitacion, f);

			// ACTUALIZAR HABITACION
			updateHabitacion(db, stmt, idHotel, numHabitacion, 0, f);

			// ACTUALIZAR HOTEL
			//updateHotel(db, stmt, idHotel, hoteles[idHotel-1].numHabActuales, -1, f); // Decrementamos el atributo numHabActuales
		}

		// CARGAR DATOS
		if (strcmp(recvBuff, "CARGAR DATOS") == 0)
		{

			// Enviar tipos habitaciones
			sprintf(sendBuff, "%d", numTipoHabs);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numTipoHabs; ++i) {
				sprintf(sendBuff, "%d", tiposHabitacion[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, tiposHabitacion[i].tipo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%f", tiposHabitacion[i].precio);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}

			printf("entrando en cargar datos\n");

			// Enviar hoteles
			sprintf(sendBuff, "%d", idHotel);
			printf("idhotel: %d\n", idHotel);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < idHotel; ++i) {
				sprintf(sendBuff, "%d", hoteles[i].id);
				printf("id: %d\n", hoteles[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].nombre);
				printf("nombre: %s\n", hoteles[i].nombre);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].localizacion);
				printf("localizacion: %s\n", hoteles[i].localizacion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%d", hoteles[i].numHabTotales);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%d", hoteles[i].numHabActuales);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				for (int j = 0; j < hoteles[i].numHabTotales; ++j) {
					sprintf(sendBuff, "%d", hoteles[i].habitaciones[j].num_habitacion);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);

					sprintf(sendBuff, "%d", hoteles[i].habitaciones[j].tipoHab.id);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);

					sprintf(sendBuff, "%d", hoteles[i].habitaciones[j].ocupantes);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}
			}

			// Enviar clientes
			sprintf(sendBuff, "%d", numClientes);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numClientes; ++i) {
				sprintf(sendBuff, "%d", clientes[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].nombre);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].email);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%d", clientes[i].numTelf);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}

			// Enviar reservas
			sprintf(sendBuff, "%d", numReservas);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numReservas; ++i) {
				sprintf(sendBuff, "%d", reservas[i].cliente->id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%d", reservas[i].hotel->id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%d", reservas[i].numHabitacion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}

			printf("carga datos acabada\n");
		}


		// SALIR
		if (strcmp(recvBuff, "EXIT") == 0)
			break;

	} while (1);

	/*
	borrarTablas(db, stmt, f);
	crearTablas(db, stmt, f);

	guardarDatos(db, stmt, hoteles, idHotel, tiposHabitacion, numTipoHabs, clientes, numClientes, reservas, numReservas, f);
	*/

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

