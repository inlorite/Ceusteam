
#ifndef OBJECTS_HABITACION_H_
#define OBJECTS_HABITACION_H_

#include "TipoHab.h"

class Habitacion {
	private:
		int num_habitacion;
	    TipoHab* tipoHab;
	    int ocupantes;

	public:
		Habitacion();
		Habitacion(int num_habitacion, TipoHab* tipoHab, int ocupantes);
		virtual ~Habitacion();
		Habitacion(const Habitacion &other);

		int getNumHabitacion();
		TipoHab* getTipoHab();
		int getOcupantes();

		void setOcupantes(int ocupantes);

		void imprimirHabitacion();
		int estaLibre();
};

#endif /* OBJECTS_HABITACION_H_ */
