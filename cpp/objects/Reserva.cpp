/*
 * Reserva.cpp
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#include "Reserva.h"
#include "stdio.h"

Reserva::Reserva() {
	cliente = NULL;
	hotel = NULL;
	numHabitacion = 0;
}

Reserva::~Reserva() {

}

Reserva::Reserva(const Reserva &other) {
	cliente = other.cliente;
	hotel = other.hotel;
	numHabitacion = other.numHabitacion;
}

/////////////////// GETTERS ///////////////////////

Cliente* Reserva::getCliente()
{
	return this->cliente;
}

Hotel* Reserva::getHotel()
{
	return this->hotel;
}

int Reserva::getNumHabitacion()
{
	return this->numHabitacion;
}
