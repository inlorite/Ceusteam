
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
		Hotel(int id, char* nombre, char* localizacion, int numHabTotales, int numHabActuales, Habitacion* habitaciones);
		virtual ~Hotel();
		Hotel(const Hotel &other);

		int getId();
		char* getNombre();
		char* getLocalizacion();
		int getNumHabTotales();
		int getNumHabActuales();
		Habitacion* getHabitaciones();
		int numHabOcupadas();

		void setNumHabActuales(int numHabActuales);

		void imprimirHotel();
		void visualizarHabitacionesHotel();
};

#endif /* OBJECTS_HOTEL_H_ */
