
#ifndef OBJECTS_RESERVA_H_
#define OBJECTS_RESERVA_H_

#include "cliente.h"
#include "hotel.h"

class Reserva {
	private:
		Cliente* cliente;
		Hotel* hotel;
		int numHabitacion;

	public:
		Reserva();
		Reserva(Cliente* cliente, Hotel* hotel, int numHabitacion);
		virtual ~Reserva();
		Reserva(const Reserva &other);

		Cliente* getCliente();
		Hotel* getHotel();
		int getNumHabitacion();
};

#endif /* OBJECTS_RESERVA_H_ */
