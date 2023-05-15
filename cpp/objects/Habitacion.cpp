
#include "Habitacion.h"
#include "stdio.h"

Habitacion::Habitacion() {
	num_habitacion = 0;
	tipoHab = NULL;
	ocupantes = 0;
}

Habitacion::Habitacion(int num_habitacion, TipoHab* tipoHab, int ocupantes) {
	this->num_habitacion = num_habitacion;
	this->tipoHab = tipoHab;
	this->ocupantes = ocupantes;
}

Habitacion::~Habitacion() {

}

Habitacion::Habitacion(const Habitacion &other) {
	num_habitacion = other.num_habitacion;
	tipoHab = other.tipoHab;
	ocupantes = other.ocupantes;
}

/////////////////// GETTERS ///////////////////////

int Habitacion::getNumHabitacion()
{
	return this->num_habitacion;
}

TipoHab* Habitacion::getTipoHab()
{
	return this->tipoHab;
}

int Habitacion::getOcupantes()
{
	return this->ocupantes;
}
