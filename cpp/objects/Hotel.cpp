

#include "Hotel.h"

Hotel::Hotel() {
	id = 0;
	nombre = new char[10];
	localizacion = new char[10];
	numHabTotales = 10;
	numHabActuales = 10;
	habitaciones = new Habitacion[10];
}

Hotel::~Hotel() {
	delete [] nombre;
	delete [] localizacion;
	delete [] habitaciones;
}

Hotel::Hotel(const Hotel &other) {
	id = other.id;
	nombre = other.nombre;
	localizacion = other.localizacion;
	numHabTotales = other.numHabTotales;
	numHabActuales = other.numHabActuales;

	habitaciones = new Habitacion[other.numHabTotales];
	for (int i = 0; i < other.numHabTotales; ++i) {
		this->habitaciones[i] = other.habitaciones[i];
	}
}

/////////////////// GETTERS ///////////////////////

int Hotel::getId()
{
	return this->id;
}

char* Hotel::getNombre()
{
	return this->nombre;
}

char* Hotel::getLocalizacion()
{
	return this->localizacion;
}

int Hotel::getNumHabTotales()
{
	return this->numHabTotales;
}

int Hotel::getNumHabActuales()
{
	return this->numHabActuales;
}

Habitacion* Hotel::getHabitaciones()
{
	return this->habitaciones;
}
