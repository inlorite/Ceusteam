#include <stdlib.h>
#include <stdio.h>
#include "../../c/data/sql.h"
#include "../objects/Cliente.h"
#include "../objects/Empleado.h"
#include "../objects/Habitacion.h"
#include "../objects/Hotel.h"
#include "../objects/Reserva.h"
#include "../objects/TipoHab.h"

#ifndef DATA_GESTORBD_H_
#define DATA_GESTORBD_H_

class GestorBD {
	private:
		sqlite3* db;
		sqlite3_stmt* stmt;
		FILE* f;
	public:
		GestorBD(FILE* f);
		virtual ~GestorBD();

		void cargarTiposHabitaciones(TipoHab* tiposHabitaciones, int* numTiposHabitaciones);
		/*
		void cargarHoteles(Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones);
		void cargarHabitacionesHoteles(TipoHab* tiposHabitaciones, Hotel* hoteles, int numHoteles);
		void cargarClientes(Cliente* clientes, int* numClientes);
		void cargarReservas(Reserva* reservas, int* numReservas, Cliente* clientes, Hotel* hoteles);

		void insertarCliente(int id, char* nombre, char* email, int numTelf, char* contrasena);
		void insertarReserva(int idCliente, int idHotel, int numHabitacion);
		void eliminarReserva(int idCliente, int idHotel, int numHabitacion);
		void updateHabitacion(int idHotel, int numHabitacion, int ocupantes);
		void updateHotel(int idHotel, bool incNumHabActuales);
		*/
};

#endif
