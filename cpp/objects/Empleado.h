
#ifndef OBJECTS_EMPLEADO_H_
#define OBJECTS_EMPLEADO_H_

#include "hotel.h"

class Empleado {
	private:
		int id;
		char* nombre;
		Hotel* hotel;

	public:
		Empleado();
		Empleado(int id, char* nombre, Hotel* hotel);
		virtual ~Empleado();
		Empleado(const Empleado &other);

		int getId();
		char* getNombre();
		Hotel* getHotel();
};

#endif /* OBJECTS_EMPLEADO_H_ */
