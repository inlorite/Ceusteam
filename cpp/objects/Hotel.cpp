
#include <iostream>
#include "Hotel.h"
#include "string.h"

using namespace std;

Hotel::Hotel() {
	id = 0;
	nombre = new char[10];
	localizacion = new char[10];
	numHabTotales = 10;
	numHabActuales = 10;
	habitaciones = new Habitacion[10];
}

Hotel::Hotel(int id, char* nombre, char* localizacion, int numHabTotales, int numHabActuales, Habitacion* habitaciones) {
	this->id = id;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this->localizacion = new char[strlen(localizacion)+1];
	strcpy(this->localizacion, localizacion);
	this->numHabTotales = numHabTotales;
	this->numHabActuales = numHabActuales;

	this->habitaciones = new Habitacion[numHabTotales];
	for (int i = 0; i < numHabTotales; ++i) {
		this->habitaciones[i] = habitaciones[i];
	}
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

/////////////////// SETTERS ///////////////////////

void Hotel::setNumHabActuales(int numHabActuales)
{
	this->numHabActuales = numHabActuales;
}

/////////////////// FUNCIONES ///////////////////////

void Hotel::imprimirHotel()
{
	cout << "[" << this->id << " - " << this->nombre << " - " << this->localizacion << "Ocupacion: " << this->numHabActuales << "/"<< this->numHabTotales << "]" << endl;
}

void Hotel::visualizarHabitacionesHotel()
{
	for (int i = 0; i < this->numHabActuales; ++i) {
		this->habitaciones[i].imprimirHabitacion();
	}
}
