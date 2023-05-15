
#ifndef OBJECTS_HOTEL_H_
#define OBJECTS_HOTEL_H_

#include "Habitacion.h"

class Hotel {
	private:
		int id;
		char* nombre;
		char* localizacion;
		int numHabTotales;
		int numHabActuales;
		Habitacion* habitaciones;

	public:
		Hotel();
		virtual ~Hotel();
		Hotel(const Hotel &other);

		int getId();
		char* getNombre();
		char* getLocalizacion();
		int getNumHabTotales();
		int getNumHabActuales();
		Habitacion* getHabitaciones();
};

#endif /* OBJECTS_HOTEL_H_ */
