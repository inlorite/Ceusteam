/*
 * Habitacion.cpp
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#include "Habitacion.h"

Habitacion::Habitacion() {
	num_habitacion = 0;
	TipoHab t = TipoHab();
	tipoHab = t;
	ocupantes = 0;
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

TipoHab Habitacion::getTipoHab()
{
	return this->tipoHab;
}

int Habitacion::getOcupantes()
{
	return this->ocupantes;
}
