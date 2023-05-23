#include <iostream>
#include "Habitacion.h"
#include "stdio.h"
#include "string.h"

using namespace std;

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

/////////////////// SETTERS ///////////////////////

void Habitacion::setOcupantes(int ocupantes)
{
	this->ocupantes = ocupantes;
}

/////////////////// FUNCIONES ///////////////////////

void Habitacion::imprimirHabitacion()
{
	char* estado = new char [10];
	strcpy(estado, "OCUPADA");
	if (this->estaLibre())
		strcpy(estado, "LIBRE");

	cout << "[" << this->num_habitacion << " - " << this->tipoHab->getTipo() << " - " << estado << "]" << endl;
}

int Habitacion::estaLibre()
{
	if (this->ocupantes)
		return 0;

	return 1;
}
